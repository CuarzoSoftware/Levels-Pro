#ifndef TEST_H
#define TEST_H

#include "../global/Global.h"
#include "../audio/AudioImporter.h"
#include <ApplicationServices/ApplicationServices.h>
#include <QtMath>


struct SoundState {
    float volume;
    float sampleRate;
    int index;
    float toneFreq;
    float frameOffset;
    float squareWaveSign;
};

int16_t *song16;



/*----------------------------------------------------*/

typedef struct MyAUGraphPlayer
{
    AudioStreamBasicDescription inputFormat;
    AudioFileID inputFile;
    AUGraph graph;
    AudioUnit fileAU;
    AudioUnit pitch;
    AudioUnit speechAU;
}
MyAUGraphPlayer;


Float64 PrepareFileAU(MyAUGraphPlayer *player)
{
    AudioUnitSetProperty(player->fileAU,kAudioUnitProperty_ScheduledFileIDs, kAudioUnitScope_Global,0, &player->inputFile, sizeof(player->inputFile));
    UInt64 nPackets;
    UInt32 propsize = sizeof(nPackets);
    AudioFileGetProperty(player->inputFile,kAudioFilePropertyAudioDataPacketCount, &propsize,&nPackets);
    ScheduledAudioFileRegion rgn;
    memset (&rgn.mTimeStamp, 0, sizeof(rgn.mTimeStamp));
    rgn.mTimeStamp.mFlags = kAudioTimeStampSampleTimeValid;
    rgn.mTimeStamp.mSampleTime = 0;
    rgn.mCompletionProc = NULL;
    rgn.mCompletionProcUserData = NULL;
    rgn.mAudioFile = player->inputFile;
    rgn.mLoopCount = 1;
    rgn.mStartFrame = 0;
    rgn.mFramesToPlay = nPackets * player->inputFormat.mFramesPerPacket;
    AudioUnitSetProperty(player->fileAU, kAudioUnitProperty_ScheduledFileRegion,kAudioUnitScope_Global, 0,&rgn,sizeof(rgn));
    AudioTimeStamp startTime;
    memset (&startTime, 0, sizeof(startTime));
    startTime.mFlags = kAudioTimeStampSampleTimeValid; startTime.mSampleTime = -1;
    AudioUnitSetProperty(player->fileAU, kAudioUnitProperty_ScheduleStartTimeStamp,kAudioUnitScope_Global, 0,&startTime, sizeof(startTime));
    return (nPackets * player->inputFormat.mFramesPerPacket) /player->inputFormat.mSampleRate;
}

void CreateMyAUGraph(MyAUGraphPlayer *player)
{
    // Crea el graph
    NewAUGraph(&player->graph);

    // Crea una unidad de salida
    AudioComponentDescription outputcd = {};
    outputcd.componentType = kAudioUnitType_Output;
    outputcd.componentSubType = kAudioUnitSubType_DefaultOutput;
    outputcd.componentManufacturer = kAudioUnitManufacturer_Apple;

    // Crea el nodo de la unidad
    AUNode outputNode;
    AUGraphAddNode(player->graph,&outputcd,&outputNode);

    //
    AudioComponentDescription fileplayercd = {};
    fileplayercd.componentType = kAudioUnitType_Generator;
    fileplayercd.componentSubType = kAudioUnitSubType_AudioFilePlayer;
    fileplayercd.componentManufacturer = kAudioUnitManufacturer_Apple;
    AUNode fileNode;
    AUGraphAddNode(player->graph,&fileplayercd,&fileNode);
    AUGraphOpen(player->graph);
    AUGraphNodeInfo(player->graph,fileNode,NULL, &player->fileAU);
    AUGraphConnectNodeInput(player->graph,fileNode, 0, outputNode, 0);
    AUGraphInitialize(player->graph);

}
void test()
{

    // Url de la cancion
    CFURLRef inputFileURL = CFURLCreateWithFileSystemPath( kCFAllocatorDefault,CFSTR("/users/eduardo/audio16.wav"), kCFURLPOSIXPathStyle, false);

    // Crea un nuevo struct
    MyAUGraphPlayer player = {};

    // Lee la canción
    AudioFileOpenURL(inputFileURL, kAudioFileReadPermission,0,&player.inputFile);

    // Elimina el url
    CFRelease(inputFileURL);

    UInt32 propSize = sizeof(player.inputFormat);
    AudioFileGetProperty(player.inputFile,kAudioFilePropertyDataFormat, &propSize, &player.inputFormat);


    CreateMyAUGraph(&player);
    Float64 fileDuration = PrepareFileAU(&player);
    AUGraphStart(player.graph);
    usleep ((int)(fileDuration * 1000.0 * 1000.0));

    AUGraphStop (player.graph);
    AUGraphUninitialize (player.graph);
    AUGraphClose(player.graph);
    AudioFileClose(player.inputFile);
    return;

}
/*----------------------------------------------------*/

