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
    void welcome();
    void run();

    // Time settings
    TimeSettings *timeSettings = new TimeSettings();

    // Audio
    void createTrack();

public slots:
    void zoomChanged(float value);


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
