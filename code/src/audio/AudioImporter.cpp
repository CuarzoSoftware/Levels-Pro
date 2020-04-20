#include "AudioImporter.h"
#include "../global/Global.h"

AudioImporter::AudioImporter(const QString &url)
{

    QFile file(url);

    if(!file.open(QFile::ReadOnly)) return;

    data = file.readAll().data();

    memcpy(  riffChunkId,           data + offset, 4); offset+=4;
    memcpy( &chunkBodySize,         data + offset, 4); offset+=4;
    memcpy(  riffFormatCode,        data + offset, 4); offset+=4;

    memcpy(  formatChunkId,         data + offset, 4); offset+=4;
    memcpy( &formatChunkBodySize,   data + offset, 4); offset+=4;
    memcpy( &formatCode,            data + offset, 2); offset+=2;
    memcpy( &channelsNumber,        data + offset, 2); offset+=2;
    memcpy( &samplesPerSecond,      data + offset, 4); offset+=4;
    memcpy( &bytesPerSecond,        data + offset, 4); offset+=4;
    memcpy( &bytesPerSampleFrame,   data + offset, 2); offset+=2;
    memcpy( &bitsPerSample,         data + offset, 2); offset+=2;

    // Si no es INT PCM
    if(formatCode != 1)
    {
        if(formatChunkBodySize >= 18)
        {
            memcpy( &extensionSize,         data + offset,  2); offset+=2;
        }

        if(formatChunkBodySize == 40)
        {
            memcpy( &extensionValidBits,    data + offset,  2); offset+=2;
            memcpy( &extensionChannelMask,  data + offset,  4); offset+=4;
            memcpy( extensionSpeakers,      data + offset, 16); offset+=16;
        }

    }


    // ID de chunk siguiente ( Puede ser "fact" o "data" )
    memcpy( factChunkId, data + offset,4); offset+=4;

    // Si es "fact"
    if(strcmp(factChunkId,"fact") == 0)
    {
         memcpy( &factBodySize,     data + offset,4); offset+=4;
         memcpy( &factSampleFrames, data + offset,4); offset+=4;
         memcpy( dataChunkId,       data + offset,4); offset+=4;

         if(strcmp(dataChunkId,"PEAK") == 0)
         {
             strcpy(peakChunkId,"PEAK");
             memcpy( &peakBodySize, data + offset,4); offset+=4;
             offset+=peakBodySize;
             memcpy( dataChunkId,       data + offset,4); offset+=4;
         }
         else
         {
             strcpy(peakChunkId,"NONE");
         }
    }
    else
    {
        strcpy(dataChunkId,factChunkId);
        strcpy(factChunkId,"NONE");
        strcpy(peakChunkId,"NONE");
    }

    memcpy( &dataBodySize,     data + offset,4); offset+=4;




    if(strcmp(riffFormatCode,"WAVE") == 0)qDebug("ES WAVE!");

    qDebug() << "   ---------- RIFF CHUNK ------------";
    qDebug() << "   Chunk ID:                  " << riffChunkId;
    qDebug() << "   Body Size:                 " << chunkBodySize << "bytes";
    qDebug() << "   Format Code:               " << riffFormatCode << "\n";

    qDebug() << "   --------- FORMAT CHUNK -----------";
    qDebug() << "   Chunk ID:                  " << formatChunkId;
    qDebug() << "   Chunk Size:                " << formatChunkBodySize << "bytes";
    qDebug() << "   Format Code:               " << formatCode << "(1=INT PCM  2=ADPCM  3=FLOAT PCM   6=A-LAW   7=μ-LAW   65534=WaveFormatExtensible)";
    qDebug() << "   Number of Channels:        " << channelsNumber;
    qDebug() << "   Samples per Second:        " << samplesPerSecond;
    qDebug() << "   Bytes per Second:          " << bytesPerSecond;
    qDebug() << "   Bytes per Sample Frame:    " << bytesPerSampleFrame;
    qDebug() << "   Bits per Sample:           " << bitsPerSample << "\n";

    qDebug() << "   --------- FORMAT EXTENSION -------";
    qDebug() << "   Extension Size:            " << extensionSize << "bytes";
    qDebug() << "   Valid Bits:                " << extensionValidBits << "bits";
    qDebug() << "   Channel Mask:              " << extensionChannelMask;
    qDebug() << "   Speakers:                  " << extensionSpeakers[0] << extensionSpeakers[1] << extensionSpeakers[2] << extensionSpeakers[3] << extensionSpeakers[4] << extensionSpeakers[5] << extensionSpeakers[6] << extensionSpeakers[7] << extensionSpeakers[8] << extensionSpeakers[9] << extensionSpeakers[10] << extensionSpeakers[11] << extensionSpeakers[12] << extensionSpeakers[13] << extensionSpeakers[14] << extensionSpeakers[15] << "\n";

    qDebug() << "   --------- FACT CHUNK -------------";
    qDebug() << "   Chunk ID:                  " << factChunkId;
    qDebug() << "   Chunk Size:                " << factBodySize << "bytes";
    qDebug() << "   Sample Frames:             " << factSampleFrames << "\n";

    qDebug() << "   --------- PEAK CHUNK -------------";
    qDebug() << "   Chunk ID:                  " << peakChunkId ;
    qDebug() << "   Chunk Size:                " << peakBodySize << "bytes" << "\n";

    qDebug() << "   --------- DATA CHUNK -------------";
    qDebug() << "   Chunk ID:                  " << dataChunkId ;
    qDebug() << "   Music Data Size:           " << dataBodySize << "bytes" << "\n";

    float seconds = (float)dataBodySize/(float)bytesPerSecond;
    unsigned int minutes = (unsigned int)seconds/60;
    unsigned int remainingSeconds = (unsigned int)seconds%60;


    qDebug() << "   --------------- INFO -------------";
    qDebug() << "   Seconds:                  " << seconds << "seconds";
    qDebug() << "   Minutes:                  " << minutes << ":" << remainingSeconds << "minutes";




}
