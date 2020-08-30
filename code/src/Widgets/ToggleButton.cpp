#include "ToggleButton.h"
#include <Global/Utils.h>
#include <QVariant>

/*!
    \class ToggleButton
    \brief The ToggleButton class...

    \inheaderfile Widgets/ToggleButton.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QWidget
*/

// Constructor I
ToggleButton::ToggleButton(Icon *icon, unsigned int layoutMargin, const QSize &fixedSize)
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","toggleButton");

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

    // Obtiene el color de icono por defecto
    defaultIconColor = _icon->getColor();
}

// Constructor II
ToggleButton::ToggleButton(unsigned int verticalMargin, Icon *icon, const QString &extraClass)
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","toggleButton "+extraClass);

    // Ajusta el layout
    layout->setContentsMargins(8,verticalMargin,8,verticalMargin);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    // Eventos del mouse
    setMouseTracking(true);

    // Crea el pixmap
    _icon = icon;

    // Asigna el icono al layout
    layout->addWidget(_icon);

    // Obtiene el color de icono por defecto
    defaultIconColor = _icon->getColor();
}


void ToggleButton::setActive(bool mode)
{
    _active = mode;

    if(mode)
    {
        Utils::addWidgetClass(this,"active");
        _icon->setColor(activeIconColor);
    }
    else
    {
        Utils::removeWidgetClass(this,"active");
        _icon->setColor(defaultIconColor);
    }

    changed(mode);
}

bool ToggleButton::isActive()
{
    return _active;
}

void ToggleButton::setActiveIconColor(const QColor &color)
{
    activeIconColor = color;
}


void ToggleButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    Utils::removeWidgetClass(this,"active");
    Utils::addWidgetClass(this,"pressing");
    _icon->setColor(activeIconColor);
}

void ToggleButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setActive(!_active);
    Utils::removeWidgetClass(this,"pressing");
}
