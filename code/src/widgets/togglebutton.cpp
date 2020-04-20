#include "ToggleButton.h"
#include "../audio/test.h"

ToggleButton::ToggleButton(QString icon)
{
    // Permite aplicar color de fondo
    setAttribute(Qt::WA_StyledBackground, true);

    // Asigna la clase para los estilos
    setProperty("class","toggleButton off");

    // Asigna una altura fija
    setFixedSize(38,38);

    // Ajusta el layout
    layout->setMargin(6);

    // Asigna el layout
    setLayout(layout);

    // Eventos del mouse
    setMouseTracking(true);
    _icon->setMouseTracking(true);

    // Crea el pixmap
    _pixmap = QIcon(icon).pixmap(64,64);

    // Ajusta el tamaño de la imagen
    _icon->setScaledContents(true);

    // Le asigna el color
    setIconColor(QColor(32,32,32));

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
        setProperty("class","toggleButton on");
    else
        setProperty("class","toggleButton off");

    style()->unpolish(this);
    style()->polish(this);
    update();

}

bool ToggleButton::isActive()
{
    return _active;
}


void ToggleButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setProperty("class","toggleButton pressing");
    style()->unpolish(this);
    style()->polish(this);
    update();
}

void ToggleButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setActive(!_active);
    setup();
}
