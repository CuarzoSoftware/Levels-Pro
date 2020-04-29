#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <Global/Includes.h>
#include <Widgets/Icon.h>


class ToggleButton : public QWidget
{
    Q_OBJECT
public:
    ToggleButton(Icon *icon, unsigned int layoutMargin=11, const QSize &fixedSize = QSize(38,38));
    ToggleButton(unsigned int verticalMargin,Icon *icon, const QString &extraClass="dark blue");
    void setActive(bool mode);
    bool isActive();
signals:
    void changed(bool state);


private:
    QHBoxLayout *layout = new QHBoxLayout(this);
    Icon *_icon;
    bool _active = false;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


};

#endif // TOGGLEBUTTON_H
