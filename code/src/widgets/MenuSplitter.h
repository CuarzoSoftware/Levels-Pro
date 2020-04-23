#ifndef MENUSPLITTER_H
#define MENUSPLITTER_H

#include "../Global/Global.h"

class MenuSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit MenuSplitter(Qt::Orientation orientation);

};

#endif // MENUSPLITTER_H
