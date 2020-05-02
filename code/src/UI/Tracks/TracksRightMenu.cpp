#include "TracksRightMenu.h"

TracksRightMenu::TracksRightMenu()
{

    // Allows background color
    setAttribute(Qt::WA_StyledBackground, true);

    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);

    verticalLayout->addWidget(ruler);
    verticalLayout->addStretch(1);
}
