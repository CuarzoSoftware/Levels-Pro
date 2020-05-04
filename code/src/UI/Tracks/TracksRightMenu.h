#ifndef TRACKSRIGHTMENU_H
#define TRACKSRIGHTMENU_H

#include <UI/Tracks/TracksRuler.h>
#include <UI/Tracks/TrackBand.h>
#include <QVBoxLayout>
#include <QScrollArea>
#include <Widgets/Ruler.h>

class TracksRightMenu : public QFrame
{
    Q_OBJECT
public:
    explicit TracksRightMenu();
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    TracksRuler *ruler = new TracksRuler();
    QScrollArea *tracksScroll = new QScrollArea();
    Ruler *tracksRuler = new Ruler(Ruler::RulerType::TracksRuler);

    QVBoxLayout *tracksLayout = new QVBoxLayout(tracksRuler);

    // Adds a new track
    void addTrack(TrackBand *newTrack);

signals:

};

#endif // TRACKSRIGHTMENU_H
