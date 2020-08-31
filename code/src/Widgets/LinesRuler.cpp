#include "LinesRuler.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QtMath>
#include <QDebug>

// Constructor
LinesRuler::LinesRuler()
{

    // Set the font styles for the ruler numbers
    QFont font("SF Pro Display");
    font.setPixelSize(13);
    font.setWeight(QFont::Weight::Normal);
    setFont(font);

    // Set the shadow gradient of the project end
    projectEndShadow.setColorAt(0,QColor(0,0,0,70));
    projectEndShadow.setColorAt(0.3,QColor(0,0,0,30));
    projectEndShadow.setColorAt(1,QColor(0,0,0,0));

    // Sets a fixed height
    setFixedHeight(18);

}

void LinesRuler::setHorizontalScrollBar(ScrollBar *sb)
{
    hScrollBar = sb;
    connect(hScrollBar,&ScrollBar::valueChanged,this,&LinesRuler::scrollChanged);
}

void LinesRuler::setTimeSettings(TimeSettings *settings)
{
    timeSettings = settings;
    connect(timeSettings,&TimeSettings::projectLengthChanged,this,&LinesRuler::projectLengthChanged);
}

void LinesRuler::setZoom(float _zoom)
{
    // Stores the newz zoom value
    zoom = _zoom;

    // Calculate useful metrics to prevent re calculating
    updateDimensions();

    // Refresh the view
    repaint();
}

void LinesRuler::scrollChanged(int x)
{
    // Stores the new position
    offset = x;

    // Refresh the view
    repaint();
}

void LinesRuler::getBeginAndEndIndex()
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

void LinesRuler::updateDimensions()
{
    tickWidth = 200.f*(zoom) + (1.f - zoom)*((float)width() -28.f)/timeSettings->projectLenghtInTicks;
    barWidth = tickWidth*timeSettings->ticksPerBar;
    beatWidth = barWidth/timeSettings->beatsNumber;
    divWidth = beatWidth/timeSettings->divitionsPerBeat;
    totalWidth = timeSettings->projectLenghtInTicks*tickWidth;
}

// Draw bar lines
void LinesRuler::drawBars()
{
    // Number of bars skipped
    skip = 1 + 40/currentDimension;

    getBeginAndEndIndex();

    for(i = begin; i < end; i+=powSkip)
    {
        // Gets the x position
        x = i*barWidth;

        // Paint the bar line
        painter->setPen(linePen);

        painter->drawLine(x-0.5-offset, h, x-0.5-offset, 0);


    }
}

// Draw beat lines
void LinesRuler::drawBeats()
{
    if(barWidth < 5) return;

    // Number of beats skipped
    skip = 1 + 10/currentDimension;

    getBeginAndEndIndex();

    for(i = begin;i < end; i+=powSkip)
    {
        x = i*beatWidth;
        painter->drawLine(x-0.5-offset, h, x-0.5-offset, 9);
    }
}

// Draw divition lines
void LinesRuler::drawDivitions()
{
    if(beatWidth < 5) return;

    // Number of divs skipped
    skip = 1 + 10/currentDimension;

    getBeginAndEndIndex();

    for(i = begin;i < end; i+=powSkip)
    {
        x = i*divWidth;
        painter->drawLine(x-0.5-offset, h, x-0.5-offset, 12);
    }
}

// Draw ticks numbers including divitions
void LinesRuler::drawTicks()
{
    if(divWidth < 80) return;

    // Number of divs skipped
    skip = 1 + 11 / currentDimension;

    getBeginAndEndIndex();

    for(i = begin;i < end; i+=powSkip)
    {
        tick =  i % (uint)timeSettings->ticksPerDivition;
        if(tick != 0)
        {
            x = i*tickWidth;

            painter->drawLine(x-0.5-offset, h, x-0.5-offset, 14);

        }

    }
}
void LinesRuler::drawProjectEnd()
{

}

void LinesRuler::paintRuler()
{
    // Draw Bar Lines
    drawBars();

    // Visible area ( Size of the window )
    w = width();
    h = height();

    // Prevent negative numbers
    if(offset < 0)
        offset = 0;

    // Draw background
    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundBrush);
    painter->drawRect(0,0,w,h);

    // Draw border bottom
    painter->setPen(borderPen);
    painter->drawLine(0,h,w,h);

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
        //drawTicksWithoutDivitions();
    }


}

void LinesRuler::paintEvent(QPaintEvent *event)
{
    // Disable unused warings
    Q_UNUSED(event);

    // Begin painting
    painter->begin(this);

    // Paint Ruler
    paintRuler();

    // Paint project end
    drawProjectEnd();

    // Ends painting
    painter->end();
}

void LinesRuler::projectLengthChanged()
{
    updateDimensions();
}










