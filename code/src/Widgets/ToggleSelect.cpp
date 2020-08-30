#include "ToggleSelect.h"

ToggleSelect::ToggleSelect(QWidget *parent)
{
    setParent(parent);
    addWidget(toggleButton);
    addWidget(select);
    toggleButton->setActiveIconColor(Qt::white);
}
