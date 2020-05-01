#include "EditorMenu.h"
#include <Global/Utils.h>

EditorMenu::EditorMenu()
{
    // Añade su clase
    Utils::addWidgetClass(this,"centerMenu");

    // Asigna una altura mínima
    setMinimumHeight(100);

    // Lo esconde inicialmente
    hide();
}
