#include "TracksScroll.h"
#include <QResizeEvent>

TracksScroll::TracksScroll(QWidget *scrollWidget)
{
    setProperty("class","scrollArea");
    setWidget(scrollWidget);
    setWidgetResizable(true);
}

void TracksScroll::resizeEvent(QResizeEvent *event)
{
    scrollResized(event->size().width(),event->size().height());
}
