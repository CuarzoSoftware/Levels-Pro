#include "Utils.h"

// Añade una clase de estilo a un widget
void Utils::addWidgetClass(QWidget *widget, const QString &className)
{
    // Obtiene sus clases actuales
    QString classString = widget->property("class").toString();
    QStringList currentClasses = classString.split(" ");

    // Verifica que no la tenga
    for(int i = 0; i < currentClasses.length(); i++)
    {
        // Si ya la tiene, se detiene
        if(currentClasses[i].compare(className) == 0)
            return;
    }

    // Si no la tiene, la agrega
    widget->setProperty("class",classString.append(" ").append(className));

    // Actualiza los estilos
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();

}

// Elimina una clase de estilo a un widget
void Utils::removeWidgetClass(QWidget *widget, const QString &className)
{
    // Obtiene sus clases actuales
    QStringList currentClasses = widget->property("class").toString().split(" ");

    // Verifica que la tenga
    for(int i = 0; i < currentClasses.length(); i++)
    {
        // Si ya la tiene, la elimina
        if(currentClasses[i].compare(className) == 0)
        {
            // Elimina la clase
            currentClasses.removeAt(i);

            // Nuevo string para almacenar las clases sin incluir la a eliminar
            QString newClassString = "";

            // Asigna las clases anteriores al nuevo string
            for(int j = 0; j < currentClasses.length(); j++)
                newClassString.append(" ").append(currentClasses[j]);

            // Asigna el cambio
            widget->setProperty("class",newClassString);

            // Actualiza los estilos
            widget->style()->unpolish(widget);
            widget->style()->polish(widget);
            widget->update();
        }

    }

}
