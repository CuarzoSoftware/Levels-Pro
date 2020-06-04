#include "EditorMenu.h"
#include <Global/Utils.h>

/*!
    \class EditorMenu
    \brief The EditorMenu class...

    \inheaderfile UI/Editor/EditorMenu.h
    \ingroup UI
    \inmodule UI

    \inherits MainMenu
*/

EditorMenu::EditorMenu()
{
    // Añade su clase
    Utils::addWidgetClass(this,"centerMenu");

    // Asigna una altura mínima
    setMinimumHeight(100);

    // Lo esconde inicialmente
    hide();
}
