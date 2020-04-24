#ifndef MAINMENU_H
#define MAINMENU_H

#include <Global/Includes.h>
#include <Widgets/MenuTopBar.h>

class MainMenu : public QFrame
{
    Q_OBJECT
public:
    explicit MainMenu();
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    MenuTopBar *topBar = new MenuTopBar();


};

#endif // MAINMENU_H
