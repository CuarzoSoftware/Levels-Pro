#ifndef TOGGLESELECT_H
#define TOGGLESELECT_H

#include <Widgets/CompactContainer.h>
#include <Widgets/ToggleButton.h>
#include <Widgets/Select.h>

class ToggleSelect : public CompactContainer
{
    Q_OBJECT
public:
    explicit ToggleSelect(QWidget *parent = nullptr);
    ToggleButton *toggleButton = new ToggleButton(1,new Icon(":res/svg/power.svg",QSize(21,21)));
    Select *select = new Select("Smart");

signals:

};

#endif // TOGGLESELECT_H
