#pragma once

#include "gnsdk.hpp"

#include <fstream>
#include <string>

namespace AudioFingerprint
{

using namespace gracenote;
using namespace gracenote::musicid;

class AudioSource : public IGnAudioSource
{
  std::string _inputFile;
  std::ifstream  _wavFile;
  gnsdk_uint32_t _sampleRate;
  gnsdk_uint32_t _bitsPerSample;
  gnsdk_uint32_t _channels;

public:
  AudioSource(const std::string &inputFile);
  gnsdk_uint32_t SourceInit() override;
  void SourceClose() override;
  gnsdk_uint32_t SamplesPerSecond() override;
  gnsdk_uint32_t SampleSizeInBits() override;
  gnsdk_uint32_t NumberOfChannels() override;
  gnsdk_size_t GetData(gnsdk_byte_t* dataBuffer, gnsdk_size_t dataSize) override;
};

}