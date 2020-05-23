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

    // Constructor
    explicit TimeRuler(HScrollBar *sb);

    // Changes the background color
    void setBackgroundColor(const QColor &color);

    // Stores the time settings
    void setTimeSettings(TimeSettings *settings);

    // Set zoom
    void setZoom(float _zoom);

public slots:
    // Listen to scroll changes
    void scrollChanged(int x);

private:
    // Draws the ruler
    void paintRuler();

    // Calculate useful metrics and sets the scroll range
    void updateDimensions();

    // Drawing methods
    void drawBars();
    void drawBeats();
    void drawDivitions();
    void drawTicks();
    void drawTicksWithoutDivitions();

    // Draws the loop bar
    void drawLoop();

    // Draws the project end
    void drawProjectLengthHandle();

    // Calculate the begin and end index for each drawing
    void getBeginAndEndIndex();

    // Variables used for drawing
    uint i, x, w, h, beat, bar, div, tick, begin, end, skip, powSkip, loopBeginPos, loopEndPos, innerOffset;

    // Stores the zoom value
    float zoom = 0.0001f;

    // The scroll x offset
    float offset = 0.f;

    // Widths in pixels, calculated in updateDimensions()
    float totalWidth = 100.f;
    float tickWidth = 100.f;
    float barWidth = 100.f;
    float beatWidth = 100.f;
    float divWidth = 100.f;

    // Stores the current width in use ( In getBeginAndEndIndex() )
    float currentDimension = 1.f;

    // Tells if the loop bar should be drawn
    bool isLoopBarVisible = false;

    // The painter
    QPainter *painter = new QPainter();

    // Light line color
    QColor barWhite = QColor("#636363");

    // Light text color
    QColor textWhite = QColor("#D4D4D4");

    // Pens
    QPen barPen = QPen(barWhite, 0.5);
    QPen borderPen = QPen(QColor("#171717"), 1.5);
    QPen textPen = QPen(textWhite);
    QPen loopPen = QPen(Qt::black,0.5);

    // Gradient for the project end shadow
    QLinearGradient projectEndShadow = QLinearGradient();

    // Handle pixmap
    QPixmap lengthHandle = QPixmap(":/res/png/length-handle.png");

    // Dashed background brush
    QBrush dashesBrush = QBrush(QPixmap(":/res/png/loop-texture.png"));

    // Brushes
    QBrush backgroundBrush = QBrush(QColor("#333333"));
    QBrush loopDisabledBrush = QBrush(QColor("#4B4B4B"));
    QBrush loopEnabledBrush = QBrush(QColor("#BF9C2C"));
    QBrush transparentBlack = QBrush(QColor(0,0,0,100));

    // Time settings reference
    TimeSettings *timeSettings;

    // Scroll bar reference
    HScrollBar *hScrollBar;


protected:
   // Qt paint event
   virtual void paintEvent(QPaintEvent *event) override;

};

#endif // TIMERULER_H
