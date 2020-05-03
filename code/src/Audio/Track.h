#ifndef TRACK_H
#define TRACK_H

#include <UI/Tracks/TrackController.h>
#include <UI/Tracks/TrackBand.h>
#include <Audio/Region.h>

#include <QList>

class Track : public QObject
{
    Q_OBJECT
public:
    explicit Track();
    TrackController *controller = new TrackController();
    TrackBand *trackBand = new TrackBand();
    QList<Region*> trackRegions;

    uint height = 60;
signals:

};

#endif // TRACK_H
