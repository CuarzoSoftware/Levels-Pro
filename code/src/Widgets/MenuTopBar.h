#ifndef MENUTOPBAR_H
#define MENUTOPBAR_H

#include <Global/Includes.h>

class MenuTopBar : public QWidget
{
    Q_OBJECT
public:
    explicit MenuTopBar();
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);

signals:

};

#endif // MENUTOPBAR_H
