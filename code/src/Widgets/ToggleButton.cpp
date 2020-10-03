#include "ToggleButton.h"
#include <Global/Utils.h>
#include <QStyle>

/*!
    \class ToggleButton
    \brief The ToggleButton class...

    \inheaderfile Widgets/ToggleButton.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QWidget
*/

// Constructor I
ToggleButton::ToggleButton(
        Icon *icon,
        unsigned int layoutMargin,
        const QSize &fixedSize,
        const QColor activeBackgroundColor,
        const QColor inactiveBackgroundColor,
        const QColor activeIconColor,
        const QColor inactiveIconColor)
{
    // Allow background color
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna una altura fija
    setFixedSize(fixedSize);

    // Ajusta el layout
    layout->setMargin(layoutMargin);

    // Eventos del mouse
    setMouseTracking(true);

    // Crea el pixmap
    _icon = icon;

    // Asigna el icono al layout
    layout->addWidget(_icon);


    setInactiveBackgroundColor(inactiveBackgroundColor);
    setActiveBackgroundColor(activeBackgroundColor);
    setInactiveIconColor(inactiveIconColor);
    setActiveIconColor(activeIconColor);

}

// Constructor II
ToggleButton::ToggleButton(
        unsigned int verticalMargin,
        Icon *icon,
        const QColor activeBackgroundColor,
        const QColor inactiveBackgroundColor,
        const QColor activeIconColor,
        const QColor inactiveIconColor)
{
    // Allow background color
    setAttribute(Qt::WA_StyledBackground, true);

    // Ajusta el layout
    layout->setContentsMargins(8,verticalMargin,8,verticalMargin);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    // Eventos del mouse
    setMouseTracking(true);

    // Crea el pixmap
    _icon = icon;

    // Asigna el icono al layout
    layout->addWidget(_icon);

    setInactiveBackgroundColor(inactiveBackgroundColor);
    setActiveBackgroundColor(activeBackgroundColor);
    setInactiveIconColor(inactiveIconColor);
    setActiveIconColor(activeIconColor);

}


void ToggleButton::setActive(bool mode)
{
    _active = mode;

    if(mode)
    {
        _icon->setColor(_activeIconColor);
        setBackgroundColor(_activeBackgroundColor);
    }
    else
    {
        _icon->setColor(_inactiveIconColor);
        setBackgroundColor(_inactiveBackgroundColor);
    }

    changed(mode);
}

bool ToggleButton::isActive()
{
    return _active;
}

void ToggleButton::setActiveIconColor(const QColor &color)
{
    _activeIconColor = color;
    if(_active)
        _icon->setColor(_activeIconColor);
}

void ToggleButton::setActiveBackgroundColor(const QColor &color)
{
    _activeBackgroundColor = color;
    if(_active)
        setBackgroundColor(_activeBackgroundColor);
}

void ToggleButton::setInactiveIconColor(const QColor &color)
{
    _inactiveIconColor = color;
    if(!_active)
        _icon->setColor(_inactiveIconColor);
}

void ToggleButton::setInactiveBackgroundColor(const QColor &color)
{
    _inactiveBackgroundColor = color;
    if(!_active)
        setBackgroundColor(_inactiveBackgroundColor);
}

void ToggleButton::setBackgroundColor(const QColor &color)
{
    setStyleSheet("background-color:"+color.name()+";");
}


void ToggleButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QColor c = _inactiveBackgroundColor;
    if(_active)
        c = _activeBackgroundColor;

    setBackgroundColor(c.darker(110));
}

void ToggleButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setActive(!_active);
}
