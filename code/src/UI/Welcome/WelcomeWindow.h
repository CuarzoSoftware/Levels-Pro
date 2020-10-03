#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>
#include <Widgets/HLayout.h>
#include <Widgets/VLayout.h>
#include <Widgets/ListItem.h>

class WelcomeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWindow(QWidget *parent = nullptr);

private:
    ListItem *newProjectListItem = new ListItem(new Icon(":/res/svg/new-project.svg",QSize(26,26)),"New Project",this);
    ListItem *recentListItem = new ListItem(new Icon(":/res/svg/recent.svg", QSize(26,26)),"Recent",this);
    ListItem *templatesListItem = new ListItem(new Icon(":/res/svg/folder.svg",QSize(26,26)),"Templates",this);

    VLayout *verticalLayout = new VLayout(this);
    QWidget *topWidget = new QWidget(this);
    QWidget *projectDetailsWidget = new QWidget(this);
    QWidget *leftMenu = new QWidget(this);
    QWidget *buttonsWidget = new QWidget(this);

    VLayout *listLayout = new VLayout(leftMenu);

    HLayout *horizontalLayout = new HLayout(topWidget);


signals:

};

#endif // WELCOMEWINDOW_H
