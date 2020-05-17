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

    void drawBars();
    void drawBeats();
    void drawDivitions();
    void drawTicks();
    void drawTicksWithoutDivitions();
    void drawLoop();

    void getBeginAndEndIndex();

    uint i, x, w, h, beat, bar, div, tick, begin, end, skip, powSkip, loopBeginPos, loopEndPos, innerOffset;

    bool isLoopBarVisible = false;

    float zoom = 0.0001f;
    float offset = 0.f;
    float totalWidth = 100.f;
    float tickWidth = 100.f;
    float barWidth = 100.f;
    float beatWidth = 100.f;
    float divWidth = 100.f;
    float currentDimension = 1.f;

    QPainter *painter = new QPainter();

    QColor barWhite = QColor("#636363");
    QColor textWhite = QColor("#D4D4D4");

    QPen barPen = QPen(barWhite, 0.5);
    QPen borderPen = QPen(QColor("#171717"), 1.5);
    QPen textPen = QPen(textWhite);
    QPen loopPen = QPen(Qt::black,0.5);

    QBrush backgroundBrush = QBrush(QColor("#333333"));
    QBrush dashesBrush = QBrush(QPixmap(":/res/png/loop-texture.png"));
    QBrush loopDisabledBrush = QBrush(QColor("#4B4B4B"));
    QBrush loopEnabledBrush = QBrush(QColor("#BF9C2C"));

    TimeSettings *timeSettings;

    HScrollBar *hScrollBar;


protected:
   virtual void paintEvent(QPaintEvent *event) override;

};

#endif // TIMERULER_H
