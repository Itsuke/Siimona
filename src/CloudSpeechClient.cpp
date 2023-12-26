// #include "CloudSpeechClient.hpp"
// #include "network_param.hpp"
// #include <base64.h>
// #include <ArduinoJson.h>
// #define USE_SERIAL Serial
// #include <Arduino.h>
// #include <HTTPClient.h>
// //#define uart_en 15
//  #define led_3 4
//  #define led_1 15
// #define led_2 2
// //#include <SoftwareSerial.h>
// ////SoftwareSerial (D4, D2);
// //const char* chatgpt_token = "Your_ChatGPT_Token";
// CloudSpeechClient::CloudSpeechClient(Authentication authentication) {
//   this->authentication = authentication;
//   WiFi.begin(ssid, password);
//  //  while (WiFi.status() == WL_CONNECTED){ digitalWrite(led_3,1);}
//   while (WiFi.status() != WL_CONNECTED) delay(1000);
//   client.setCACert(root_ca);
 
//   int is_connected = client.connect(server, 443);
//   Serial.print("Is connected ?: ");
//   Serial.println(is_connected);
//   if (!is_connected) Serial.println("Connection failed!"); digitalWrite(led_3,1);digitalWrite(led_1,0);digitalWrite(led_2,0);
// }

// String ans;

// CloudSpeechClient::~CloudSpeechClient() {
//   client.stop();
//   WiFi.disconnect();
// }

// void CloudSpeechClient::PrintHttpBody2(Audio* audio)
// {
//   String enc = base64::encode(audio->paddedHeader, sizeof(audio->paddedHeader));
//   enc.replace("\n", "");  // delete last "\n"
//   client.print(enc);      // HttpBody2
//   char** wavData = audio->wavData;
//   for (int j = 0; j < audio->wavDataSize / audio->dividedWavDataSize; ++j) {
//     enc = base64::encode((byte*)wavData[j], audio->dividedWavDataSize);
//     enc.replace("\n", "");// delete last "\n"
//     size_t result = client.print(enc);    // HttpBody2er
//   }
// }

// void CloudSpeechClient::Transcribe(Audio* audio) {
//   String HttpBody1 = "{\"config\":{\"encoding\":\"LINEAR16\",\"sampleRateHertz\":16000,\"languageCode\":\"en-IN\"},\"audio\":{\"uri\":\"";
//   String HttpBody3 = "\"}}\r\n\r\n";
//   int httpBody2Length = (audio->wavDataSize + sizeof(audio->paddedHeader)) * 4 / 3; // 4/3 is from base64 encoding
//   String ContentLength = String(HttpBody1.length() + httpBody2Length + HttpBody3.length());
//   String HttpHeader;

//   // Construct HTTP header
//   HttpHeader = String("POST /v1/speech:recognize?key=") + ApiKey +
//                String(" HTTP/1.1\r\nHost: speech.googleapis.com\r\nContent-Type: application/json\r\nContent-Length: ") + ContentLength + String("\r\n\r\n");

//   log_d("Was here -1");
//   // Send the HTTP request
//   client.print(HttpHeader);
//   client.print(HttpBody1);
//   client.print("gs://cloud-samples-tests/speech/brooklyn.flac");
//   //PrintHttpBody2(audio);
//   client.print(HttpBody3);
//   log_d("Was here 0");

//   // Wait for the server to close the connection
//   while (client.connected()) {
//     delay(10000);
//     break;
//   }

//   log_d("Was here");

//   // Read the response
//   String response;
//   while (client.available()) {
//     char temp = client.read();
//     response += temp;
//   }
//   log_d("Was here 2");

//   // Close the connection
//   client.stop();

//   // Extract the JSON part of the response
//   int position = response.indexOf('{');
//   String json_data = response.substring(position);

//   // Print the JSON data for debugging
//   Serial.print("Json data--");
//   Serial.print(json_data);

//   // Store the JSON data in the 'ans' variable (assuming 'ans' is a class variable)
//   ans = json_data;
// }