#ifndef LINESRULER_H
#define LINESRULER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <Audio/TimeSettings.h>
#include <Widgets/ScrollBar.h>

class LinesRuler : public QWidget
{
    Q_OBJECT
public:

    // Constructor
    explicit LinesRuler();

    // Stores the scrollbar
    void setHorizontalScrollBar(ScrollBar *sb);

    // Stores the time settings
    void setTimeSettings(TimeSettings *settings);

    // Set zoom
    void setZoom(float _zoom);


public slots:
    // Listen to scroll changes
    void scrollChanged(int x);

private:
    // Gradient for the project end shadow
    QLinearGradient projectEndShadow = QLinearGradient();

    // The painter
    QPainter *painter = new QPainter();

    // Variables used for drawing
    uint i, x, w, h, beat, bar, div, tick, begin, end, skip, powSkip,innerOffset;

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

    // Pens
    QPen linePen = QPen(QColor("#BBBBBB"), 0.5);
    QPen borderPen = QPen(QColor("#BBBBBB"), 1.5);

    // Brushes
    QBrush backgroundBrush = QBrush(QColor("#FFFFFF"));

    // Horizontal scrollbar reference
    ScrollBar *hScrollBar;

    // Time settings reference
    TimeSettings *timeSettings;

    // Calculate the begin and end index for each drawing
    void getBeginAndEndIndex();

    // Calculate useful metrics and sets the scroll range
    void updateDimensions();

    // Draw lines
    void drawBars();
    void drawBeats();
    void drawDivitions();
    void drawTicks();
    void drawTicksWithoutDivitions();

    // Draw Project End
    void drawProjectEnd();

    // Draws the ruler
    void paintRuler();

protected:
   virtual void paintEvent(QPaintEvent *event) override;
private slots:
  void  projectLengthChanged();

};


#endif // LINESRULER_H
