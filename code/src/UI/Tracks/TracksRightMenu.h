#ifndef TRACKSRIGHTMENU_H
#define TRACKSRIGHTMENU_H

#include <UI/Tracks/TracksRuler.h>
#include <UI/Tracks/TrackBand.h>
#include <QVBoxLayout>
#include <UI/Tracks/TracksScroll.h>
#include <Widgets/Ruler.h>

class TracksRightMenu : public QFrame
{
    Q_OBJECT
public:
    explicit TracksRightMenu();
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    TracksRuler *ruler = new TracksRuler();
    QWidget *scrollWidget = new QWidget();
    TracksScroll *tracksScroll = new TracksScroll(scrollWidget);
    Ruler *tracksRuler = new Ruler();
    QVBoxLayout *tracksLayout = new QVBoxLayout(scrollWidget);

    // Adds a new track
    void addTrack(TrackBand *newTrack);

signals:

};

#endif // TRACKSRIGHTMENU_H
