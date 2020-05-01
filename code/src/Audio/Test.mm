#ifndef TEST_H
#define TEST_H

#include <Audio/AudioImporter.h>
#include <Audio/Test.h>

#include <QDebug>
#include <QtMath>
#include <QApplication>

#include <cstring>
#include <thread>



struct SoundState {
    float volume;
    float sampleRate;
    int index;
    float toneFreq;
    float frameOffset;
    float squareWaveSign;
};

int16_t *song16;


int loadX = 0;
/*----------------------------------------------------*/

typedef struct MyAUGraphPlayer
{
    AudioStreamBasicDescription inputFormat;
    AudioFileID inputFile;
    AUGraph graph;
    AudioUnit fileAU;
    AudioUnit pitch;
    AudioUnit eqAU;
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

// EQ
AudioComponentDescription eqDesc = {};

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




    AUNode eqNode;
    AUGraphAddNode(player->graph,&eqDesc,&eqNode);


    //
    AudioComponentDescription fileplayercd = {};
    fileplayercd.componentType = kAudioUnitType_Generator;
    fileplayercd.componentSubType = kAudioUnitSubType_AudioFilePlayer;
    fileplayercd.componentManufacturer = kAudioUnitManufacturer_Apple;
    AUNode fileNode;
    AUGraphAddNode(player->graph,&fileplayercd,&fileNode);
    AUGraphOpen(player->graph);
    AUGraphNodeInfo(player->graph,fileNode,NULL, &player->fileAU);
    AUGraphNodeInfo(player->graph,eqNode,NULL, &player->eqAU);
    AUGraphConnectNodeInput(player->graph,fileNode, 0, eqNode, 0);
    AUGraphConnectNodeInput(player->graph,eqNode, 0, outputNode, 0);



    AUGraphInitialize(player->graph);


}


void auCallback(void *inUserData, AudioQueueRef queue, AudioQueueBufferRef buffer)
{

    auto soundState = static_cast<SoundState*>(inUserData);
    uint32_t framesToGen = buffer->mAudioDataBytesCapacity / 2;
    buffer->mAudioDataByteSize = framesToGen * 2;
    auto bufferPos = static_cast<int16_t*>(buffer->mAudioData);

    // Si 88200 = 1 segundo
    // 100hz se encuentran cada

    float percentDone = 0.0f;
    Q_UNUSED(percentDone);
    for (uint32_t x = 0; x < framesToGen; ++x)
    {

        float smile = -qAbs(qSin((float)soundState->index*M_PI/455.f)) + 1.0f;
        *bufferPos++ = song16[soundState->index]*smile;
        soundState->index++;

    }

    AudioQueueEnqueueBuffer(queue, buffer, 0, nullptr);
}


void setup()
{

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



QString OSTypeToChar(OSType type)
{
    char *st = new char[5];
    memcpy(st,&type,4);
    QString s = QString::fromUtf8(st);
    std::reverse(s.begin(), s.end());
    return s;
}
const char * mungeString(CFStringRef someString)
{
    return CFStringGetCStringPtr(someString, kCFStringEncodingMacRoman);

}

void Test::run()
{
    // Crea un nuevo struct
    MyAUGraphPlayer player = {};

    AudioComponentDescription desc = {0};
    AudioComponent inComponent = {};
    AudioComponentDescription outDesc = {};
    CFStringRef name;
    UInt32 count =  AudioComponentCount(&desc);
    qDebug() << count;
    for(UInt32 i = 0; i < count; i++)
    {

       inComponent = AudioComponentFindNext(inComponent, &desc);

        AudioComponentGetDescription(inComponent, &outDesc);

        AudioComponentCopyName(inComponent, &name);

        if(i == 540)
        {
           break;
        }

        qDebug() << i << "--"<<OSTypeToChar(outDesc.componentType) << " -- " << QString::fromCFString(name);
    }
    //return;
    eqDesc = outDesc;

    // Url de la cancion
    CFURLRef inputFileURL = CFURLCreateWithFileSystemPath( kCFAllocatorDefault,CFSTR("/users/eduardo/tame.mp3"), kCFURLPOSIXPathStyle, false);

    // Lee la canción
    AudioFileOpenURL(inputFileURL, kAudioFileReadPermission,0,&player.inputFile);

    // Elimina el url
    CFRelease(inputFileURL);

    UInt32 propSize = sizeof(player.inputFormat);
    AudioFileGetProperty(player.inputFile,kAudioFilePropertyDataFormat, &propSize, &player.inputFormat);


    CreateMyAUGraph(&player);

    sendAU(player.eqAU);

    Float64 fileDuration = PrepareFileAU(&player);

    AUGraphStart(player.graph);

    usleep ((int)(fileDuration * 1000.0 * 1000.0));

    AUGraphStop (player.graph);
    AUGraphUninitialize (player.graph);
    AUGraphClose(player.graph);
    AudioFileClose(player.inputFile);

    return;
}
#endif
