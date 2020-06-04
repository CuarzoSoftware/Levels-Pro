#include "Ruler.h"

/*!
    \class Ruler
    \brief The Ruler class...

    \inheaderfile Widgets/Ruler.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QWidget
*/

Ruler::Ruler(RulerType type)
{
    rulerType = type;

    // If is the number ruler, sets the font
    if(rulerType == RulerType::NumberRuler)
    {
        QFont font("Helvetica Neue");
        font.setPixelSize(13);
        font.setWeight(QFont::Weight::Bold);
        setFont(font);
    }
}

void Ruler::setBackgroundColor(const QColor &color)
{
    backgroundBrush.setColor(color);
}

void Ruler::setBarSize(uint barSizePixels)
{
    barSize = barSizePixels;
}

void Ruler::setBeatsPerBar(uint beats)
{
    beatsPerBar = beats;
}

void Ruler::numberRulerPaint()
{
    uint w = width();
    uint h = height();

    QPainter painter(this);

    // Draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundBrush);
    painter.drawRect(0,0,w,h);

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

    // Draw border bottom
    painter.setPen(borderPen);
    painter.drawLine(0, h, w, h);
}

void Ruler::marksRulerPaint()
{
    uint w = width();
    uint h = height();

    QPainter painter(this);

    // Draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundBrush);
    painter.drawRect(0,0,w,h);

    // Draw Bar Lines
    uint x,beatX;
    uint beatSize = barSize/beatsPerBar;
    uint lines = w/barSize;
    for(uint i = 0; i < lines; i++)
    {
        painter.setPen(barPen);
        x = i*barSize;
        painter.drawLine(x, h, x, 0);

        // Draw beat lines
        painter.setPen(beatPen);
        for(uint j = 1;j<beatsPerBar; j++)
        {
            beatX = j*beatSize + x;
            painter.drawLine(beatX, h, beatX, h - h/4);
        }
    }

    // Draw border bottom
    painter.setPen(borderPen);
    painter.drawLine(0, h, w, h);
}

void Ruler::tracksRulerPaint()
{
    uint w = width();
    uint h = height();

    QPainter painter(this);

    // Draw background
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundBrush);
    painter.drawRect(0,0,w,h);

    // Draw Bar Lines
    uint x;
    uint lines = w/barSize;
    painter.setPen(barPen);

    for(uint i = 0; i < lines; i++)
    {
        x = i*barSize;
        painter.drawLine(x, h, x, 0);
    }

}


void Ruler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    switch(rulerType)
    {
        case RulerType::NumberRuler:
        numberRulerPaint();
        break;
        case RulerType::MarksRuler:
        marksRulerPaint();
        break;
        case RulerType::TracksRuler:
        tracksRulerPaint();
        break;
        default:
        return;
    }



}
