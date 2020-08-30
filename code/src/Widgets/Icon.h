#ifndef ICON_H
#define ICON_H

#include <QLabel>
#include <Global/Color.h>

class Icon : public QLabel
{
    Q_OBJECT
public:
    Icon(const QString &iconURL,const QColor &color=QColor("#666"));
    Icon(const QString &iconURL,const QSize &fixedSize,const QColor &color=QColor("#666"));
    void setIcon(const QString &iconURL);
    void setColor(const QColor &color);
    QColor getColor();

private:
    QColor _iconColor;
signals:

};

#endif // ICON_H
