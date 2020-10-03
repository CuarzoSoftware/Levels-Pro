#include "ListItem.h"

ListItem::ListItem(Icon *icon, const QString &text, QWidget *parent) : QWidget(parent)
{
    // Allow background color
    setAttribute(Qt::WA_StyledBackground, true);

    _icon = icon;
    _label->setText(text);
    setActive(false);
    horizontalLayout->addWidget(_icon);
    horizontalLayout->addWidget(_label);
}

void ListItem::setActive(bool mode)
{
    _active = mode;

    if(mode)
    {
        _icon->setColor(activeContentColor);
        _label->setStyleSheet("color:"+activeContentColor.name()+";");
        setStyleSheet("background-color:"+activeBackgroundColor.name()+";");
    }
    else
    {
        _icon->setColor(inactiveContentColor);
        _label->setStyleSheet("color:"+inactiveContentColor.name()+";");
        setStyleSheet("background-color:"+inactiveBackgroundColor.name()+";");
    }
}

bool ListItem::isActive()
{
    return _active;
}
