#include "MenuSplitter.h"

MenuSplitter::MenuSplitter(Qt::Orientation orientation)
{
    // Configura el splitter
    setOrientation(orientation);
    setHandleWidth(2);
    setProperty("class","menuSplitter");
}
