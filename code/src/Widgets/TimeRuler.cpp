#include "TimeRuler.h"
#include <QtMath>
#include <QDebug>

TimeRuler::TimeRuler(HScrollBar *sb)
{
    hScrollBar = sb;
    QFont font("Helvetica Neue");
    font.setPixelSize(13);
    font.setWeight(QFont::Weight::Bold);
    setFont(font);
    setFixedHeight(20);

}

void TimeRuler::setBackgroundColor(const QColor &color)
{
    backgroundBrush.setColor(color);
}

void TimeRuler::setTimeSettings(TimeSettings *settings)
{
    timeSettings = settings;
}

void TimeRuler::setZoom(float _zoom)
{
    //zoom = _zoom;
    zoom = _zoom;
    updateDimensions();
    repaint();
}

void TimeRuler::scrollChanged(int x)
{
    offset = x;
    repaint();
}

void TimeRuler::paintRuler()
{
    // Visible area
    uint w = width();
    uint h = height();

    QPainter painter(this);

    painter.setViewport(-offset,0,w,h);

    // Draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundBrush);
    painter.drawRect(offset,0,w,h);

    // Draw border bottom
    painter.setPen(borderPen);
    painter.drawLine(offset, h, offset + w,h);


    uint i, x, beat, bar, div, tick;

    /*************************
     ** BARS PRINTING
     *************************/

    // Number of bars skipped
    uint skip = 1 + 100/barWidth;
    uint powSkip = 1;

    // Filter numbers different from pow of 2
    if( skip > 1 )
        while(powSkip<<1 <= skip)
            powSkip = powSkip<<1;


    for(i = 0; i < timeSettings->projectLenghtInBars; i+=powSkip)
    {
        // Gets the x position
        x = i*barWidth;


        if(x > offset + w)
            break;

        if(x >= offset - barWidth)
        {
            // Paint the bar line
            painter.setPen(barPen);
            painter.drawLine(x, h, x, 3);

            // Draw the bar number
            painter.setPen(textPen);
            painter.drawText(x+6,h-6,QString::number(i+1));
        }

    }

    return;

    if(barWidth < 200) return;

    /*************************
     ** BEATS PRINTING
     *************************/

    // Number of beats skipped
    skip = 1 + 100/beatWidth;
    powSkip = 1;

    // Filter numbers different from pow of 2
    if( skip > 1 )
        while(powSkip<<1 <= skip)
            powSkip = powSkip<<1;


    for(i = 0;i < timeSettings->projectLengthInBeats; i+=powSkip)
    {
        beat =  i % timeSettings->beatsNumber;
        if(beat != 0)
        {
            x = i*beatWidth;

            if(x > offset + w)
                break;

            if(x >= offset - beatWidth)
            {
                bar = i / timeSettings->beatsNumber + 1;
                painter.drawText(x+6,h-6,QString::number(bar)+" "+QString::number(beat + 1));
            }
        }

    }

    /*************************
     ** DIVITIONS PRINTING
     *************************/

    // Only for 1, 2, 4, 8 beat note values
    if(timeSettings->noteValue <= 8)
    {

        if(beatWidth < 200) return;

        // Number of divs skipped
        skip = 1 + 100/divWidth;
        powSkip = 1;

        // Filter numbers different from pow of 2
        if( skip > 1 )
            while(powSkip<<1 <= skip)
                powSkip = powSkip<<1;


        for(i = 0;i < timeSettings->projectLengthInDivitions; i+=powSkip)
        {
            div =  i % (uint) timeSettings->divitionsPerBeat;
            if(div != 0)
            {
                x = i*divWidth;

                if(x > offset + w)
                    break;

                if(x >= offset - divWidth)
                {
                    beat =  (i/(uint)timeSettings->divitionsPerBeat)%timeSettings->beatsNumber;
                    bar = i / timeSettings->divitionsPerBar + 1;
                    painter.drawText(x+6,h-6,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(div + 1));
                }
            }

        }

        if(divWidth < 180) return;

        /********************************
         ** TICKS PRINTING WITH DIVITIONS
         ********************************/

        // Number of divs skipped
        skip = 1 + 180 / tickWidth;
        powSkip = 1;

        // Filter numbers different from pow of 2
        if( skip > 1 )
            while(powSkip<<1 <= skip)
                powSkip = powSkip<<1;



        for(i = 0;i < timeSettings->projectLenghtInTicks; i+=powSkip)
        {
            tick =  i % (uint)timeSettings->ticksPerDivition;
            if(tick != 0)
            {
                x = i*tickWidth;

                if(x > offset + w)
                    break;

                if(x >= offset - tickWidth && 60 < tick*tickWidth && 80 < (timeSettings->ticksPerDivition - tick)*tickWidth)
                {
                    beat =  (i/(uint)timeSettings->ticksPerBeat) % timeSettings->beatsNumber;
                    div =  (i / (uint)timeSettings->ticksPerDivition) % (uint)timeSettings->divitionsPerBeat;
                    bar = i / timeSettings->ticksPerBar + 1;

                    painter.drawText(x+6,h-6,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(div + 1)+" "+QString::number(tick + 1));
                }
            }

        }
    }
    else
    {
        if(divWidth < 180) return;

        /********************************
         ** TICKS PRINTING WITH DIVITIONS
         ********************************/

        // Number of divs skipped
        skip = 1 + 180 / tickWidth;
        powSkip = 1;

        // Filter numbers different from pow of 2
        if( skip > 1 )
            while(powSkip<<1 <= skip)
                powSkip = powSkip<<1;


        for(i = 0;i < timeSettings->projectLenghtInTicks; i+=powSkip)
        {
            tick =  i % (uint)timeSettings->ticksPerDivition;
            if(tick != 0)
            {
                x = i*tickWidth;

                if(x > offset + w)
                    break;

                if(x >= offset - tickWidth && 60 < tick*tickWidth && 80 < (timeSettings->ticksPerDivition - tick)*tickWidth)
                {
                    beat =  (i/(uint)timeSettings->ticksPerBeat) % timeSettings->beatsNumber;
                    bar = i / timeSettings->ticksPerBar + 1;

                    painter.drawText(x+6,h-6,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(tick + 1));
                }
            }

        }
    }










}

void TimeRuler::updateDimensions()
{
    tickWidth = 200.f*(zoom) + (1.f - zoom)*width()/timeSettings->projectLenghtInTicks;
    barWidth = tickWidth*timeSettings->ticksPerBar;
    beatWidth = barWidth/timeSettings->beatsNumber;
    divWidth = beatWidth/timeSettings->divitionsPerBeat;
    totalWidth = timeSettings->projectLenghtInTicks*tickWidth;

    // Asign the horizontal scroll range
    hScrollBar->setRange(totalWidth - width());
}


void TimeRuler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    paintRuler();
}











