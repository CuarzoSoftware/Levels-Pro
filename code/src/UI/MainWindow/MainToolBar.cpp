#include "MainToolBar.h"
#include <QVariant>

MainToolBar::MainToolBar()
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","mainToolBar");

    // Asigna una altura fija
    setFixedHeight(50);

    // Lo esconde inicialmente
    hide();
}
