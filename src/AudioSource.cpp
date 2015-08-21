#include "AudioSource.h"

namespace AudioFingerprint
{

namespace
{

typedef struct  WAV_HEADER{
    char                RIFF[4];        // RIFF Header      Magic header
    unsigned long       ChunkSize;      // RIFF Chunk Size  
    char                WAVE[4];        // WAVE Header      
    char                fmt[4];         // FMT header       
    unsigned long       Subchunk1Size;  // Size of the fmt chunk                                
    unsigned short      AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    unsigned short      NumOfChan;      // Number of channels 1=Mono 2=Sterio                   
    unsigned long       SamplesPerSec;  // Sampling Frequency in Hz                             
    unsigned long       bytesPerSec;    // bytes per second 
    unsigned short      blockAlign;     // 2=16-bit mono, 4=16-bit stereo 
    unsigned short      bitsPerSample;  // Number of bits per sample      
    char                Subchunk2ID[4]; // "data"  string   
    unsigned long       Subchunk2Size;  // Sampled data length    

}WAVHeader; 

}

AudioSource::AudioSource(const std::string &inputFile):
  _inputFile(inputFile),
  _sampleRate(0),
  _bitsPerSample(0),
  _channels(0)
{
  std::cout << "Input file: " << _inputFile << std::endl;
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
    WAVHeader header;

    std::cout << "Reading WAV file header..." << std::endl;

    _wavFile.read(&header, sizeof(header));
    _sampleRate = header.SamplesPerSec;
    _bitsPerSample = header.bitsPerSample;
    _channels = header.NumOfChan;

    std::cout << "Sample Rate: " << _sampleRate << std::endl;
    std::cout << "Bits per sample: " << _bitsPerSample << std::endl;
    std::cout << "Channels: " << _channels << std::endl;

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