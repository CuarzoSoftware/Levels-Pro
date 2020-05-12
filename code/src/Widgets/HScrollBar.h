#ifndef HSCROLLBAR_H
#define HSCROLLBAR_H

#include <QWidget>

class HScrollBar : public QWidget
{
    Q_OBJECT
public:
    enum Position{Top,Bottom};
    explicit HScrollBar(QWidget *parent = nullptr, Position pos = Position::Bottom);
    QWidget *bar = new QWidget(this);

private:
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    void setPosition(Position pos);
    void refreshPosition();
    Position position;
    float zoom = 0.0f;


signals:
    void scrollChanged(float x);

};

#endif // HSCROLLBAR_H
