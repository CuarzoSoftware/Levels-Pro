#ifndef TOPBAR_H
#define TOPBAR_H

#include "../Global/Global.h"

#include "../Widgets/CompactContainer.h"
#include "../Widgets/ToggleButton.h"
#include "../Global/Color.h"

class TopBar : public QWidget
{
    Q_OBJECT
public:
    explicit TopBar();
    QHBoxLayout *layout = new QHBoxLayout();

    // Item containers
    CompactContainer *leftContainer = new CompactContainer();
    CompactContainer *toolsContainer = new CompactContainer();
    CompactContainer *playbackContainer = new CompactContainer();
    CompactContainer *modesContainer = new CompactContainer();
    CompactContainer *tempoContainer = new CompactContainer();
    CompactContainer *rightContainer = new CompactContainer();

    // Left container Buttons
    ToggleButton *libraryBtn = new ToggleButton(":/res/svg/library.svg");
    ToggleButton *inspectorBtn = new ToggleButton(":/res/svg/inspector.svg",9);
    ToggleButton *toolsBtn = new ToggleButton(":/res/svg/tools.svg");

    // Tools Buttons
    ToggleButton *mixerBtn = new ToggleButton(":/res/svg/controls-9.svg");
    ToggleButton *editBtn = new ToggleButton(":/res/svg/scissors.svg");

    // Playback Buttons
    ToggleButton *rewindBtn = new ToggleButton(":/res/svg/rewind.svg");
    ToggleButton *forwardBtn = new ToggleButton(":/res/svg/fast-forward.svg");
    ToggleButton *backStopBtn = new ToggleButton(":/res/svg/back.svg");
    ToggleButton *playBtn = new ToggleButton(":/res/svg/play-button.svg");
    ToggleButton *recordBtn = new ToggleButton(":/res/svg/circle.svg",11,QColor("#C83028"));
    ToggleButton *loopBtn = new ToggleButton(":/res/svg/repeat.svg");

    // Modes Buttons
    ToggleButton *replaceBtn = new ToggleButton(":/res/svg/error.svg");
    ToggleButton *lowLatencyBtn = new ToggleButton(":/res/svg/speed.svg",7);
    ToggleButton *tunerBtn = new ToggleButton(":/res/svg/tuner.svg",8);
    ToggleButton *soloBtn = new ToggleButton(":/res/svg/solo.svg",8);

    // Time Buttons
    ToggleButton *countBtn = new ToggleButton(":/res/svg/timer.svg");
    ToggleButton *metronomeBtn = new ToggleButton(":/res/svg/metronome.svg",8);

    // Right Buttons
    ToggleButton *marksBtn = new ToggleButton(":/res/svg/list.svg");
    ToggleButton *notesBtn = new ToggleButton(":/res/svg/edit.svg",9);
    ToggleButton *loopsBtn = new ToggleButton(":/res/svg/infinity.svg");
    ToggleButton *mediaBtn = new ToggleButton(":/res/svg/music-player-1.svg");


};

#endif // TOPBAR_H
