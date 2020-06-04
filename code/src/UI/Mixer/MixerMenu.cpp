#include "MixerMenu.h"
#include <Global/Utils.h>

/*!
    \class MixerMenu
    \brief The MixerMenu class...

    \inheaderfile UI/Mixer/MixerMenu.h
    \ingroup UI
    \inmodule UI

    \inherits MainMenu
*/

MixerMenu::MixerMenu()
{
    // Añade su clase
    Utils::addWidgetClass(this,"centerMenu");

    // Asigna una altura mínima
    setMinimumHeight(100);

    // Lo esconde inicialmente
    hide();
}
