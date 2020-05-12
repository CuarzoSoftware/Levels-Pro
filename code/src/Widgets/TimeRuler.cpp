#include "TimeRuler.h"
#include <QDebug>

TimeRuler::TimeRuler()
{
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
    repaint();
}

void TimeRuler::scrollChanged(float x)
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


    float tickWidth = 200.f*(zoom) + (1.f - zoom)*w/timeSettings->projectLenghtInTicks;
    float barSize = tickWidth*timeSettings->ticksPerBar;

    painter.setViewport(-offset*timeSettings->projectLenghtInTicks*tickWidth,0,w,h);

    // Draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundBrush);
    painter.drawRect(0,0,timeSettings->projectLenghtInTicks*tickWidth,h);

    //painter.setBrush(QBrush(Qt::red));
    //painter.drawRect(0,0,tickWidth,h);


    uint x;
    uint lines = w/barSize;
    for(uint i = 0; i < timeSettings->projectLenghtInBars; i++)
    {
        painter.setPen(barPen);
        x = i*barSize;
        painter.drawLine(x, h, x, 0);

        // Draw text
        painter.setPen(textPen);
        painter.drawText(x+6,h-6,QString::number(i+1));
    }

    /*
    // Draw Bar Lines
    uint x;
    uint lines = w/barSize;
    for(uint i = 0; i < lines; i++)
    {
        painter.setPen(barPen);
        x = i*barSize;
        painter.drawLine(x, h, x, 0);

        // Draw text
        painter.setPen(textPen);
        painter.drawText(x+6,h-6,QString::number(i+1));
    }
    */
    // Draw border bottom
    painter.setPen(borderPen);
    painter.drawLine(0, h, w, h);
}


void TimeRuler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    paintRuler();
}










