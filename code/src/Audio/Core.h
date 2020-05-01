#ifndef CORE_H
#define CORE_H

#include <QApplication>
#include <UI/MainWindow/MainWindow.h>

class Core : public QObject
{
    Q_OBJECT
public:
    Core(QApplication *_levels);

    // Initial methods
    void configure();
    void run();
private:

    // App reference
    QApplication *levels;

    // UI references
    MainWindow *mainWindow;

    // Configuration methods
    void setDefaultFontFamily();
    void loadDefaultStyle();


signals:

};

#endif // CORE_H
