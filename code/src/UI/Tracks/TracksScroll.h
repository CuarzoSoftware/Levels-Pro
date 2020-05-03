#ifndef TRACKSSCROLL_H
#define TRACKSSCROLL_H

#include <QScrollArea>

class TracksScroll : public QScrollArea
{
    Q_OBJECT
public:
    TracksScroll(QWidget *scrollWidget);
signals:
    void scrollResized(uint width,uint height);
protected:
    virtual void resizeEvent(QResizeEvent *event);
};

#endif // TRACKSSCROLL_H
