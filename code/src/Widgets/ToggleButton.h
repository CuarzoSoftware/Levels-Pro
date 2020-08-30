#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <Widgets/Icon.h>
#include <QHBoxLayout>


class ToggleButton : public QWidget
{
    Q_OBJECT
public:
    ToggleButton(Icon *icon, unsigned int layoutMargin=11, const QSize &fixedSize = QSize(38,38));
    ToggleButton(unsigned int verticalMargin,Icon *icon, const QString &extraClass="dark blue");
    void setActive(bool mode);
    bool isActive();
    void setActiveIconColor(const QColor &color);
signals:
    void changed(bool state);


private:
    QHBoxLayout *layout = new QHBoxLayout(this);
    Icon *_icon;
    bool _active = false;
    QColor defaultIconColor;
    QColor activeIconColor = QColor("#444");

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


};

#endif // TOGGLEBUTTON_H
