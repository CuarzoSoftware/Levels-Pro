#ifndef CORE_H
#define CORE_H

#include <UI/MainWindow/MainWindow.h>
#include <Audio/TimeSettings.h>
#include <Audio/Track.h>
#include <QApplication>
#include <QList>

class Core : public QObject
{
    Q_OBJECT
public:
    Core(QApplication *_levels);

    // Initial methods
    void configure();
    void run();

    // Time settings
    TimeSettings *timeSettings = new TimeSettings();

    // Audio
    void createTrack();
    void setHorizontalZoom(float zoom);

public slots:
    void zoomChanged(float value);
    void verticalScrollChanged(int pos);
    void horizontalScrollChanged(int pos);


private:

    // App reference
    QApplication *levels;

    // UI references
    MainWindow *mainWindow;


    // Audio
    QList<Track*>tracksList;

    // Configuration methods
    void setDefaultFontFamily();
    void loadDefaultStyle();


signals:

};

#endif // CORE_H
