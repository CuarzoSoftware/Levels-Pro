#include "Core.h"
#include <QFontDatabase>
#include <QScrollBar>
#include <QtMath>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QRegularExpression>
#include <Global/Color.h>
#include <UI/Welcome/WelcomeWindow.h>


Core::Core(QApplication *_levels)
{
    // Stores the app reference
    levels = _levels;

    // Check if the settings and themes directory exist
    QDir settingsDir(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
    if(!settingsDir.exists())
        settingsDir.mkpath(".");
    if(!settingsDir.exists("./themes"))
        settingsDir.mkpath("./themes");


}

void Core::configure()
{
    timeSettings->setTimeSignature(32,4);
    timeSettings->setProjectLengthInTicks(960*4*100);

    // Loads default font
    setDefaultFontFamily();

    // Loads the default style
    loadDefaultStyle();
}

void Core::welcome()
{
    WelcomeWindow *welcomeWindow = new WelcomeWindow();
    welcomeWindow->show();
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



void Core::zoomChanged(float value)
{

    // Scroll zoom 0-1 with exponential curve
    float smoothedZoom = qPow(value,5);
    mainWindow->tracksMenu->rightMenu->timeRuler->setZoom(smoothedZoom);
    mainWindow->tracksMenu->rightMenu->linesRuler->setZoom(smoothedZoom);

}



// Load default styles
void Core::loadDefaultStyle()
{
    QFile File(":/res/styles/default.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    File.close();

    // Parse color variables
    int begin = StyleSheet.indexOf("<");
    int end = StyleSheet.indexOf(">",begin);

    while(begin != -1)
    {
        StyleSheet.replace(begin,end-begin+1,Color::theme.getString(StyleSheet.mid(begin+1,end-begin-1)));
        begin = StyleSheet.indexOf("<",begin);
        end = StyleSheet.indexOf(">",begin);
    }

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
