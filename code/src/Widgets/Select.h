#ifndef SELECT_H
#define SELECT_H

#include <Global/Includes.h>
#include <Widgets/Icon.h>

class Select : public QWidget
{
    Q_OBJECT
public:
    Select(const QString &title, uint verticalMargin = 4);
    Select(Icon *displayIcon, uint verticalMargin = 4);
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    Icon *icon;
    Icon *downArrow = new Icon(":res/svg/down-arrow.svg");
    QLabel *label;

private:
    void setup();



signals:

};

#endif // SELECT_H
