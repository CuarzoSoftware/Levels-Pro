#ifndef TRACKSRIGHTMENU_H
#define TRACKSRIGHTMENU_H

#include <UI/Tracks/TracksRuler.h>
#include <QVBoxLayout>

class TracksRightMenu : public QFrame
{
    Q_OBJECT
public:
    explicit TracksRightMenu();
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    TracksRuler *ruler = new TracksRuler();

signals:

};

#endif // TRACKSRIGHTMENU_H
