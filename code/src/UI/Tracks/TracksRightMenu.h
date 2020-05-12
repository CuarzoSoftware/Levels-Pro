#ifndef TRACKSRIGHTMENU_H
#define TRACKSRIGHTMENU_H

#include <UI/Tracks/TrackBand.h>
#include <Widgets/Ruler.h>
#include <Widgets/TimeRuler.h>
#include <Widgets/HScrollBar.h>
#include <QVBoxLayout>
#include <QFrame>

class TracksRightMenu : public QFrame
{
    Q_OBJECT
public:
    explicit TracksRightMenu();
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    TimeRuler *timeRuler = new TimeRuler();
    Ruler *tracksRuler = new Ruler(Ruler::RulerType::TracksRuler);

    QVBoxLayout *tracksLayout = new QVBoxLayout(tracksRuler);

    HScrollBar *hScrollBar = new HScrollBar(this);

    // Adds a new track
    void addTrack(TrackBand *newTrack);


signals:

};

#endif // TRACKSRIGHTMENU_H
