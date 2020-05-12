#ifndef TIMESETTINGS_H
#define TIMESETTINGS_H

/**************************************
 ** 1 bar = (Depend of time signature)
 ** 1 beat = 4 divs
 ** 1 Div = 240 ticks
 **************************************/

class TimeSettings
{
public:
    explicit TimeSettings()
    {
        // Default settings
        setSampleRate(41100.f);
        setBpm(120.f);
        setTicksPerBeat(960.f);
        setTimeSignature(4,4);
        setProjectLengthInTicks(591520.f); // 128 bars
    }

    void setProjectLengthInTicks(float length)
    {
        projectLenghtInTicks = length;
        projectLengthInDivitions = projectLenghtInTicks/ticksPerDivition;
        projectLengthInBeats = projectLenghtInTicks/ticksPerBeat;
        projectLenghtInBars = projectLenghtInTicks/ticksPerBar;

    }

    void setTicksPerBeat(float _ticksPerBeat)
    {
        ticksPerBeat = _ticksPerBeat;
        ticksPerDivition = ticksPerBeat/4.f;
        ticksPerWholeNote = ticksPerBeat*4.f;
        ticksPerBar = (ticksPerWholeNote/noteValue)*beatsNumber;
    }

    void setSampleRate(float _sampleRate)
    {
        sampleRate = _sampleRate;
    }

    void setBpm(float _bpm)
    {
        bpm = _bpm;
    }

    void setTimeSignature(unsigned int _beatsNumber,unsigned int _noteValue)
    {
        beatsNumber = _beatsNumber;
        noteValue = _noteValue;
        ticksPerBar = (ticksPerWholeNote/noteValue)*beatsNumber;
    }

    float sampleRate;

    float bpm;


    float ticksPerWholeNote;
    float ticksPerDivition;
    float ticksPerBeat;
    float ticksPerBar;

    float projectLenghtInTicks;
    float projectLenghtInBars;
    float projectLengthInBeats;
    float projectLengthInDivitions;

    // Time signature
    unsigned int beatsNumber = 4;
    unsigned int noteValue = 4;
};

#endif // TIMESETTINGS_H
