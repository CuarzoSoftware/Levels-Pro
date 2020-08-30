#include "Icon.h"
#include <QIcon>

/*!
    \class Icon
    \brief The Icon class...

    \inheaderfile Widgets/Icon.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QLabel
*/

// Constructor I
Icon::Icon(const QString &iconURL, const QColor &color)
{

    // Ajusta el tamaño de la imagen
    setScaledContents(true);

    // Almacena el color
    _iconColor = color;

    // Asigna el ícono
    setIcon(iconURL);

}

// Constructor II
Icon::Icon(const QString &iconURL,const QSize &fixedSize,const QColor &color)
{
    // Ajusta el tamaño de la imagen
    setScaledContents(true);

    // Asigna un tamaño fijo
    setFixedSize(fixedSize);

    // Almacena el color
    _iconColor = color;

    // Asigna el ícono
    setIcon(iconURL);
}

void Icon::setIcon(const QString &iconURL)
{
    // Crea el pixmap
    setPixmap(QIcon(iconURL).pixmap(64,64));

    // Le asigna el color
    setColor(_iconColor);
}

void Icon::setColor(const QColor &color)
{
    _iconColor = color;

    QImage tmp = pixmap()->toImage();

    for(int y = 0; y < tmp.height(); y++)
    {
        for(int x= 0; x < tmp.width(); x++)
        {
            _iconColor.setAlpha(tmp.pixelColor(x,y).alpha());
            tmp.setPixelColor(x,y,_iconColor);
        }
    }
    setPixmap(QPixmap::fromImage(tmp));
}

QColor Icon::getColor()
{
    return _iconColor;
}
