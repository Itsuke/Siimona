#ifndef _MY_AUDIO_HPP
#define _MY_AUDIO_HPP

#include <Arduino.h>
#include "I2S.hpp"

// 16bit, monoral, 16000Hz,  linear PCM
class Audio {

  static const short headerSize = 44;
  static const short i2sBufferSize = 12000; // 12000/8 = 1500 * 30 = 45000
  char i2sBuffer[i2sBufferSize];
  void CreateWavHeader(byte* header, int waveDataSize);

public:
  I2S* i2s;
  static const int wavDataSize = 90000;                   // It must be multiple of dividedWavDataSize. Recording time is about 1.9 second.
  static const short dividedWavDataSize = i2sBufferSize/4; // 3000
  char** wavData;                                         // It's divided. Because large continuous memory area can't be allocated in esp32.
  byte paddedHeader[headerSize + 4] = {0};                // The size must be multiple of 3 for Base64 encoding. Additional byte size must be even because wave data is 16bit.

  Audio();
  ~Audio();
  void Record();
};

#endif // _MY_AUDIO_HPP