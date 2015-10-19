#include "AudioSource.h"
#include "SimpleLogger.h"
#include <iostream>

namespace AudioFingerprint
{

namespace
{

#define SWAPPED_US(x) (((x) >> 8) | ((x) << 8))
#define SWAPPED_UL(x) ((((x) >> 24) & 0xff) | (((x) << 8) & 0xff0000) | (((x) >> 8) & 0xff00) | (((x) << 24) & 0xff000000))

#pragma pack(push, 1)

typedef struct {
    char RIFF [4];
    uint32_t Size;
    char Format [4];
    char SubID_1 [4];
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumOfChan;
    uint32_t SamplesPerSec;
    uint32_t bytesPerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char SubID_2 [4];
    uint32_t SubSize_2;
} WAVHeader;

#pragma pack(pop)

const char * RIFF = "RIFF";
const char * WAVE = "WAVE";
const char * fmt = "fmt";

}

AudioSource::AudioSource(const std::string &inputFile):
  _inputFile(inputFile),
  _sampleRate(0),
  _bitsPerSample(0),
  _channels(0)
{
  SimpleLogger::instance() << "Input file: " << _inputFile << "\n";
}

gnsdk_uint32_t AudioSource::SourceInit()
{
  _wavFile.open(_inputFile.c_str(), std::ios_base::in | std::ios_base::binary);
  if (_wavFile.fail())
  {
      return -1;
  }
  else
  {
    WAVHeader header = {};

    _wavFile.read(reinterpret_cast<char*>(&header), sizeof(header));

    _sampleRate = header.SamplesPerSec;
    _bitsPerSample = header.bitsPerSample;
    _channels = header.NumOfChan;
    

    SimpleLogger::instance() << "Sample Rate: " << _sampleRate << "\n";
    SimpleLogger::instance() << "Bits per sample: " << _bitsPerSample << "\n";
    SimpleLogger::instance() << "Channels: " << _channels << "\n";

    return 0;
  }
}

void AudioSource::SourceClose()
{
  _wavFile.close();
}

gnsdk_uint32_t AudioSource::SamplesPerSecond()
{
  return _sampleRate;
}

gnsdk_uint32_t AudioSource::SampleSizeInBits()
{
  return _bitsPerSample;
}

gnsdk_uint32_t AudioSource::NumberOfChannels()
{
  return _channels;
}

gnsdk_size_t AudioSource::GetData(gnsdk_byte_t* dataBuffer, gnsdk_size_t dataSize)
{
  _wavFile.read((gnsdk_char_t*)dataBuffer, dataSize);
  return _wavFile.gcount();
}

}