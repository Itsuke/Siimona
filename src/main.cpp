#include <Arduino.h>
// Include I2S driver
#include <driver/i2s.h>
#include <my_audio.hpp>
// #include <CloudSpeechClient.hpp>
#include "my_http_handler.hpp"
#include <wi_fi_handler.hpp>
 
// Connections to INMP441 I2S microphone
#define I2S_WS 25
#define I2S_SD 32
#define I2S_SCK 33
 
// Use I2S Processor 0
#define I2S_PORT I2S_NUM_0
 
// Define input buffer length
#define bufferLen 64
int16_t sBuffer[bufferLen];

#define no_of_record_per_sec 475
#define ten_seconds_of_data_recording 10 * no_of_record_per_sec
int16_t recording[ten_seconds_of_data_recording];
int global_counter = 0;
float mean = 0;
WiFiHandler wifi = WiFiHandler();


void print_memory() {
  Serial.println("ESP32 Memory Information:");
  Serial.print("Flash Size: ");
  Serial.print(ESP.getFlashChipSize() / (1024 * 1024), 2); // Convert to MB
  Serial.println("MB");
  Serial.print("Free Flash: ");
  Serial.print(ESP.getFreeSketchSpace() / 1024); // Remain in KB
  Serial.println("KB");
  Serial.print("RAM Size: ");
  Serial.print(ESP.getHeapSize() / 1024); // Convert to KB
  Serial.println("KB");
  Serial.print("Free RAM: ");
  Serial.print(ESP.getFreeHeap() / 1024); // Convert to KB
  Serial.println("KB");
}
 
HTTPHandler http;
void setup() {
  Serial.begin(115200);

  delay(1000);

  print_memory();
  wifi.connect(WIFI_STA);

  Serial.println("\r\nRecord start!\r\n");
  delay(2000);
  Serial.println("\r\nRecord start!\r\n");
  Audio* audio = new Audio();

  
  audio->Record();
  Serial.print("Free RAM 3: ");
  Serial.println(ESP.getFreeHeap() / 1024);
  Serial.println("Recording Completed. Now Processing...");

  http.get_audio_string(audio);

  // CloudSpeechClient* cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);
  // cloudSpeechClient->Transcribe(audio);
  // delete cloudSpeechClient;
  delete audio;
}
 
void loop() {


  // // False print statements to "lock range" on serial plotter display
  // // Change rangelimit value to adjust "sensitivity"
  // int rangelimit = 3000;
  // Serial.print(global_counter);
  // Serial.print(" ");
  // Serial.print(rangelimit * -1);
  // Serial.print(" ");
  // Serial.print(rangelimit);
  // Serial.print(" ");
 
  // // Get I2S data and place in data buffer
  // size_t bytesIn = 0;
  // esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);
 
  // if (result == ESP_OK)
  // {
  //   // Read I2S data buffer
  //   int16_t samples_read = bytesIn / 8;
  //   if (samples_read > 0) {
  //     float mean = 0;
  //     for (int16_t i = 0; i < samples_read; ++i) {
  //       mean += (sBuffer[i]);
  //     }
 
  //     // Average the data reading
  //     mean /= samples_read;
 
  //     // Print to serial plotter
  //     Serial.println(mean);
  //   }
  // }
  
  // if (global_counter == ten_seconds_of_data_recording){
  //   Serial.print(" ");
  // }
  // else{
  //   recording[global_counter] = mean;
  //   global_counter += 1;
  // }
}