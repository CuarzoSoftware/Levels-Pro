#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>
#include <Widgets/Icon.h>
#include <QHBoxLayout>
#include <Global/Color.h>

class ListItem : public QWidget
{
    Q_OBJECT
public:
    explicit ListItem(Icon *icon,const QString &text,QWidget *parent = nullptr);
    void setActive(bool mode);
    bool isActive();

private:
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);

    bool _active = false;
    Icon *_icon;
    QLabel *_label = new QLabel(this);

    QColor inactiveBackgroundColor = Color::theme.get("ListItemDefaultInactiveBackground");
    QColor activeBackgroundColor = Color::theme.get("ListItemDefaultActiveBackground");
    QColor inactiveContentColor = Color::theme.get("ListItemDefaultInactiveContent");
    QColor activeContentColor = Color::theme.get("ListItemDefaultActiveContent");

};

#endif // LISTITEM_H
