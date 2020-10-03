#ifndef COLOR_H
#define COLOR_H

#include <QColor>
#include <QVariantMap>

class Theme
{
public:
    Theme(const QString &themePath);
    QColor get( const QString &colorName );
    QString getString( const QString &colorName );
private:
    void generateDefaultTheme();
    QVariantMap customTheme;
    QVariantMap defaultTheme;
    bool useDefault = true;
};


class Color
{
public:
    static Theme theme;
};



#endif // COLOR_H
