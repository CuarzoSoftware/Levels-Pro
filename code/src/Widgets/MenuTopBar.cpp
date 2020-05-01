#include "MenuTopBar.h"
#include <QVariant>

MenuTopBar::MenuTopBar()
{
    // Asigna una altura fija
    setFixedHeight(30);

    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Configura el layout
    horizontalLayout->setSpacing(0);
    horizontalLayout->setMargin(0);

    // Asigna la clase para los estilos
    setProperty("class","menuTopBar");
}
