#include "IconSlider.h"
#include <QVariant>
#include <QEvent>
#include <QtMath>

/*!
    \class IconSlider
    \brief The IconSlider class...

    \inheaderfile Widgets/IconSlider.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QWidget
*/


IconSlider::IconSlider(Icon *icn)
{
    // Allows background color
    setAttribute(Qt::WA_StyledBackground, true);

    // Style class
    setProperty("class","iconSlider");

    icon = icn;
    icon->setParent(this);
    icon->move(5,5);

    handle->setParent(this);
    handle->move(24,6);
    handle->installEventFilter(this);

    line->setAttribute(Qt::WA_StyledBackground, true);
    line->setProperty("class","line");
    line->setFixedSize(48,3);
    line->move(24,11);


    setFixedSize(80,26);
}

void IconSlider::setValue(float val)
{
    if(val < 0)
        value = 0;
    else if(val > 1)
        value = 1;
    else
        value = val;
    valueChanged(value);
    handle->move(line->x() + (line->width()-handle->width())*value,handle->y());
}

float IconSlider::getValue()
{
    return value;
}

bool IconSlider::eventFilter(QObject *object, QEvent *event)
{
    if(object == handle)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            handle->setColor(QColor("#444444"));
            pressingHandle = true;
            lastMousePos = QCursor::pos().x();
        }
        if(event->type() == QEvent::MouseButtonRelease)
        {
            handle->setColor(QColor("#666666"));
            pressingHandle = false;
        }
        if(pressingHandle && event->type() == QEvent::MouseMove)
        {

            float delta = (QCursor::pos().x()-lastMousePos)*0.005;

            if(lastMousePos != QCursor::pos().x())
                setValue(value + delta);

            lastMousePos = QCursor::pos().x();
        }
    }
}


