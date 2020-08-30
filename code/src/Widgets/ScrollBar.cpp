#include "ScrollBar.h"
#include <QEvent>

ScrollBar::ScrollBar(Qt::Orientation orientation, QWidget * parent = 0)
{
    QScrollBar::setOrientation(orientation);
    QScrollBar::setParent(parent);
}

void ScrollBar::setParent(QWidget *parent)
{
    QScrollBar::setParent(parent);
    parent->installEventFilter(this);
    updateDimensions();
}

void ScrollBar::updateDimensions()
{
    QSize s = parentWidget()->size();
    if(QScrollBar::orientation() == Qt::Vertical)
    {
        move(s.width()-15,0);
        resize(15,s.height());
    }
    else
    {
        move(0,s.height()-15);
        resize(s.width(),15);
    }
}

bool ScrollBar::eventFilter(QObject *object, QEvent *event)
{
    if(object == parent() && event->type() == QEvent::Resize)
    {
        updateDimensions();
    }
}


