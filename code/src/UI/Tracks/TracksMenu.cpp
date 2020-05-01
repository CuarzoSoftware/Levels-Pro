#include "TracksMenu.h"

TracksMenu::TracksMenu()
{
    // Añade el topbar
    verticalLayout->addWidget(topBar);

    horizontalSplitter->addWidget(leftMenu);
    horizontalSplitter->addWidget(rightMenu);
    horizontalSplitter->setHandleWidth(1);

    verticalLayout->addWidget(horizontalSplitter);

    // ELIMINAR DEPUES
    //verticalLayout->addStretch(1);
}

