#include "TimeRuler.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include <QCursor>
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
TimeRuler::TimeRuler()
{

    // Set the font styles for the ruler numbers
    QFont font("SF Pro Display");
    font.setPixelSize(13);
    font.setWeight(QFont::Weight::Normal);
    setFont(font);

    // Adjust the size of the dashed background texture
    QTransform mat = dashesBrush.transform();
    mat.scale(0.55f,0.55f);
    dashesBrush.setTransform(mat);

    // Set the shadow gradient of the project end
    projectEndShadow.setColorAt(0,QColor(0,0,0,70));
    projectEndShadow.setColorAt(0.3,QColor(0,0,0,30));
    projectEndShadow.setColorAt(1,QColor(0,0,0,0));

    // Sets a fixed height
    setFixedHeight(18);
    setMouseTracking(true);

    // Setup the project length resize timer
    connect(projectLengthResizeDelay,&QTimer::timeout,this,&TimeRuler::projectLengthResize);


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
    connect(timeSettings,&TimeSettings::projectLengthChanged,this,&TimeRuler::projectLengthChanged);
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
       painter->drawRect(0,0,w,h);
    }
    // If looping is disabled
    else
    {
        // Draw normal background
        painter->setBrush(backgroundBrush);
        painter->drawRect(0,0,w,h);

        // Draw disabled bar ( gray )
        if(isLoopBarVisible)
        {
            painter->setBrush(loopDisabledBrush);
            painter->drawRect(loopBeginPos-offset,0,loopEndPos-loopBeginPos-offset,h);
        }

    }

    // Set the text pen
    textPen.setColor(textWhite);
    barPen.setColor(barWhite);

    // Draw border bottom
    painter->setPen(borderPen);
    painter->drawLine(0, h, w,h);

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
    tickWidth = 200.f*(zoom) + (1.f - zoom)*((float)width() -28.f)/timeSettings->projectLenghtInTicks;
    barWidth = tickWidth*timeSettings->ticksPerBar;
    beatWidth = barWidth/timeSettings->beatsNumber;
    divWidth = beatWidth/timeSettings->divitionsPerBeat;
    totalWidth = timeSettings->projectLenghtInTicks*tickWidth;

    // Asign the horizontal scroll range
    hScrollBar->setRange(0,totalWidth - width() + 28);
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
        painter->drawLine(x-0.5-offset, h, x-0.5-offset, 3);

        // Draw the bar number
        painter->setPen(textPen);
        painter->drawText(x+5-offset,h-5,QString::number(i+1));

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
            painter->drawText(x+5-offset,h-5,QString::number(bar)+" "+QString::number(beat + 1));
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
            painter->drawText(x+5-offset,h-5,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(div + 1));

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

                painter->drawText(x+5-offset,h-5,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(div + 1)+" "+QString::number(tick + 1));
            }
        }

    }
}

// Draw ticks numbers exccluding divitions
void TimeRuler::drawTicksWithoutDivitions()
{
    if(divWidth < 50) return;

    // Number of divs skipped
    skip = 1 + 50 / currentDimension;

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

                painter->drawText(x+5-offset,h-5,QString::number(bar)+" "+QString::number(beat + 1)+" "+QString::number(tick + 1));
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

    painter->setClipRect(loopBeginPos - offset,0,w,h);
    painter->setClipping(true);

    painter->setPen(Qt::NoPen);
    painter->setBrush(loopEnabledBrush);

    painter->drawRect(loopBeginPos - offset,0,w-0.5,h);

    textPen.setColor(Qt::white);
    barPen.setColor(Qt::white);


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
    painter->drawRect(totalWidth-offset,0,w,h);

    // Draw shadow
    projectEndShadow.setStart(totalWidth - offset,0);
    projectEndShadow.setFinalStop(totalWidth - offset + 20,0);
    painter->setBrush(projectEndShadow);
    painter->drawRect(totalWidth - offset ,0,20,h);

    // Draw handle
    painter->drawPixmap(totalWidth+1-offset,2,h-3,h-4,lengthHandle);

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

void TimeRuler::setHorizontalScrollBar(ScrollBar *sb)
{
    hScrollBar = sb;
    connect(hScrollBar,&ScrollBar::valueChanged,this,&TimeRuler::scrollChanged);
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

void TimeRuler::resizeEvent(QResizeEvent *event)
{
    int delta = event->size().width() - event->oldSize().width();

    hScrollBar->setRange(0,totalWidth - width() + 28);

    // If the width increases and the scroll is at the end
    if(delta > 0 && offset > 0 && offset + width() > totalWidth + 28)
    {
        // Scrolls backwards
        hScrollBar->setValue(hScrollBar->value() + delta);
    }

}



void TimeRuler::mouseMoveEvent(QMouseEvent *event)
{

    // If dragging the project length resizer handle
    if(changingProjectlength)
    {

        if(totalWidthOld + event->x() - projectLengthDragBegin + offset < 0)
        {
            resizeDirection = 0;
            totalWidth = 0;
            return;
        }

        if(event->x() > width() - 10)
        {
            resizeDirection = 2;
            projectLengthResize();
        }
        else if(event->x() < 0)
        {
            resizeDirection = -2;
            projectLengthResize();
        }
        else
        {
            resizeDirection = 0;
        }

        totalWidth = totalWidthOld + event->x() - projectLengthDragBegin + offset;
        repaint();
        return;
    }


    // If the cursor is over the project length resizer handle
    if(event->x() >= totalWidth - offset)
    {
        setCursor(Qt::SizeHorCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void TimeRuler::mousePressEvent(QMouseEvent *event)
{
    if(event->x() >= totalWidth - offset)
    {
        totalWidthOld = totalWidth;
        projectLengthDragBegin = event->x() + offset;
        changingProjectlength = true;
    }

}

void TimeRuler::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(changingProjectlength)
    {
        changingProjectlength = false;
        float newLength = totalWidth*timeSettings->projectLenghtInTicks/totalWidthOld;

        if(newLength < timeSettings->ticksPerBar*2)
            newLength = timeSettings->ticksPerBar*2;

        timeSettings->setProjectLengthInTicks(newLength);

    }
}

void TimeRuler::projectLengthResize()
{
    if(changingProjectlength && resizeDirection != 0)
    {
        offset += resizeDirection;
        hScrollBar->setRange(0,hScrollBar->maximum()+resizeDirection);
        hScrollBar->setValue(hScrollBar->value()+resizeDirection);
        projectLengthResizeDelay->start(1);

        totalWidth = totalWidthOld + mapFromGlobal(QCursor::pos()).x() - projectLengthDragBegin + offset;
        repaint();
    }
}

void TimeRuler::projectLengthChanged()
{
    updateDimensions();
    setZoom(0.f);
    hScrollBar->setValue(0);
}











