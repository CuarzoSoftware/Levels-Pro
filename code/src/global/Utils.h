#ifndef UTILS_H
#define UTILS_H

#include "Global.h"

class Utils
{
public:
    static void addWidgetClass(QWidget *widget, const QString &className);
    static void removeWidgetClass(QWidget *widget, const QString &className);
};

#endif // UTILS_H
