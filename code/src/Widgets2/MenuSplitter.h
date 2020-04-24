#ifndef MENUSPLITTER_H
#define MENUSPLITTER_H

#include <Global/Includes.h>

class MenuSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit MenuSplitter(Qt::Orientation orientation);

};

#endif // MENUSPLITTER_H
