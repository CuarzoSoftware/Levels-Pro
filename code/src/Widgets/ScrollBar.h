#ifndef HSCROLLBAR_H
#define HSCROLLBAR_H

#include <QScrollBar>

class ScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit ScrollBar(Qt::Orientation orientation, QWidget *parent);
    void setParent(QWidget *parent);

private:
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    void updateDimensions();
};

#endif // HSCROLLBAR_H
