#ifndef TRACKSRIGHTMENU_H
#define TRACKSRIGHTMENU_H

#include <UI/Tracks/TrackBand.h>
#include <UI/Tracks/TracksView.h>
#include <Widgets/LinesRuler.h>
#include <Widgets/TimeRuler.h>
#include <Widgets/ScrollBar.h>
#include <QVBoxLayout>
#include <QFrame>

class TracksRightMenu : public QFrame
{
    Q_OBJECT
public:
    explicit TracksRightMenu();

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    TracksView *tracksView = new TracksView(this);
    TimeRuler *timeRuler = new TimeRuler();
    LinesRuler *linesRuler = new LinesRuler();

    //QVBoxLayout *tracksLayout = new QVBoxLayout(tracksRuler);



    // Adds a new track
    void addTrack(TrackBand *newTrack);


signals:

};

#endif // TRACKSRIGHTMENU_H
