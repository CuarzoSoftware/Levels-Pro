#include "MainMenu.h"
#include <QVariant>

/*!
    \class MainMenu
    \brief The MainMenu class...

    \inheaderfile Widgets/MainMenu.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QFrame
*/

MainMenu::MainMenu()
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","menu");

    // Configura el layout
    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(0);
}
