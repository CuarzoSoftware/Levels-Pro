#include "TracksMenu.h"
#include <Audio/Core.h>
#include <QWheelEvent>

TracksMenu::TracksMenu(Core *_core)
{
    setMouseTracking(true);
    core = _core;

    // Añade el topbar
    verticalLayout->addWidget(topBar);

    horizontalSplitter->addWidget(leftMenu);
    horizontalSplitter->addWidget(rightMenu);
    horizontalSplitter->setHandleWidth(1);

    verticalLayout->addWidget(horizontalSplitter);

    // ELIMINAR DEPUES
    //verticalLayout->addStretch(1);
}

void TracksMenu::wheelEvent(QWheelEvent *event)
{
   //core->setHorizontalZoom( core->horizontalZoom + (float)event->pixelDelta().x()*0.001f);
}

