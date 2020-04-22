#include "ToggleButton.h"
#include "../Audio/Test.h"

ToggleButton::ToggleButton(const QString &iconUrl, uint layoutMargin, const QColor &iconColor)
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","toggleButton");

    // Asigna una altura fija
    setFixedSize(38,38);

    // Ajusta el layout
    layout->setMargin(layoutMargin);

    // Asigna el layout
    setLayout(layout);

    // Eventos del mouse
    setMouseTracking(true);
    _icon->setMouseTracking(true);

    // Crea el pixmap
    _pixmap = QIcon(iconUrl).pixmap(64,64);

    // Ajusta el tamaño de la imagen
    _icon->setScaledContents(true);

    // Le asigna el color
    setIconColor(iconColor);

    // Asigna el icono al layout
    layout->addWidget(_icon);
}



void ToggleButton::setIconColor(QColor color)
{

    QImage tmp = _pixmap.toImage();

    for(int y = 0; y < tmp.height(); y++)
    {
        for(int x= 0; x < tmp.width(); x++)
        {
            color.setAlpha(tmp.pixelColor(x,y).alpha());
            tmp.setPixelColor(x,y,color);
        }
    }
    _icon->setPixmap(QPixmap::fromImage(tmp));

}

void ToggleButton::setActive(bool mode)
{
    _active = mode;

    if(mode)
        Utils::addWidgetClass(this,"active");
    else
        Utils::removeWidgetClass(this,"active");
}

bool ToggleButton::isActive()
{
    return _active;
}


void ToggleButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    Utils::removeWidgetClass(this,"active");
    Utils::addWidgetClass(this,"pressing");
}

void ToggleButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setActive(!_active);
    Utils::removeWidgetClass(this,"pressing");
}
