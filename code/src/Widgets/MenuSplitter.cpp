#include "MenuSplitter.h"
#include <QVariant>

MenuSplitter::MenuSplitter(Qt::Orientation orientation)
{
    // Configura el splitter
    setOrientation(orientation);
    setHandleWidth(2);
    setProperty("class","menuSplitter");
}
