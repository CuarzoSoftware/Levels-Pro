#include <Audio/Core.h>

// Initial method
int main(int argc, char *argv[])
{

    // Creates the Qt application
    QApplication *levels = new QApplication(argc, argv);

    // Run Levels
    Core *core = new Core(levels);
    core->configure();
    core->run();

    return levels->exec();
}

// Audio
/*
QThread audioThread;
Test *test = new Test;
AudioUnitWrap *wrap = new AudioUnitWrap();

test->moveToThread(&audioThread);
QObject::connect(&audioThread, &QThread::started, test, &Test::run);
QObject::connect(test, &Test::sendAU,wrap,&AudioUnitWrap::getAudioUnit);
audioThread.start();


// C
#include <thread>
#include <chrono>
#include <cstring>
#include <cmath>

// Mac OS X
#ifdef Q_OS_MAC
    #include <AudioToolbox/AudioToolbox.h>
    #include <ApplicationServices/ApplicationServices.h>
#endif
*/
