#ifndef HTTP_HANDLER
#define HTTP_HANDLER
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <my_audio.hpp>


class HTTPHandler{
private:
    HTTPClient https;
    // https://platform.openai.com/docs/models/model-endpoint-compatibility
    String endpoint = "https://api.openai.com/v1/completions";
    String google_endpoint = "https://speech.googleapis.com/v1/speech:recognize";
    String model = "gpt-3.5-turbo-instruct";
    String inputText = "Hello, ChatGPT!";
    String content_type = "application/json";
    String max_tokens = "40";
    String temperature = "0.2";
    
    void add_headers();
    void add_element_to_payload(String&, String, String, bool);
    String create_payload(String);
    bool post(String);
    String extact_answer();
    String get_audio_as_bytes(Audio*);


public:
    HTTPHandler();
    ~HTTPHandler();
    String get_chatgpt_answer(String);
    String get_audio_string(Audio*);
};

#endif // HTTP_HANDLER