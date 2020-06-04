#include "HScrollBar.h"
#include <QVariant>
#include <QEvent>
#include <QWheelEvent>
#include <QtMath>
#include <QDebug>


/*!
    \class HScrollBar
    \brief The HScrollBar class simulates the native Apple kinetic scrolling.
    \since 1.0

    \inheaderfile Widgets/HScrollBar.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QWidget
*/

/*!
    \enum HScrollBar::Position

    This enum type specifies a the scrollbar position:

    \value Top
           Displays the scroll bar at the top of the parent.
    \value Bottom
           Displays the scroll bar at the bottom of the parent.

*/

/*!
    The HScrollBar class constructor. It requires a parent \l{QWidget}, and the handle position is opcional.
    By position by default is the bottom.
*/
HScrollBar::HScrollBar(QWidget *parent, Position handlePosition)
{
    // Assign parent
    setParent(parent);

    // Sets the position
    setHandlePosition(handlePosition);

    // Allows background color
    setAttribute(Qt::WA_StyledBackground, true);

    // Style class
    setProperty("class","scrollBar");

    // Sets fixed height
    setFixedHeight(14);
    bar->setFixedSize(200,8);
    bar->move(0,3);

    // Elastic updater
    elasticTimer->setInterval(0);
    connect(elasticTimer,&QTimer::timeout,this,&HScrollBar::elasticFix);

    // Refresh the position
    refreshPosition();

    // Listen to parent events ( Resize, scroll, etc )
    parent->installEventFilter(this);
}

/*!
    Sets the scroll range in pixels (the inner size of the target Widget).
*/
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

/*!
    Changes the scroll position by a given offset in pixels.
*/
void HScrollBar::moveX(float offset)
{
    x -=  offset;

    // Check if reched limits
    //validateX();

    // Move the scroll bar
    int barPos = 0;
    if(range > 0)
        barPos = x*(width() - bar->width())/range;
    bar->move(barPos ,bar->pos().y());


    // Notify scroll change
    scrollChanged(x);
}

/*!
    Changes the scroll position in pixels.
*/
void HScrollBar::setX(float pos)
{
    x =  pos;

    // Check if reched limits
    //validateX();

    // Move the scroll bar
    int barPos = 0;
    if(range > 0)
        barPos = x*(width() - bar->width())/range;
    bar->move(barPos ,bar->pos().y());


    // Notify scroll change
    scrollChanged(x);
}

/*!
    Internally animates the scrolling when it overpass the range limits.
*/
void HScrollBar::elasticFix()
{
    if(scrollFinished)
    {
        if(elasticIndex > 0.f)
        {
            if(x < 0)
            {
                elasticIndex-=0.01;
                setX( -qPow(elasticIndex,2)*elongation);
                elasticTimer->start();
            }
            else if( x > range)
            {
                elasticIndex-=0.01;
                setX( range + qPow(elasticIndex,2)*elongation);
                elasticTimer->start();
            }

        }
    }
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

            float delta = (float)e->pixelDelta().x();

            // Mouse Wheel
            if(e->phase() == Qt::NoScrollPhase)
            {
                scrollFinished = true;

                if( x - delta < 0)
                {
                    setX(0);
                    return true;
                }

                if( x - delta > range)
                {
                    setX(range);
                    return true;
                }

                moveX(delta);

                return true;
            }
            else if(e->phase() == Qt::ScrollUpdate )
            {

                scrollFinished = false;

                if( x < -2.f )
                {
                    delta = delta/(-x/2.f);
                }
                else if( x > range + 2.f )
                {
                    delta = delta/(x/2.f);
                }

                moveX(delta);

            }
            else if(e->phase() == Qt::ScrollMomentum)
            {
                if(scrollFinished)
                    return true;

                if(x < 0)
                {
                    doingElasticScroll = true;
                    scrollFinished = true;
                    elongation = qAbs(x);
                    elasticIndex = 1;
                    elasticFix();
                    return true;
                }
                else if(x > range)
                {
                    doingElasticScroll = true;
                    scrollFinished = true;
                    elongation = x - range;
                    elasticIndex = 1;
                    elasticFix();
                    return true;
                }

                moveX(delta);

            }
            else if(e->phase() == Qt::ScrollBegin)
            {
                scrollFinished = false;
                momentumBlocked = false;
            }
            else if(e->phase() == Qt::ScrollEnd)
            {
                scrollFinished  = true;

                if( x < 0)
                {
                    doingElasticScroll = true;
                    elongation = qAbs(x);
                    elasticIndex = 1;
                    elasticFix();
                }else if(x > range)
                {
                    doingElasticScroll = true;
                    elongation = x - range;
                    elasticIndex = 1;
                    elasticFix();
                }

            }

            return true;
        }

    }


    return false;
}

void HScrollBar::setHandlePosition(HScrollBar::Position handlePosition)
{
    position = handlePosition;
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
        x = -sqrt(-x);

    else if( x > range)
        x = range;
}

