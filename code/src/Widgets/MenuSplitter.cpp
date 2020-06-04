#include "MenuSplitter.h"
#include <QVariant>

/*!
    \class MenuSplitter
    \brief The MenuSplitter class...

    \inheaderfile Widgets/MenuSplitter.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QSplitter
*/

MenuSplitter::MenuSplitter(Qt::Orientation orientation)
{
    // Configura el splitter
    setOrientation(orientation);
    setHandleWidth(2);
    setProperty("class","menuSplitter");
}
