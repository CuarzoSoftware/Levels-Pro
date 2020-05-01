#ifndef MENUTOPBAR_H
#define MENUTOPBAR_H

#include <QWidget>
#include <QHBoxLayout>

class MenuTopBar : public QWidget
{
    Q_OBJECT
public:
    explicit MenuTopBar();
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);

signals:

};

#endif // MENUTOPBAR_H
