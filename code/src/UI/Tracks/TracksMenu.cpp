#include "TracksMenu.h"
#include <Global/Utils.h>
#include <Audio/Core.h>
#include <QWheelEvent>
#include <QNativeGestureEvent>


/*!
    \class TracksMenu
    \brief The TracksMenu class...

    \inheaderfile UI/Tracks/TracksMenu.h
    \ingroup UI
    \inmodule UI

    \inherits MainMenu
*/


TracksMenu::TracksMenu(Core *_core)
{
    setMouseTracking(true);
    core = _core;

    // Añade el topbar
    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(0);
    verticalLayout->addWidget(topBar);

    Utils::addWidgetClass(horizontalSplitter,"tracksMenuSplitter");
    horizontalSplitter->addWidget(leftMenu);
    horizontalSplitter->addWidget(rightMenu);
    horizontalSplitter->setHandleWidth(1);


    verticalLayout->addWidget(horizontalSplitter);

    // Replaces the tracks list scrollbar
    leftMenu->tracksScrollArea->setVerticalScrollBar(verticalScrollBar);
    verticalScrollBar->setParent(rightMenu->tracksView);
    horizontalScrollBar->setParent(rightMenu->tracksView);
    rightMenu->timeRuler->setHorizontalScrollBar(horizontalScrollBar);
    installEventFilter(this);

}

void TracksMenu::wheelEvent(QWheelEvent *event)
{
   //core->setHorizontalZoom( core->horizontalZoom + (float)event->pixelDelta().x()*0.001f);
   horizontalScrollBar->setValue(horizontalScrollBar->value() - event->pixelDelta().x());
   verticalScrollBar->setValue(verticalScrollBar->value() - event->pixelDelta().y());
}
#include <QDebug>
bool TracksMenu::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::NativeGesture)
    {
        QNativeGestureEvent *gesture = static_cast<QNativeGestureEvent*>(event);
        if(gesture->gestureType() == Qt::ZoomNativeGesture)
        {
            topBar->hZoomSlider->setValue(topBar->hZoomSlider->getValue() + gesture->value());
        }
            //core->setHorizontalZoom( core->horizontalZoom + (float)event->pixelDelta().x()*0.001f)
    }
}

