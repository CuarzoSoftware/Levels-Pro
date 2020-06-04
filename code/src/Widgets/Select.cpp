#include "Select.h"
#include <QVariant>

/*!
    \class Select
    \brief The Select class...

    \inheaderfile Widgets/Select.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QWidget
*/

Select::Select(const QString &title, uint verticalMargin)
{
    // Asigna margin vertical
    horizontalLayout->setContentsMargins(8,verticalMargin,8,verticalMargin);

    // Crea el texto
    label = new QLabel(title);

    // Lo añade al layout
    horizontalLayout->addWidget(label);

    // Configuración
    setup();
}

Select::Select(Icon *displayIcon, uint verticalMargin)
{
    // Asigna margin vertical
    horizontalLayout->setContentsMargins(8,verticalMargin,8,verticalMargin);

    // Almacena el ícono
    icon = displayIcon;

    // Lo añade al layout
    horizontalLayout->addWidget(icon);

    // Configuración
    setup();
}

void Select::setup()
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);

    setProperty("class","select");
    downArrow->setFixedSize(8,8);
    horizontalLayout->addWidget(downArrow);
    horizontalLayout->setSpacing(6);
}
