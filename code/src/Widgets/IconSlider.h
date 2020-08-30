#ifndef ICONSLIDER_H
#define ICONSLIDER_H

#include <QWidget>
#include <Widgets/Icon.h>
#include <QTimer>

class IconSlider : public QWidget
{
    Q_OBJECT
public:
    explicit IconSlider(Icon *icn);
    QWidget *line = new QWidget(this);
    Icon *icon;
    Icon *handle = new Icon(":/res/svg/slider-handle.svg",QSize(10,10),QColor("#666666"));
    void setValue(float val);
    float getValue();
signals:
    void valueChanged(float val);
private:
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    float value = 0.0f;
    bool pressingHandle = false;
    int lastMousePos = 0.0f;


};

#endif // ICONSLIDER_H
