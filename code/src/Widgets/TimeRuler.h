#ifndef TIMERULER_H
#define TIMERULER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <Audio/TimeSettings.h>

class TimeRuler : public QWidget
{
    Q_OBJECT
public:

    explicit TimeRuler();
    void setBackgroundColor(const QColor &color);
    void setTimeSettings(TimeSettings *settings);
    void setZoom(float _zoom);

public slots:
    void scrollChanged(float x);

private:
    void paintRuler();

    float zoom = 0.0001f;
    float offset = 0.f;

    QPen barPen = QPen(QColor("#636363"), 0.5);
    QPen borderPen = QPen(QColor("#171717"), 1.5);
    QPen textPen = QPen(QColor("#D4D4D4"));

    QBrush backgroundBrush = QBrush(QColor("#333333"));

    TimeSettings *timeSettings;


protected:
   virtual void paintEvent(QPaintEvent *event) override;

};

#endif // TIMERULER_H
