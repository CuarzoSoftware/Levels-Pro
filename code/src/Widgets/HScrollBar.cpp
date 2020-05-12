#include "HScrollBar.h"
#include <QVariant>
#include <QEvent>
#include <QWheelEvent>

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
    bar->move(50,3);

    // Refresh the position
    refreshPosition();

    // Listen to parent events ( Resize, scroll, etc )
    parent->installEventFilter(this);
}


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
            bar->move(bar->pos().x() + e->pixelDelta().x(),bar->pos().y());
            if(bar->pos().x() < 0)
                bar->move(0,bar->pos().y());

            if(bar->pos().x() + bar->width() > width())
                bar->move(width() - bar->width(),bar->pos().y());

            scrollChanged((float)bar->pos().x()/((float)(width() - bar->width())));
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
