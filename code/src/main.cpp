#include "global/Global.h"
#include "ui/MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication *levels = new QApplication(argc, argv);

    MainWindow *mainWindow = new MainWindow(levels);
    mainWindow->show();

    return levels->exec();
}
