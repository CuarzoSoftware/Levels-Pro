#ifndef TRACKSRIGHTMENU_H
#define TRACKSRIGHTMENU_H

#include <QScrollArea>
#include <QVBoxLayout>

class TracksRightMenu : public QFrame
{
    Q_OBJECT
public:
    explicit TracksRightMenu();
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

signals:

};

#endif // TRACKSRIGHTMENU_H
