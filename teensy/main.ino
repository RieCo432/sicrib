#include <ArduinoJson.h>
#include <FastLED.h>

#define NUM_LEDS 790
#define DATA_PIN 11
#define CLOCK_PIN 12

DynamicJsonDocument fx_config(2048);
CRGB leds[NUM_LEDS];

const char* hue_color_span_rainbow = "hue_color_span_rainbow";
const char* hue_color_span_cycle = "hue_color_span_cycle";
const char* christmas_animation = "christmas_animation";
const char* static_color = "static";
const char* rave = "rave";
const char* audio = "audio";
const char* none = "none";

char* effect_name = new char[16];


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  if (Serial.available() > 0) {
    deserializeJson(fx_config, Serial.readStringUntil('\n'));
    effect_name =  fx_config["effect"];
    //Serial.println(effect_name);
  }

  if (strcmp(effect_name, hue_color_span_rainbow) == 0) {
    
  } else if (strcmp(effect_name, hue_color_span_cycle) == 0){
    
  } else if (strcmp(effect_name, christmas_animation) == 0){
    
  } else if (strcmp(effect_name, static_color) == 0){
    
  } else if (strcmp(effect_name, rave) == 0){
    
  } else if (strcmp(effect_name, audio) == 0){
    
  } else if (strcmp(effect_name, none) == 0){
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);    
    }
    LEDS.show();
  }
  Serial.flush(); 
}
