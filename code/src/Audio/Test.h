#ifndef TESTx_H
#define TESTx_H

#include <QObject>
#include <AudioToolbox/AudioToolbox.h>

class Test : public QObject
{
     Q_OBJECT
public slots:
    void run();
signals:
    void sendAU(void *au);
};

#endif // TEST_H
