#include <UI/MainWindow/MainWindow.h>
//#include <Audio/Test.h>
//#include <Audio/AUPluginUI.h>
#include <QThread>
#include <Global/Includes.h>


#include <QFontDatabase>



int main(int argc, char *argv[])
{

    QApplication *levels = new QApplication(argc, argv);
    MainWindow *mainWindow = new MainWindow(levels);
    mainWindow->show();

    int id = QFontDatabase::addApplicationFont(":res/fonts/HelveticaNeue.ttc");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    font.setStyleHint(QFont::Helvetica);
    levels->setFont(font);
    // Audio
    /*
    QThread audioThread;
    Test *test = new Test;
    AudioUnitWrap *wrap = new AudioUnitWrap();

    test->moveToThread(&audioThread);
    QObject::connect(&audioThread, &QThread::started, test, &Test::run);
    QObject::connect(test, &Test::sendAU,wrap,&AudioUnitWrap::getAudioUnit);
    audioThread.start();
    */

    return levels->exec();
}
