#include "MainMenu.h"

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
