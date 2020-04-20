#ifndef TOPBAR_H
#define TOPBAR_H

#include "../global/Global.h"

#include "../widgets/ToggleButton.h"

class TopBar : public QWidget
{
    Q_OBJECT
public:
    explicit TopBar();
    QHBoxLayout *layout = new QHBoxLayout();


};

#endif // TOPBAR_H
