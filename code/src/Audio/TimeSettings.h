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
        setTimeSignature(4,4);
    }

    void setProjectLengthInTicks(float length)
    {
        projectLenghtInTicks = length;
        projectLengthInDivitions = projectLenghtInTicks/ticksPerDivition;
        projectLengthInBeats = projectLenghtInTicks/ticksPerBeat;
        projectLenghtInBars = projectLenghtInTicks/ticksPerBar;

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

        ticksPerBeat = ticksPerWholeNote/noteValue;
        ticksPerBar = ticksPerBeat*beatsNumber;
        divitionsPerBeat = 16.f/noteValue;
        divitionsPerBar = divitionsPerBeat*beatsNumber;
        ticksPerDivition = ticksPerBeat/divitionsPerBeat;

        projectLengthInDivitions = projectLenghtInTicks/ticksPerDivition;
        projectLengthInBeats = projectLenghtInTicks/ticksPerBeat;
        projectLenghtInBars = projectLenghtInTicks/ticksPerBar;
    }

    float sampleRate;

    float bpm;

    float divitionsPerBeat;
    float divitionsPerBar;

    float ticksPerWholeNote = 3840.f;
    float ticksPerBeat;
    float ticksPerDivition;

    unsigned int loopBeginTick = 300;
    unsigned int loopEndTick = 500;

    float ticksPerBar;

    float projectLenghtInTicks = 591520.f;
    float projectLenghtInBars;
    float projectLengthInBeats;
    float projectLengthInDivitions;

    // Time signature
    unsigned int beatsNumber = 4;
    unsigned int noteValue = 4;
};

#endif // TIMESETTINGS_H
