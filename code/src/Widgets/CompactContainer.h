#ifndef COMPACTCONTAINER_H
#define COMPACTCONTAINER_H

#include <QWidget>
#include <QHBoxLayout>

class CompactContainer : public QWidget
{
    Q_OBJECT
public:
    explicit CompactContainer(QWidget *parent = nullptr);
    void addWidget(QWidget *widget);

    QHBoxLayout *layout = new QHBoxLayout(this);
private:
    void fixWidgetStyles();

signals:

};

#endif // COMPACTCONTAINER_H
