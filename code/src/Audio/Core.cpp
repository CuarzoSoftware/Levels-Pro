#include "Core.h"
#include <QFontDatabase>
#include <QFile>
#include <QScrollBar>
#include <QtMath>

// Remove after
#include <QDebug>


/*!
    \class Core
    \brief The Core class...

    \inheaderfile Audio/Core.h
    \ingroup Audio
    \inmodule Audio

    \inherits QObject
*/

Core::Core(QApplication *_levels)
{
    // Stores the app reference
    levels = _levels;

}

void Core::configure()
{
    timeSettings->setTimeSignature(4,4);
    timeSettings->setProjectLengthInTicks(960*4*100);

    // Loads default font
    setDefaultFontFamily();

    // Loads the default style
    loadDefaultStyle();
}

void Core::run()
{
    // Creates the main window
    mainWindow = new MainWindow(this);

    // Asignt time settings to other components
    mainWindow->tracksMenu->rightMenu->timeRuler->setTimeSettings(timeSettings);
    mainWindow->tracksMenu->rightMenu->linesRuler->setTimeSettings(timeSettings);

    // Listen to zoom changes from the zoom slider
    connect(mainWindow->tracksMenu->topBar->hZoomSlider,&IconSlider::valueChanged,this,&Core::zoomChanged);


    for(int i = 0; i < 50 ; i++)
        createTrack();

    mainWindow->show();
    mainWindow->tracksMenu->topBar->hZoomSlider->setValue(0);

}

void Core::createTrack()
{
    Track *newTrack = new Track();
    tracksList.prepend(newTrack);

    mainWindow->tracksMenu->leftMenu->addTrack(newTrack->controller);
    //mainWindow->tracksMenu->rightMenu->addTrack(newTrack->trackBand);
}

void Core::setHorizontalZoom(float zoom)
{
    /*
    if(zoom > 1.0f) horizontalZoom = 1.0f;
    else if(zoom < 0.0f) horizontalZoom = 0.0f;
    else horizontalZoom = zoom;

    //float rulerWidth = tracksRightMenu->width() + 10.f * tracksRightMenu->width() * horizontalZoom;
    */
}

void Core::zoomChanged(float value)
{

    // Scroll zoom 0-1 with exponential curve
    float smoothedZoom = qPow(value,5);
    mainWindow->tracksMenu->rightMenu->timeRuler->setZoom(smoothedZoom);
    mainWindow->tracksMenu->rightMenu->linesRuler->setZoom(smoothedZoom);

}



void Core::verticalScrollChanged(int pos)
{
    //tracksMenu->rightMenu->tracksRuler->move(tracksMenu->rightMenu->tracksRuler->x(),pos);
}

void Core::horizontalScrollChanged(int pos)
{
    /*
    tracksMenu->rightMenu->tracksRuler->setXScroll(pos);
    tracksMenu->rightMenu->ruler->topRuler->setXScroll(pos);
    tracksMenu->rightMenu->ruler->bottomRuler->setXScroll(pos);

    tracksMenu->rightMenu->tracksRuler->move(pos,tracksMenu->rightMenu->tracksRuler->y());
    tracksMenu->rightMenu->ruler->topRuler->move(pos,tracksMenu->rightMenu->ruler->topRuler->y());
    tracksMenu->rightMenu->ruler->bottomRuler->move(pos,tracksMenu->rightMenu->ruler->bottomRuler->y());
    */
}

// Carga los estilos por defecto
void Core::loadDefaultStyle()
{
    QFile File(QCoreApplication::applicationDirPath()+"/../Resources/theme.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    File.close();

    levels->setStyleSheet(StyleSheet);
}

void Core::setDefaultFontFamily()
{
    QFontDatabase::addApplicationFont(":res/fonts/SF-Pro-Display-Bold.otf");
    QFontDatabase::addApplicationFont(":res/fonts/SF-Pro-Display-Medium.otf");
    QFontDatabase::addApplicationFont(":res/fonts/SF-Pro-Display-Light.otf");


    int id = QFontDatabase::addApplicationFont(":res/fonts/SF-Pro-Display-Regular.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    QApplication::setFont(font);
}
