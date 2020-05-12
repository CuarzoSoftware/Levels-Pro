#include "TracksMenuTopBar.h"

TracksMenuTopBar::TracksMenuTopBar()
{    
    // Configura el layout del topbar
    horizontalLayout->setContentsMargins(8,3,8,3);
    horizontalLayout->setSpacing(8);

    // Añade los selects de edición al container
    editSelectsContainer->addWidget(editionSelect);
    editSelectsContainer->addWidget(functionsSelect);
    editSelectsContainer->addWidget(visualizationSelect);

    // Añade el container al topbar
    horizontalLayout->addWidget(editSelectsContainer);

    // Añade los botones de modo de edición al container
    editModesContainer->addWidget(automationBtn);
    editModesContainer->addWidget(flexBtn);

    // Añade el container al topbar
    horizontalLayout->addWidget(editModesContainer);

    // Añade el botón head tracker al topbar
    horizontalLayout->addWidget(headTrackerBtn);
    horizontalLayout->addStretch(1);

    // Selects de tipo de cursor
    cursorModesContainer->addWidget(leftBtnSelect);
    cursorModesContainer->addWidget(rightBtnSelect);
    horizontalLayout->addWidget(cursorModesContainer);
    horizontalLayout->addStretch(1);

    // Select de configuración
    horizontalLayout->addWidget(confSelect);

    // Zoom de waves
    horizontalLayout->addWidget(wavesZoomBtn);

    // Container de zoom
    zoomContainer->addWidget(verticalZoomBtn);
    zoomContainer->addWidget(horizontalZoomBtn);
    horizontalLayout->addWidget(zoomContainer);

    slider->setTickInterval(1);
    slider->setRange(0,10000000);

    horizontalLayout->addWidget(slider);
}
