#include "MainMenu.h"

MainMenu::MainMenu()
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","menu");

    // Configura el layout vertical
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);

    // Añade el TopBar al layout
    verticalLayout->addWidget(topBar);
    verticalLayout->addStretch(1);

}
