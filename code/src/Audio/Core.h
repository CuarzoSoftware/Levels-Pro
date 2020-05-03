#ifndef CORE_H
#define CORE_H

#include <UI/MainWindow/MainWindow.h>
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

    // Project Variables
    uint sampleRate = 44100;
    float bpm = 120.0f;
    float projectLenght = 20.0; // In bars
    uint beatsNumber = 4;
    uint noteValue = 4;

    // UI
    float horizontalZoom = 0.0f;



    // Audio
    void createTrack();
    void setHorizontalZoom(float zoom);

public slots:
    void zoomChanged(int value);
    void tracksScrollResized(uint width,uint height);
    void verticalScrollChanged(int pos);
    void horizontalScrollChanged(int pos);


private:

    // App reference
    QApplication *levels;

    // UI references
    MainWindow *mainWindow;
    TracksMenu *tracksMenu;


    // Audio
    QList<Track*>tracksList;

    // Configuration methods
    void setDefaultFontFamily();
    void loadDefaultStyle();


signals:

};

#endif // CORE_H
