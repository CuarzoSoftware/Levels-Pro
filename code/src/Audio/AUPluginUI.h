#ifndef AUDIOUNITUI_H
#define AUDIOUNITUI_H

#include <QObject>
#include <AudioToolBox/AudioToolbox.h>
#include <QMacCocoaViewContainer>
#include <AudioToolbox/AUCocoaUIView.h>
#include <QDebug>
#include <QSizePolicy>
#include <QWindow>
#include <QGuiApplication>


class AudioUnitWrap : public QObject
{
    Q_OBJECT
public:
    explicit AudioUnitWrap();
    QMacCocoaViewContainer *viewCont;
    NSView *view;
    float req_width = 0;
    float req_height = 0;
    bool resizable = false;
    bool in_live_resize = false;
    QWidget *topWidget = new QWidget();
    QWidget *childWidget = new QWidget(topWidget);



public slots:
    void getAudioUnit(void *un);
};

#endif // AUDIOUNITUI_H
