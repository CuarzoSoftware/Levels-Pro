#include "MainToolBar.h"
#include <QVariant>

/*!
    \class MainToolBar
    \brief The MainToolBar class...

    \inheaderfile UI/MainWindow/MainToolBar.h
    \ingroup UI
    \inmodule UI

    \inherits QWidget
*/

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
