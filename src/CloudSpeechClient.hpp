// #ifndef _CLOUDSPEECHCLIENT_HPP
// #define _CLOUDSPEECHCLIENT_HPP
// #include <WiFiClientSecure.h>
// #include "my_audio.hpp"

// enum Authentication {
//   USE_ACCESSTOKEN,
//   USE_APIKEY
// };

// class CloudSpeechClient {
//   WiFiClientSecure client;
//   void PrintHttpBody2(Audio* audio);
//   Authentication authentication;

// public:
//   CloudSpeechClient(Authentication authentication);
//   ~CloudSpeechClient();
//   void Transcribe(Audio* audio);
// };

// #endif // _CLOUDSPEECHCLIENT_HPP