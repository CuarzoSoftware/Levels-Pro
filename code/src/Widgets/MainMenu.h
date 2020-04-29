#ifndef MAINMENU_H
#define MAINMENU_H

#include <Global/Includes.h>

class MainMenu : public QFrame
{
    Q_OBJECT
public:
    explicit MainMenu();
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);



};

#endif // MAINMENU_H
