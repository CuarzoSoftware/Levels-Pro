#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include "../global/Global.h"

class ToggleButton : public QWidget
{
    Q_OBJECT
public:
    explicit ToggleButton(QString icon);
    void setIconColor(QColor color);
    void setActive(bool mode);
    bool isActive();

private:
    QHBoxLayout *layout = new QHBoxLayout();
    QLabel *_icon = new QLabel();
    QPixmap _pixmap;
    bool _active = false;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


};

#endif // TOGGLEBUTTON_H
