#include "TracksMenu.h"

TracksMenu::TracksMenu()
{

    // Configura la barra superior
    setupTopBar();
}

void TracksMenu::setupTopBar()
{
    // Configura el layout del topbar
    topBar->horizontalLayout->setContentsMargins(8,3,8,3);
    topBar->horizontalLayout->setSpacing(8);

    // Añade los selects de edición al container
    editSelectsContainer->addWidget(editionSelect);
    editSelectsContainer->addWidget(functionsSelect);
    editSelectsContainer->addWidget(visualizationSelect);

    // Añade el container al topbar
    topBar->horizontalLayout->addWidget(editSelectsContainer);

    // Añade los botones de modo de edición al container
    editModesContainer->addWidget(automationBtn);
    editModesContainer->addWidget(flexBtn);

    // Añade el container al topbar
    topBar->horizontalLayout->addWidget(editModesContainer);

    // Añade el botón head tracker al topbar
    topBar->horizontalLayout->addWidget(headTrackerBtn);
    topBar->horizontalLayout->addStretch(1);

    // Selects de tipo de cursor
    cursorModesContainer->addWidget(leftBtnSelect);
    cursorModesContainer->addWidget(rightBtnSelect);
    topBar->horizontalLayout->addWidget(cursorModesContainer);
    topBar->horizontalLayout->addStretch(1);

    // Select de configuración
    topBar->horizontalLayout->addWidget(confSelect);

    // Zoom de waves
    topBar->horizontalLayout->addWidget(wavesZoomBtn);

    // Container de zoom
    zoomContainer->addWidget(verticalZoomBtn);
    zoomContainer->addWidget(horizontalZoomBtn);
    topBar->horizontalLayout->addWidget(zoomContainer);




}
