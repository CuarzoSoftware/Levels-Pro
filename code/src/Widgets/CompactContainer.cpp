#include "CompactContainer.h"
#include <Global/Utils.h>

// Constructor
CompactContainer::CompactContainer(QWidget *parent)
{
    // Asigna el padre
    setParent(parent);

    // Ajusta el layout
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetFixedSize);
}

// Añade un widget al contenedor
void CompactContainer::addWidget(QWidget *widget)
{
    // Añade el widget al layout
    layout->addWidget(widget);

    // Arregla sus estilos
    fixWidgetStyles();
}

// Arregla los estilos de los widgets
void CompactContainer::fixWidgetStyles()
{
    // Si solo hay un widget
    if(layout->count() == 1)
    {

        Utils::removeWidgetClass(layout->itemAt(0)->widget(),"CompactContainerBegin");
        Utils::removeWidgetClass(layout->itemAt(0)->widget(),"CompactContainerMiddle");
        Utils::removeWidgetClass(layout->itemAt(0)->widget(),"CompactContainerLast");
        return;
    }

    // Si hay mas de un widget
    for(int i = 0; i < layout->count(); i++)
    {
        // Si es el primero
        if(i == 0)
        {
            Utils::addWidgetClass(layout->itemAt(i)->widget(),"CompactContainerBegin");
            Utils::removeWidgetClass(layout->itemAt(i)->widget(),"CompactContainerMiddle");
            Utils::removeWidgetClass(layout->itemAt(i)->widget(),"CompactContainerLast");
        }

        // Si es el último
        else if(i == layout->count() - 1)
        {
            Utils::removeWidgetClass(layout->itemAt(i)->widget(),"CompactContainerBegin");
            Utils::removeWidgetClass(layout->itemAt(i)->widget(),"CompactContainerMiddle");
            Utils::addWidgetClass(layout->itemAt(i)->widget(),"CompactContainerLast");
        }
        // Si está en la mitad
        else
        {
            Utils::removeWidgetClass(layout->itemAt(i)->widget(),"CompactContainerBegin");
            Utils::addWidgetClass(layout->itemAt(i)->widget(),"CompactContainerMiddle");
            Utils::removeWidgetClass(layout->itemAt(i)->widget(),"CompactContainerLast");
        }

    }
}
