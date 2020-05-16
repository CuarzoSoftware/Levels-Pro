#include "HScrollBar.h"
#include <QVariant>
#include <QEvent>
#include <QWheelEvent>
#include <QtMath>
#include <QDebug>

HScrollBar::HScrollBar(QWidget *parent, Position pos)
{
    // Assign parent
    setParent(parent);

    // Sets the position
    setPosition(pos);

    // Allows background color
    setAttribute(Qt::WA_StyledBackground, true);

    // Style class
    setProperty("class","scrollBar");

    // Sets fixed height
    setFixedHeight(14);
    bar->setFixedSize(200,8);
    bar->move(0,3);

    // Refresh the position
    refreshPosition();

    // Listen to parent events ( Resize, scroll, etc )
    parent->installEventFilter(this);
}

// Range in pixels ( The size of the target widget )
void HScrollBar::setRange(int _range)
{
    range = _range;

    // Sets the bar width
    float barWidth = width()*width()/(range+width());

    // If it is less than 16 pixels
    if(barWidth < 16)
        barWidth = 16;

    bar->setFixedWidth(barWidth);

    // Notify scroll change
    scrollChanged(x);

}

// Move the scroll position
void HScrollBar::moveX(int offset)
{
    x -=  offset;

    // Check if reched limits
    validateX();

    // Move the scroll bar
    int barPos = 0;
    if(range > 0)
        barPos = x*(width() - bar->width())/range;
    bar->move(barPos ,bar->pos().y());


    // Notify scroll change
    scrollChanged(x);
}

void HScrollBar::setX(int pos)
{
    x =  pos;

    // Check if reched limits
    validateX();

    // Move the scroll bar
    int barPos = 0;
    if(range > 0)
        barPos = x*(width() - bar->width())/range;
    bar->move(barPos ,bar->pos().y());


    // Notify scroll change
    scrollChanged(x);
}

// Filter some of the parent's events
bool HScrollBar::eventFilter(QObject *object, QEvent *event)
{

    if (object == parent())
    {

        if(event->type() == QEvent::Resize)
        {
            refreshPosition();
            return true;
        }
        else if(event->type() == QEvent::Wheel)
        {
            QWheelEvent *e = static_cast<QWheelEvent *>(event);
            moveX(e->pixelDelta().x());

            return true;
        }

    }


    return false;
}

void HScrollBar::setPosition(HScrollBar::Position pos)
{
    position = pos;
}

void HScrollBar::refreshPosition()
{
    if(position == Position::Bottom)
    {
        move(0,parentWidget()->height() - height());
        setFixedWidth(parentWidget()->width());
    }
    else
    {
        move(0,0);
        setFixedWidth(parentWidget()->width());
    }
}

void HScrollBar::validateX()
{
    // Check if reched limits
    if(x < 0)
        x = 0;

    else if( x > range)
        x = range;
}