void auCallback(void *inUserData, AudioQueueRef queue, AudioQueueBufferRef buffer)
{

    auto soundState = static_cast<SoundState*>(inUserData);
    uint32_t framesToGen = buffer->mAudioDataBytesCapacity / 2;
    buffer->mAudioDataByteSize = framesToGen * 2;
    auto bufferPos = static_cast<int16_t*>(buffer->mAudioData);

    // Si 88200 = 1 segundo
    // 100hz se encuentran cada

    float percentDone = 0.0f;
    for (int x = 0; x < framesToGen; ++x)
    {

        float smile = -qAbs(qSin((float)soundState->index*M_PI/455.f)) + 1.0f;
        *bufferPos++ = song16[soundState->index]*smile;
        soundState->index++;

    }

    AudioQueueEnqueueBuffer(queue, buffer, 0, nullptr);
}


void setup()
{
    test();
    return;
    AudioImporter importer("/users/eduardo/sound.wav");

    song16 = new int16_t[importer.dataBodySize];
    memcpy(song16,importer.data + importer.offset,importer.dataBodySize);

    AudioStreamBasicDescription auDesc {};
    auDesc.mSampleRate = importer.samplesPerSecond;
    auDesc.mFormatID = kAudioFormatLinearPCM;

    auDesc.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger; //kLinearPCMFormatFlagIsBigEndian | kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    auDesc.mBytesPerPacket = importer.channelsNumber * importer.bitsPerSample/8;
    auDesc.mFramesPerPacket = 1;
    auDesc.mBytesPerFrame = importer.channelsNumber * importer.bitsPerSample/8;
    auDesc.mChannelsPerFrame = importer.channelsNumber;
    auDesc.mBitsPerChannel = importer.bitsPerSample;

    qDebug() << "mBytesPerPacket:"<< auDesc.mBytesPerPacket;
    qDebug() << "mBytesPerFrame:"<< auDesc.mBytesPerFrame;
    qDebug() << "mChannelsPerFrame:"<< auDesc.mChannelsPerFrame;
    qDebug() << "mBitsPerChannel:"<< auDesc.mBitsPerChannel;




    // Referencia a la cola
    AudioQueueRef auQueue = nullptr;
    AudioQueueBufferRef auBuffers[1] {};

    // our persistent state for sound playback
    SoundState soundState {};
    soundState.index = 0;
    soundState.volume = 1.0f;



    // most of the 0 and nullptr params here are for compressed sound formats etc.
    AudioQueueNewOutput(&auDesc, &auCallback, &soundState, nullptr, nullptr, 0, &auQueue);



    AudioQueueAllocateBuffer(auQueue, 88200, &(auBuffers[0]));


   // AudioQueueAllocateBuffer(auQueue, 8192, &(auBuffers[1]));


    // prime the buffers
    auCallback(&soundState, auQueue, auBuffers[0]);
    //auCallback(&soundState, auQueue, auBuffers[1]);

    // enqueue for playing
    AudioQueueEnqueueBuffer(auQueue, auBuffers[0], 0, nullptr);
    //AudioQueueEnqueueBuffer(auQueue, auBuffers[1], 0, nullptr);

    // go!
    AudioQueueStart(auQueue, nullptr);

    // Our AudioQueue creation options put the CA handling on its own thread
    // so this is a quick hack to allow us to hear some sound.
    std::this_thread::sleep_for(std::chrono::seconds{100});

    // be nice even it doesn't really matter at this point
    if (auQueue)
        AudioQueueDispose(auQueue, true);

    QApplication::exit();

}

