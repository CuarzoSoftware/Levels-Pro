#include "TimeRuler.h"
#include <QtMath>
#include <QDebug>

/*!
    \class TimeRuler
    \brief The TimeRuler class...

    \inheaderfile Widgets/TimeRuler.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QWidget
*/

// Constructor
TimeRuler::TimeRuler(HScrollBar *sb)
{

    // Stores the horizontal scroll bar
    hScrollBar = sb;

    // Set the font styles for the ruler numbers
    QFont font("Helvetica Neue");
    font.setPixelSize(13);
    font.setWeight(QFont::Weight::Bold);
    setFont(font);

    // Adjust the size of the dashed background texture
    QMatrix mat = dashesBrush.matrix();
    mat.scale(0.55f,0.55f);
    dashesBrush.setMatrix(mat);

    // Set the shadow gradient of the project end
    projectEndShadow.setColorAt(0,Qt::black);
    projectEndShadow.setColorAt(0.1,QColor(0,0,0,50));
    projectEndShadow.setColorAt(1,QColor(0,0,0,0));

    // Sets a fixed height
    setFixedHeight(20);

}

// Changes the default background color
void TimeRuler::setBackgroundColor(const QColor &color)
{
    backgroundBrush.setColor(color);
}

// Store the time settings reference ( Project settings )
void TimeRuler::setTimeSettings(TimeSettings *settings)
{
    timeSettings = settings;
}

// Changes the zoom
void TimeRuler::setZoom(float _zoom)
{
    // Stores the newz zoom value
    zoom = _zoom;

    // Calculate useful metrics to prevent re calculating
    updateDimensions();

    // Refresh the view
    repaint();
}

// Changes the scroll position
void TimeRuler::scrollChanged(int x)
{
    // Stores the new position
    offset = x;

    // Refresh the view
    repaint();
}

// Paint the time ruler, ( Bars, beats, divs, ticks, etc )
void TimeRuler::paintRuler()
{
    // Visible area ( Size of the window )
    w = width();
    h = height();

    // Moves the viewport to the scroll position
    painter->setViewport(-offset,0,w,h);

    // Prevent negative numbers
    if(offset < 0)
        offset = 0;

    // Calculates the loopbar initial position ( in pixels )
    loopBeginPos = timeSettings->loopBeginTick*tickWidth;

    // Calculates the loopbar final position ( in pixels )
    loopEndPos = timeSettings->loopEndTick*tickWidth;

    // Tells if the loop bar is visible from the viewport
    isLoopBarVisible = true;

    // LOOP BAR TRIMMING

    // If loop bar doesn't appear in the viewport
    if( loopBeginPos > offset + w || loopEndPos < offset)
        isLoopBarVisible = false;
    else
    {
        // If loop bar begins before the viewport
        if( loopBeginPos < offset)
            loopBeginPos = offset;

        // If loop bar ends after the viewport
        if( loopEndPos > offset + w)
            loopEndPos = offset +w;
    }

    // Draw background
    painter->setPen(Qt::NoPen);

    // If looping is enabled
    if(timeSettings->loop)
    {
       // Draw dashed background
       painter->setBrush(dashesBrush);
       painter->drawRect(offset,0,w,h);
    }
    // If looping is disabled
    else
    {
        // Draw normal background
        painter->setBrush(backgroundBrush);
        painter->drawRect(offset,0,w,h);

        // Draw disabled bar ( gray )
        if(isLoopBarVisible)
        {
            painter->setBrush(loopDisabledBrush);
            painter->setPen(loopPen);
            painter->drawRect(loopBeginPos,0,loopEndPos-loopBeginPos,h);
        }

    }

    // Set the text pen
    textPen.setColor(textWhite);
    barPen.setColor(barWhite);

    // Draw border bottom
    painter->setPen(borderPen);
    painter->drawLine(offset, h, offset + w,h);

    // Used later on for begin and end index calculation
    innerOffset = offset;

    // DRAW BARS
    currentDimension = barWidth;
    drawBars();

    // DRAW BEATS
    currentDimension = beatWidth;
    drawBeats();


    // Draw Divitions only for 1, 2, 4 and 8 beat note values
    if(timeSettings->noteValue <= 8)
    {
        // DRAW DIVITIONS
        currentDimension = divWidth;
        drawDivitions();

        // DRAW TICKS WITH DIVITIONS
        currentDimension = tickWidth;
        drawTicks();
    }
    else
    {
        // DRAW TICKS WITHOUT DIVITIONS
        currentDimension = tickWidth;
        drawTicksWithoutDivitions();
    }


}

// Calculate useful metrics for later on, and set the scroll range
void TimeRuler::updateDimensions()
{
    tickWidth = 200.f*(zoom) + (1.f - zoom)*width()/timeSettings->projectLenghtInTicks;
    barWidth = tickWidth*timeSettings->ticksPerBar;
    beatWidth = barWidth/timeSettings->beatsNumber;
    divWidth = beatWidth/timeSettings->divitionsPerBeat;
    totalWidth = timeSettings->projectLenghtInTicks*tickWidth;

    // Asign the horizontal scroll range
    hScrollBar->setRange(totalWidth - width() + 40);
}

// Draw bar lines and numbers
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

// Draw beat numbers
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

// Draw divitions numbers
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

// Draw ticks numbers including divitions
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

// Draw ticks numbers exccluding divitions
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

// Draws the loop bar ( If is enabled (orange), needs to redraw the numbers in black )
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

// Draws the project end and resize handle
void TimeRuler::drawProjectLengthHandle()
{
    w = width();

    if(offset + w < totalWidth) return;

    // Draw dark background ( Outside project length )
    painter->setPen(Qt::NoPen);
    painter->setBrush(transparentBlack);
    painter->setClipping(false);
    painter->drawRect(totalWidth,0,offset+w,h);

    // Draw shadow
    projectEndShadow.setStart(totalWidth,0);
    projectEndShadow.setFinalStop(totalWidth + 10,0);
    painter->setBrush(projectEndShadow);
    painter->drawRect(totalWidth,0,10,h);

    // Draw handle
    painter->drawPixmap(totalWidth+1,2,h-3,h-4,lengthHandle);

}

// Calculates the visible begin and end index for each time divition drawing, and the skipping value
void TimeRuler::getBeginAndEndIndex()
{

    // Filter numbers different from pow of 2
    powSkip = 1;
    if( skip > 1 )
        while(powSkip<<1 <= skip)
            powSkip = powSkip<<1;

    // First visible index
    begin = innerOffset / (currentDimension*powSkip);

    // For some reason the multiplication needs to be done separately
    begin *= powSkip;

    // Last visible index
    end = begin + w/currentDimension + powSkip*2;

}


void TimeRuler::paintEvent(QPaintEvent *event)
{
    // Disable unused warings
    Q_UNUSED(event);

    // Begin painting
    painter->begin(this);

    // Paint Ruler
    paintRuler();

    // Paint Loop Bar
    drawLoop();

    // Paint project end
    drawProjectLengthHandle();

    // Ends painting
    painter->end();
}











