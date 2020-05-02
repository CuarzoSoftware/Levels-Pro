#include "TracksRuler.h"
#include <QVariant>
#include <QScrollBar>

TracksRuler::TracksRuler()
{
    // Removes scroll area border
    setProperty("class","scrollArea");

    // Sets the same height as the left menu topbar
    setFixedHeight(40);

    // Sets the central widget
    setWidget(scrollWidget);
    setWidgetResizable(true);

    // Set the rulers rect
    rulersLayout->setMargin(0);
    rulersLayout->setSpacing(0);
    rulersLayout->addWidget(topRuler);
    rulersLayout->addWidget(bottomRuler);
    topRuler->setFixedWidth(3000);
    topRuler->setFixedHeight(20);
    bottomRuler->setFixedWidth(3000);
    bottomRuler->setFixedHeight(20);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalScrollBar()->setSingleStep(1);

}
