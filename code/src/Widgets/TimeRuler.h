#ifndef TIMERULER_H
#define TIMERULER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <Audio/TimeSettings.h>
#include <Widgets/ScrollBar.h>

class TimeRuler : public QWidget
{
    Q_OBJECT
public:

    // Constructor
    explicit TimeRuler();//HScrollBar *sb

    // Changes the background color
    void setBackgroundColor(const QColor &color);

    // Stores the time settings
    void setTimeSettings(TimeSettings *settings);

    // Set zoom
    void setZoom(float _zoom);

    // Set Horizontal Scroll Bar
    void setHorizontalScrollBar(ScrollBar *sb);

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

    // When changing project length
    float totalWidthOld = 0.0f;

    // Stores the current width in use ( In getBeginAndEndIndex() )
    float currentDimension = 1.f;

    // The begining X cord of the cursor while changing the project length
    int projectLengthDragBegin = 0;

    // Tells if the loop bar should be drawn
    bool isLoopBarVisible = false;

    // If the project length resizer is grabed
    bool changingProjectlength = false;

    // The painter
    QPainter *painter = new QPainter();

    // Light line color
    QColor barWhite = QColor("#AAAAAA");

    // Light text color
    QColor textWhite = QColor("#666666");

    // Pens
    QPen barPen = QPen(barWhite, 0.5);
    QPen borderPen = QPen(QColor("#AAAAAA"), 1.5);
    QPen textPen = QPen(textWhite);
    QPen loopPen = QPen(Qt::black,0.5);

    // Gradient for the project end shadow
    QLinearGradient projectEndShadow = QLinearGradient();

    // Handle pixmap
    QPixmap lengthHandle = QPixmap(":/res/png/length-handle.png");

    // Dashed background brush
    QBrush dashesBrush = QBrush(QPixmap(":/res/png/loop-texture.png"));

    // Brushes
    QBrush backgroundBrush = QBrush(QColor("#FFFFFF"));
    QBrush loopDisabledBrush = QBrush(QColor("#EEEEEE"));
    QBrush loopEnabledBrush = QBrush(QColor("#ffa733"));
    QBrush transparentBlack = QBrush(QColor(0,0,0,40));

    // Time settings reference
    TimeSettings *timeSettings;

    // Scroll bar reference
    ScrollBar *hScrollBar;

    // Timer for project length resize event
    QTimer *projectLengthResizeDelay = new QTimer(this);
    int resizeDirection = 0;


protected:
   virtual void paintEvent(QPaintEvent *event) override;
   virtual void resizeEvent(QResizeEvent* event) override;
   virtual void mouseMoveEvent(QMouseEvent *event) override;
   virtual void mousePressEvent(QMouseEvent *event) override;
   virtual void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void projectLengthResize();
    void projectLengthChanged();

};

#endif // TIMERULER_H
