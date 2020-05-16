#ifndef HSCROLLBAR_H
#define HSCROLLBAR_H

#include <QWidget>

class HScrollBar : public QWidget
{
    Q_OBJECT
public:
    enum Position{Top,Bottom};
    explicit HScrollBar(QWidget *parent = nullptr, Position pos = Position::Bottom);
    void setRange(int _range);
    void moveX(int offset);
    void setX(int pos);
    QWidget *bar = new QWidget(this);

private:
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    void setPosition(Position pos);
    void refreshPosition();
    void validateX();
    Position position;
    int range = 0;
    int x = 0;


signals:
    void scrollChanged(int x);

};

#endif // HSCROLLBAR_H
