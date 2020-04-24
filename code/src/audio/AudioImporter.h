#ifndef AUDIOIMPORTER_H
#define AUDIOIMPORTER_H

#include <Global/Includes.h>

class AudioImporter
{
public:
    AudioImporter(const QString &url);

    const char *data;

    // WAVE
    uint32_t offset = 0;

    // RIFF Chunk
    char *riffChunkId = new char[4];
    uint32_t chunkBodySize = 0;
    char *riffFormatCode = new char[4];

    // Format Chunk
    char *formatChunkId = new char[4];
    uint32_t formatChunkBodySize = 0;
    uint16_t formatCode = 0;
    uint16_t channelsNumber = 0;
    uint32_t samplesPerSecond = 0;
    uint32_t bytesPerSecond = 0;
    uint16_t bytesPerSampleFrame = 0;
    uint16_t bitsPerSample = 0;

    // Format Chunk Extension
    uint16_t extensionSize = 0;
    uint16_t extensionValidBits = 0;
    uint32_t extensionChannelMask = 0;
    bool *extensionSpeakers = new bool[16];

    // Fact Chunck
    char *factChunkId = new char[4];
    uint32_t factBodySize = 0;
    uint32_t factSampleFrames = 0;

    // PEAK Chunck
    char *peakChunkId = new char[4];
    uint32_t peakBodySize = 0;

    // Data Chunck
    char *dataChunkId = new char[4];
    uint32_t dataBodySize = 0;
};

#endif // AUDIOIMPORTER_H
