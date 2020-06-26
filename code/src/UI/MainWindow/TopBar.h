#ifndef TOPBAR_H
#define TOPBAR_H

#include <Widgets/CompactContainer.h>
#include <Widgets/ToggleButton.h>

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
    ToggleButton *libraryBtn = new ToggleButton(new Icon(":/res/svg/library.svg"),10);
    ToggleButton *inspectorBtn = new ToggleButton(new Icon(":/res/svg/inspector.svg"),9);
    ToggleButton *toolsBtn = new ToggleButton(new Icon(":/res/svg/tools.svg"));

    // Tools Buttons
    ToggleButton *mixerBtn = new ToggleButton(new Icon(":/res/svg/controls-9.svg"));
    ToggleButton *editBtn = new ToggleButton(new Icon(":/res/svg/scissors.svg"));

    // Playback Buttons
    ToggleButton *rewindBtn = new ToggleButton(new Icon(":/res/svg/rewind.svg"));
    ToggleButton *forwardBtn = new ToggleButton(new Icon(":/res/svg/fast-forward.svg"));
    ToggleButton *backStopBtn = new ToggleButton(new Icon(":/res/svg/back.svg"));
    ToggleButton *playBtn = new ToggleButton(new Icon(":/res/svg/play-button.svg"));
    ToggleButton *recordBtn = new ToggleButton(new Icon(":/res/svg/circle.svg",QColor("#C83028")),11);
    ToggleButton *loopBtn = new ToggleButton(new Icon(":/res/svg/repeat.svg"));

    // Modes Buttons
    ToggleButton *replaceBtn = new ToggleButton(new Icon(":/res/svg/error.svg"));
    ToggleButton *lowLatencyBtn = new ToggleButton(new Icon(":/res/svg/speed.svg"),7);
    ToggleButton *tunerBtn = new ToggleButton(new Icon(":/res/svg/tuner.svg"),8);
    ToggleButton *soloBtn = new ToggleButton(new Icon(":/res/svg/solo.svg"),8);

    // Time Buttons
    ToggleButton *countBtn = new ToggleButton(new Icon(":/res/svg/timer.svg"));
    ToggleButton *metronomeBtn = new ToggleButton(new Icon(":/res/svg/metronome.svg"),8);

    // Right Buttons
    ToggleButton *listsEditorBtn = new ToggleButton(new Icon(":/res/svg/list.svg"));
    ToggleButton *notesBtn = new ToggleButton(new Icon(":/res/svg/edit.svg"),9);
    ToggleButton *loopsBtn = new ToggleButton(new Icon(":/res/svg/infinity.svg"));
    ToggleButton *mediaBtn = new ToggleButton(new Icon(":/res/svg/music-player-1.svg"));


};

#endif // TOPBAR_H
