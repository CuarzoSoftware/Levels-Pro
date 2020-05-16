#ifndef TIMERULER_H
#define TIMERULER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <Audio/TimeSettings.h>
#include <Widgets/HScrollBar.h>

class TimeRuler : public QWidget
{
    Q_OBJECT
public:

    explicit TimeRuler(HScrollBar *sb);
    void setBackgroundColor(const QColor &color);
    void setTimeSettings(TimeSettings *settings);
    void setZoom(float _zoom);

public slots:
    void scrollChanged(int x);

private:
    void paintRuler();
    void updateDimensions();

    float zoom = 0.0001f;
    float offset = 0.f;
    float totalWidth = 100.f;
    float tickWidth = 100.f;
    float barWidth = 100.f;
    float beatWidth = 100.f;
    float divWidth = 100.f;

    QPen barPen = QPen(QColor("#636363"), 0.5);
    QPen borderPen = QPen(QColor("#171717"), 1.5);
    QPen textPen = QPen(QColor("#D4D4D4"));

    QBrush backgroundBrush = QBrush(QColor("#333333"));

    TimeSettings *timeSettings;

    HScrollBar *hScrollBar;


protected:
   virtual void paintEvent(QPaintEvent *event) override;

};

#endif // TIMERULER_H
