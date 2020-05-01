#include "TopBar.h"
#include <QVariant>

TopBar::TopBar()
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","topBar");

    // Asigna una altura fija
    setFixedHeight(60);

    // Asigna el layout
    setLayout(layout);

    // Añade los botones al container izquierdo
    leftContainer->addWidget(libraryBtn);
    leftContainer->addWidget(inspectorBtn);
    leftContainer->addWidget(toolsBtn);

    // Añade los botones al container tools
    toolsContainer->addWidget(mixerBtn);
    toolsContainer->addWidget(editBtn);

    // Añade los botones al container playback
    playbackContainer->addWidget(rewindBtn);
    playbackContainer->addWidget(forwardBtn);
    playbackContainer->addWidget(backStopBtn);
    playbackContainer->addWidget(playBtn);
    playbackContainer->addWidget(recordBtn);
    playbackContainer->addWidget(loopBtn);

    // Añade los botones al container modes
    modesContainer->addWidget(replaceBtn);
    modesContainer->addWidget(lowLatencyBtn);
    modesContainer->addWidget(tunerBtn);
    modesContainer->addWidget(soloBtn);

    // Añade los botones al container tempo
    tempoContainer->addWidget(countBtn);
    tempoContainer->addWidget(metronomeBtn);

    // Añade los botones al container derecho
    rightContainer->addWidget(listsEditorBtn);
    rightContainer->addWidget(notesBtn);
    rightContainer->addWidget(loopsBtn);
    rightContainer->addWidget(mediaBtn);


    // Añade el container izquierdo al layout
    layout->addWidget(leftContainer);

    // Añade el container tools al layout
    layout->addWidget(toolsContainer);

    // Añade el container playback al layout
    layout->addWidget(playbackContainer);

    // Añade el container modes al layout
    layout->addWidget(modesContainer);

    // Añade el container tempo al layout
    layout->addWidget(tempoContainer);

    // Añade el container derecho al layout
    layout->addWidget(rightContainer);



}