/*

struct SoundState {
    float toneFreq, volume;
    float sampleRate, frameOffset;
    float squareWaveSign;
};
void auCallback(void *inUserData, AudioQueueRef queue, AudioQueueBufferRef buffer) {
    auto soundState = static_cast<SoundState*>(inUserData);

    // we're just filling the entire buffer here
    // In a real game we might only fill part of the buffer and set the mAudioDataBytes
    // accordingly.
    uint32_t framesToGen = buffer->mAudioDataBytesCapacity / 4;
    buffer->mAudioDataByteSize = framesToGen * 4;

    // calc the samples per up/down portion of each square wave (with 50% period)
    auto framesPerTransition = soundState->sampleRate / soundState->toneFreq;

    // sample to output at current state
    int16_t sample = 32767.f * soundState->squareWaveSign * soundState->volume;

    auto bufferPos = static_cast<int16_t*>(buffer->mAudioData);
    auto frameOffset = soundState->frameOffset;

    while (framesToGen) {
        // calc rounded frames to generate and accumulate fractional error
        uint32_t frames;
        auto needFrames = static_cast<uint32_t>(std::round(framesPerTransition - frameOffset));
        frameOffset -= framesPerTransition - needFrames;

        // we may be at the end of the buffer, if so, place offset at location in wave and clip
        if (needFrames > framesToGen) {
            frameOffset += framesToGen;
            frames = framesToGen;
        }
        else {
            frames = needFrames;
        }
        framesToGen -= frames;

        // simply put the samples in
        // simply put the samples in
        for (int x = 0; x < frames; ++x) {
            *bufferPos++ = song[soundState->index];
            *bufferPos++ = song[soundState->index];
            soundState->index++;
        }

        // flip sign of wave unless we were cut off prematurely
        if (needFrames == frames)
            sample = -sample;
    }

    // save square wave state for next callback
    if (sample > 0)
        soundState->squareWaveSign = 1;
    else
        soundState->squareWaveSign = -1;
    soundState->frameOffset = frameOffset;

    AudioQueueEnqueueBuffer(queue, buffer, 0, nullptr);
}

void setup()
{
    // stereo 16-bit interleaved linear PCM audio data at 48kHz in SNORM format
      AudioStreamBasicDescription auDesc {};
      auDesc.mSampleRate = 48000.0f;
      auDesc.mFormatID = kAudioFormatLinearPCM;
      auDesc.mFormatFlags = kLinearPCMFormatFlagIsBigEndian | kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
      auDesc.mBytesPerPacket = 4;
      auDesc.mFramesPerPacket = 1;
      auDesc.mBytesPerFrame = 4;
      auDesc.mChannelsPerFrame = 2;
      auDesc.mBitsPerChannel = 16;

      AudioQueueRef auQueue = nullptr;
      AudioQueueBufferRef auBuffers[2] {};

      // our persistent state for sound playback
      SoundState soundState {};
      soundState.toneFreq = 261.6 * 2; // 261.6 ~= Middle C frequency
      soundState.volume = 0.1; // don't crank this up and expect your ears to still function
      soundState.sampleRate = auDesc.mSampleRate;
      soundState.squareWaveSign = 1; // sign of the current part of the square wave

      OSStatus err;

      // most of the 0 and nullptr params here are for compressed sound formats etc.
      err = AudioQueueNewOutput(&auDesc, &auCallback, &soundState, nullptr, nullptr, 0, &auQueue);

      if (! err) {
          // generate buffers holding at most 1/16th of a second of data
          uint32_t bufferSize = auDesc.mBytesPerFrame * (auDesc.mSampleRate / 16);
          err = AudioQueueAllocateBuffer(auQueue, bufferSize, &(auBuffers[0]));

          if (! err) {
              err = AudioQueueAllocateBuffer(auQueue, bufferSize, &(auBuffers[1]));

              if (! err) {
                  // prime the buffers
                  auCallback(&soundState, auQueue, auBuffers[0]);
                  auCallback(&soundState, auQueue, auBuffers[1]);

                  // enqueue for playing
                  AudioQueueEnqueueBuffer(auQueue, auBuffers[0], 0, nullptr);
                  AudioQueueEnqueueBuffer(auQueue, auBuffers[1], 0, nullptr);

                  // go!
                  AudioQueueStart(auQueue, nullptr);
              }
          }
      }

      // Our AudioQueue creation options put the CA handling on its own thread
      // so this is a quick hack to allow us to hear some sound.
      std::this_thread::sleep_for(std::chrono::seconds{2});

      // be nice even it doesn't really matter at this point
      if (auQueue)
          AudioQueueDispose(auQueue, true);
}
*/
#endif // TEST_H
