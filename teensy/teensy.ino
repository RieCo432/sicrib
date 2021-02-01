#include <ArduinoJson.h>
#include "Room.cpp"
//#include <FastLED.h>
#define HWSerial Serial1

//#define NUM_LEDS 790
//#define DATA_PIN 11
//#define CLOCK_PIN 10

DynamicJsonDocument fx_config(2048);
//CRGB leds[NUM_LEDS];

Room living_room;

const char* hue_color_span_rainbow = "hue_color_span_rainbow";
const char* hue_color_span_cycle = "hue_color_span_cycle";
const char* christmas_animation = "christmas_animation";
const char* static_color = "static";
const char* rave = "rave";
const char* audio = "audio";
const char* none = "none";

char* effect_name = new char[16];
unsigned long StartTime = millis();
unsigned long lastUpdate = millis();
unsigned long UpdateInterval = 0;
uint8_t hue = 0;

void setup() {
  HWSerial.setTX(1);
  HWSerial.setRX(0);
  HWSerial.begin(9600);
  // Serial.begin(9600);
  //FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  if (HWSerial.available() > 0) {
    String received = HWSerial.readStringUntil('\n');
    // HWSerial.println(received);
    // Serial.println(received);
    deserializeJson(fx_config, received);
    effect_name =  fx_config["effect"];
    living_room.build_list_circle_horizontal(true, true);
    HWSerial.println(effect_name);
    // Serial.println(effect_name);
    StartTime = millis();
    HWSerial.flush(); 
  }

  if (strcmp(effect_name, hue_color_span_rainbow) == 0) {
    long unsigned time_passed = millis() - StartTime;
    float time_in_secs = (float) time_passed / 1000.0f;
    living_room.set_hue_color_span_rainbow(0, 360, 20, 1 , time_in_secs);
    
  } else if (strcmp(effect_name, hue_color_span_cycle) == 0){
    living_room.set_all(hue);
    hue++;
    hue %= 255;
  } else if (strcmp(effect_name, christmas_animation) == 0){
    
  } else if (strcmp(effect_name, static_color) == 0){
    
  } else if (strcmp(effect_name, rave) == 0){
    
  } else if (strcmp(effect_name, audio) == 0){
    
  } else if (strcmp(effect_name, none) == 0){
    living_room.turn_off();
  }
  if (millis() - lastUpdate >= UpdateInterval) {
    living_room.update();
    lastUpdate = millis();
  }
}
