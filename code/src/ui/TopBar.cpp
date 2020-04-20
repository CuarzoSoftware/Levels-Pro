#include "TopBar.h"

TopBar::TopBar()
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","topBar");

    // Asigna una altura fija
    setFixedHeight(60);

    // Asigna el layout
    setLayout(layout);

    layout->addWidget(new ToggleButton(":/res/svg/open-box.svg"));
}
