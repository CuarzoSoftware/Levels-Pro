#ifndef RULER_H
#define RULER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>

class Ruler : public QWidget
{
    Q_OBJECT
public:
    enum RulerType {NumberRuler,MarksRuler,TracksRuler};

    explicit Ruler(RulerType type = RulerType::TracksRuler);
    void setBackgroundColor(const QColor &color);
    void setBarSize(uint barSizePixels);
    void setBeatsPerBar(uint beats);


private:
    void numberRulerPaint();
    void marksRulerPaint();
    void tracksRulerPaint();

    QColor backgroundColor = QColor("#333333");
    QColor barColor = QColor("#636363");
    QColor beatColor = QColor("#636363");

    QPen barPen = QPen(QColor("#636363"), 0.5);
    QPen beatPen = QPen(QColor("#606060"), 0.5);
    QPen borderPen = QPen(QColor("#171717"), 1.5);
    QPen textPen = QPen(QColor("#D4D4D4"));

    QBrush backgroundBrush = QBrush(QColor("#333333"));
    RulerType rulerType;

    uint barSize = 60;
    uint beatsPerBar = 4;


protected:
   virtual void paintEvent(QPaintEvent *event) override;

};

#endif // RULER_H
