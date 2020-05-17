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
    QMatrix mat = dashesBrush.matrix();
    mat.scale(0.55f,0.55f);
    dashesBrush.setMatrix(mat);
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
    w = width();
    h = height();

    painter->setViewport(-offset,0,w,h);

    if(offset < 0)
        offset = 0;

    // Loop Bar position
    loopBeginPos = timeSettings->loopBeginTick*tickWidth;
    loopEndPos = timeSettings->loopEndTick*tickWidth;
    isLoopBarVisible = true;
    //timeSettings->loop = false;

    // Clips and checks if appears on current viewport
    if( loopBeginPos < offset)
        loopBeginPos = offset;

    if( loopBeginPos > offset + w)
        isLoopBarVisible = false;

    if( loopEndPos > offset + w)
        loopEndPos = offset +w;

    if( loopEndPos < offset)
        isLoopBarVisible = false;


    // Draw background
    painter->setPen(Qt::NoPen);

    // If loop is ON
    if(timeSettings->loop)
    {
        // Draw normal background
       painter->setBrush(dashesBrush);
       painter->drawRect(offset,0,w,h);
    }
    else
    {
        // Draw dashed background
        painter->setBrush(backgroundBrush);
        painter->drawRect(offset,0,w,h);

        // Draw disabled bar
        if(isLoopBarVisible)
        {
            painter->setBrush(loopDisabledBrush);
            painter->setPen(loopPen);
            painter->drawRect(loopBeginPos,0,loopEndPos-loopBeginPos,h);
        }

    }

    textPen.setColor(textWhite);
    barPen.setColor(barWhite);

    // Draw border bottom
    painter->setPen(borderPen);
    painter->drawLine(offset, h, offset + w,h);

    innerOffset = offset;

    // BARS
    currentDimension = barWidth;
    drawBars();


    // BEATS
    currentDimension = beatWidth;
    drawBeats();


    // Only for 1, 2, 4, 8 beat note values
    if(timeSettings->noteValue <= 8)
    {
        // DIVITIONS
        currentDimension = divWidth;
        drawDivitions();

        // TICKS WITH DIVITIONS
        currentDimension = tickWidth;
        drawTicks();
    }
    else
    {
        // TICKS WITHOUT DIVITIONS
        currentDimension = tickWidth;
        drawTicksWithoutDivitions();
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

void TimeRuler::drawBars()
{
    // Number of bars skipped
    skip = 1 + 100/currentDimension;

    getBeginAndEndIndex();

    for(i = begin; i < end; i+=powSkip)
    {
        // Gets the x position
        x = i*barWidth;

        // Paint the bar line
        painter->setPen(barPen);
        painter->drawLine(x, h, x, 3);

        // Draw the bar number
        painter->setPen(textPen);
        painter->drawText(x+6,h-6,QString::number(i+1));


    }
}

void TimeRuler::drawBeats()
{
    if(barWidth < 200) return;

    // Number of beats skipped
    skip = 1 + 100/currentDimension;

    getBeginAndEndIndex();

    for(i = begin;i < end; i+=powSkip)
    {
        beat =  i % timeSettings->beatsNumber;

        if(beat != 0) // Prevent overlapping with the bar number
        {
            x = i*beatWidth;
            bar = i / timeSettings->beatsNumber + 1;
            painter->drawText(x+6,h-6,QString::number(bar)+" "+QString::number(beat + 1));
        }
    }
}

void TimeRuler::drawDivitions()
{
    if(beatWidth < 200) return;

    // Number of divs skipped
    skip = 1 + 100/currentDimension;

    getBeginAndEndIndex();

    for(i = begin;i < end; i+=powSkip)
    {
        div =  i % (uint) timeSettings->divitionsPerBeat;
        if(div != 0)
        {
            x = i*divWidth;

            beat =  (i/(uint)timeSettings->divitionsPerBeat)%timeSettings->beatsNumber;
            bar = i / timeSettings->divitionsPerBar + 1;
            painter->drawText(x+6,h-6,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(div + 1));

        }

    }
}

void TimeRuler::drawTicks()
{
    if(divWidth < 180) return;

    // Number of divs skipped
    skip = 1 + 180 / currentDimension;

    getBeginAndEndIndex();

    for(i = begin;i < end; i+=powSkip)
    {
        tick =  i % (uint)timeSettings->ticksPerDivition;
        if(tick != 0)
        {
            x = i*tickWidth;

            if(60 < tick*tickWidth && 80 < (timeSettings->ticksPerDivition - tick)*tickWidth)
            {
                beat =  (i/(uint)timeSettings->ticksPerBeat) % timeSettings->beatsNumber;
                div =  (i / (uint)timeSettings->ticksPerDivition) % (uint)timeSettings->divitionsPerBeat;
                bar = i / timeSettings->ticksPerBar + 1;

                painter->drawText(x+6,h-6,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(div + 1)+" "+QString::number(tick + 1));
            }
        }

    }
}

void TimeRuler::drawTicksWithoutDivitions()
{
    if(divWidth < 180) return;

    // Number of divs skipped
    skip = 1 + 180 / currentDimension;

    getBeginAndEndIndex();

    for(i = begin;i < end; i+=powSkip)
    {
        tick =  i % (uint)timeSettings->ticksPerDivition;
        if(tick != 0)
        {
            x = i*tickWidth;

            if(60 < tick*tickWidth && 80 < (timeSettings->ticksPerDivition - tick)*tickWidth)
            {
                beat =  (i/(uint)timeSettings->ticksPerBeat) % timeSettings->beatsNumber;
                bar = i / timeSettings->ticksPerBar + 1;

                painter->drawText(x+6,h-6,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(tick + 1));
            }
        }

    }
}

void TimeRuler::drawLoop()
{
    if(!timeSettings->loop || !isLoopBarVisible) return;


    innerOffset = loopBeginPos;
    w = loopEndPos-loopBeginPos;

    painter->setClipRect(loopBeginPos,0,w,h);
    painter->setClipping(true);

    painter->setPen(loopPen);
    painter->setBrush(loopEnabledBrush);

    painter->drawRect(loopBeginPos,0,w,h);

    textPen.setColor(Qt::black);
    barPen.setColor(Qt::black);


    // BARS
    currentDimension = barWidth;
    drawBars();


    // BEATS
    currentDimension = beatWidth;
    drawBeats();


    // Only for 1, 2, 4, 8 beat note values
    if(timeSettings->noteValue <= 8)
    {
        // DIVITIONS
        currentDimension = divWidth;
        drawDivitions();

        // TICKS WITH DIVITIONS
        currentDimension = tickWidth;
        drawTicks();
    }
    else
    {
        // TICKS WITHOUT DIVITIONS
        currentDimension = tickWidth;
        drawTicksWithoutDivitions();
    }


}

void TimeRuler::getBeginAndEndIndex()
{


    // Filter numbers different from pow of 2
    powSkip = 1;
    if( skip > 1 )
        while(powSkip<<1 <= skip)
            powSkip = powSkip<<1;

    begin = innerOffset / (currentDimension*powSkip);

    // For some reason it works if I multiply here
    begin *= powSkip;

    end = begin + w/currentDimension + powSkip*2;

}


void TimeRuler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter->begin(this);
    paintRuler();
    drawLoop();
    painter->end();
}











