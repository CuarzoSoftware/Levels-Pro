#ifndef HSCROLLBAR_H
#define HSCROLLBAR_H

#include <QWidget>
#include <QTimer>

class HScrollBar : public QWidget
{
    Q_OBJECT
public:
    enum Position{Top,Bottom};
    explicit HScrollBar(QWidget *parent = nullptr, Position handlePosition = Position::Bottom);
    void setRange(int _range);
    void moveX(float offset);
    void setX(float pos);
    QWidget *bar = new QWidget(this);

protected slots:
    void elasticFix();

protected:
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    void setHandlePosition(Position handlePosition);
    void refreshPosition();
    void validateX();
    QTimer *elasticTimer = new QTimer(this);
    Position position;
    int range = 0;
    int previusDelta = 0;
    float x = 0;
    float elongation = 0.f;
    float elasticIndex = 0.f;
    bool scrollFinished = true;
    bool momentumBlocked = true;
    bool doingElasticScroll = true;



signals:
    void scrollChanged(int x);

};

#endif // HSCROLLBAR_H
