#include "Core.h"
#include <QFontDatabase>
#include <QFile>
#include <QScrollBar>
#include <QtMath>



Core::Core(QApplication *_levels)
{
    // Stores the app reference
    levels = _levels;
}

void Core::configure()
{
    // Loads default font
    setDefaultFontFamily();

    // Loads the default style
    loadDefaultStyle();
}

void Core::run()
{
    // Creates the main window
    mainWindow = new MainWindow(this);
    tracksMenu = mainWindow->tracksMenu;

    // Set the track conroller scrollbar
    //tracksMenu->leftMenu->tracksScrollArea->setVerticalScrollBar(tracksMenu->rightMenu->tracksScroll->verticalScrollBar());
    //tracksMenu->rightMenu->ruler->setHorizontalScrollBar(tracksMenu->rightMenu->tracksScroll->horizontalScrollBar());

    // Asignt time settings to other components
    tracksMenu->rightMenu->timeRuler->setTimeSettings(timeSettings);


    connect(tracksMenu->topBar->slider,&QSlider::valueChanged,this,&Core::zoomChanged);
    //connect(tracksMenu->rightMenu->tracksScroll->horizontalScrollBar(),&QScrollBar::valueChanged,this,&Core::horizontalScrollChanged);
    //connect(tracksMenu->rightMenu->tracksScroll->verticalScrollBar(),&QScrollBar::valueChanged,this,&Core::verticalScrollChanged);


    for(int i = 0; i < 50 ; i++)
        createTrack();
    mainWindow->show();
}

void Core::createTrack()
{
    Track *newTrack = new Track();
    tracksList.prepend(newTrack);

    tracksMenu->leftMenu->addTrack(newTrack->controller);
    tracksMenu->rightMenu->addTrack(newTrack->trackBand);
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

void Core::zoomChanged(int value)
{

    float normal = qPow((float)value * 0.0000001f,12);
    tracksMenu->rightMenu->timeRuler->setZoom(normal);
    /*
    float scrollWidth = (float)tracksMenu->rightMenu->tracksScroll->width();
    float widgetsWidth = scrollWidth + (50000.f)*normal;
    float ticksPerBar = beatsNumber*ticksPerWholeNote/noteValue;
    float barWidth = widgetsWidth/projectLenght/ticksPerBar;

    tracksMenu->rightMenu->ruler->topRuler->setBarSize(barWidth);

    tracksMenu->rightMenu->ruler->bottomRuler->setBarSize(barWidth);
    tracksMenu->rightMenu->tracksRuler->setBarSize(barWidth);


    tracksMenu->rightMenu->ruler->topRuler->setFixedWidth(widgetsWidth);

    tracksMenu->rightMenu->ruler->bottomRuler->setFixedWidth(widgetsWidth);
    tracksMenu->rightMenu->tracksRuler->setFixedWidth(widgetsWidth);
    */

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
    QFile File(":/res/styles/widgets.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    File.close();

    File.setFileName(":/res/styles/tracks.qss");
    File.open(QFile::ReadOnly);
    StyleSheet.append(QLatin1String(File.readAll()));
    File.close();

    levels->setStyleSheet(StyleSheet);
}

void Core::setDefaultFontFamily()
{
    int id = QFontDatabase::addApplicationFont(":res/fonts/HelveticaNeue.ttc");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    QApplication::setFont(font);
}
