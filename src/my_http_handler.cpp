#include "my_http_handler.hpp"
#include "passwords.hpp"
#include "network_param.hpp"
#include <base64.h>
#include <Arduino.h>


enum DataType {
    STRING,
    NUMERIC
};

void HTTPHandler::add_headers(){
    https.addHeader("Content-Type", content_type); 
    https.addHeader("Authorization", "Bearer " + String(chatgpt_token));
}



void HTTPHandler::add_element_to_payload(String& payload, String name, String value, bool use_quotes_for_value = true){
    if (!payload.isEmpty()){
        payload += ", ";
    }
    if (use_quotes_for_value){
        payload += "\"" + name + "\": \"" + value + "\"";
    }
    else{
        payload += "\"" + name + "\": " + value;
    }
}

String HTTPHandler::create_payload(String question){
    String payload;

    add_element_to_payload(payload, "prompt", question);
    add_element_to_payload(payload, "max_tokens", max_tokens, false);
    add_element_to_payload(payload, "model", model);
    add_element_to_payload(payload, "temperature", temperature, false);

    return "{" + payload + "}";
}

bool HTTPHandler::post(String payload){
    Serial.printf("[HTTPS] POST... Q: %s\n", payload.c_str());

    int httpCode = https.POST(payload);
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        Serial.printf("[HTTPS] POST... Succeeded\n");
        return true;
    }
    else {
        Serial.printf("[HTTPS] POST... Failed, error %i, %s\n", httpCode, https.getString().c_str());
        return false;
    }
}

String HTTPHandler::extact_answer(){
    int newline_sign_size = 2;
    String payload = https.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    String answer = doc["choices"][0]["text"];
    answer = answer.substring(newline_sign_size);
    Serial.printf("[HTTPS] POST... A: %s\n", answer.c_str());
    return answer;
}

String HTTPHandler::get_chatgpt_answer(String question){
    String answer;

    add_headers();
    String payload = create_payload(question);
    if(post(payload)){
        answer = extact_answer();
    }
    return answer;
}

String HTTPHandler::get_audio_as_bytes(Audio* audio)
{
    String enocded_audio;
    String enc = base64::encode(audio->paddedHeader, sizeof(audio->paddedHeader));
    enc.replace("\n", "");  // delete last "\n"
    enocded_audio += enc;
    char** wavData = audio->wavData;
    Serial.print(enc);
    for (int j = 0; j < audio->wavDataSize / audio->dividedWavDataSize; ++j) {
        enc = base64::encode((byte*)wavData[j], audio->dividedWavDataSize);
        enc.replace("\n", "");// delete last "\n"    // HttpBody2

        //Serial.print(enc);
        //enocded_audio += enc;
    }
    return enocded_audio;
}

String HTTPHandler::get_audio_string(Audio* audio)
{
    https.addHeader("Content-Type", content_type); 
    https.addHeader("X-goog-api-key", String(ApiKey));

    String config;
    add_element_to_payload(config, "encoding", "LINEAR16");
    add_element_to_payload(config, "sampleRateHertz", "8000", false);
    add_element_to_payload(config, "languageCode", "pl-PL");
    add_element_to_payload(config, "enableWordTimeOffsets", "false", false);
    config = "\"config\": {" + config + "},";

    String audio_payload;
    String audio_bytes = get_audio_as_bytes(audio);
    add_element_to_payload(audio_payload, "content", audio_bytes);
    // add_element_to_payload(audio_payload, "uri", "gs://cloud-samples-tests/speech/brooklyn.flac");
    // audio_payload.remove(audio_payload.length() - 1);
    audio_payload = "\"audio\": {" + audio_payload + "}";

    String payload;
    payload = "{" + config + audio_payload + "}";
    Serial.print("Free RAM before post: ");
    Serial.println(ESP.getFreeHeap() / 1024);
    post(payload);

    Serial.print("Answer: ");
    String payload_ans = https.getString();
    Serial.println(payload_ans);
    return payload_ans;
}

HTTPHandler::HTTPHandler(){
    this->max_tokens = max_tokens;

    Serial.print("[HTTPS] begin...");
    bool status = https.begin(google_endpoint);
    if(!status){
        Serial.printf("[HTTPS] Unable to connect");
    }
}

HTTPHandler::~HTTPHandler(){
    https.end();
}