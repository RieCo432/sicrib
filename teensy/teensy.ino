#include <ArduinoJson.h>
#include "Room.cpp"
#define HWSerial Serial1


DynamicJsonDocument fx_config(2048);

Room living_room;

const char* hue_color_span_rainbow = "hue_color_span_rainbow";
const char* hue_color_span_cycle = "hue_color_span_cycle";
const char* christmas_animation = "christmas_animation";
const char* static_color = "static";
const char* rave = "rave";
const char* audio = "audio";
const char* none = "none";
const char* horizontal = "horizontal";
const char* vertical = "vertical";

bool enabled = false;

char* effect_name = new char[16];

char* hue_color_span_direction = new char[12];
float hue_color_span_starting_hue = 0.0;
float hue_color_span_ending_hue = 360.0;
float hue_color_span_period = 60.0;
int hue_color_span_compress = 1;

uint8_t static_red = 255;
uint8_t static_green = 255;
uint8_t static_blue = 255;

bool rave_include_n = true;
bool rave_include_ne = true;
bool rave_include_e = true;
bool rave_include_se = true;
bool rave_include_s = true;
bool rave_include_sw = true;
bool rave_include_w = true;
bool rave_include_nw = true;
bool rave_include_red = true;
bool rave_include_green = true;
bool rave_include_blue = true;
bool rave_include_yellow = true;
bool rave_include_turquoise = true;
bool rave_include_magenta = true;
bool rave_include_white = true;
bool rave_include_black = true;
int rave_min_edges = 0;
int rave_max_edges = 8;

bool include_vertical = true;
bool include_horizontal = true;

unsigned long start_time = millis();

void setup() {
  HWSerial.setTX(1);
  HWSerial.setRX(0);
  HWSerial.begin(9600);

  Serial.begin(9600);
}

void loop() {
  if (HWSerial.available() > 0) {
    String received = HWSerial.readStringUntil('\n');
    deserializeJson(fx_config, received);
    effect_name =  fx_config["effect"];

    Serial.println(effect_name);
    
    if (strcmp(effect_name, hue_color_span_rainbow) == 0 || strcmp(effect_name, hue_color_span_cycle) == 0) {
      hue_color_span_direction = fx_config["effect_params"]["hue_color_span"]["direction"];
      hue_color_span_starting_hue = fx_config["effect_params"]["hue_color_span"]["starting_hue"];
      hue_color_span_ending_hue = fx_config["effect_params"]["hue_color_span"]["ending_hue"];
      hue_color_span_period = fx_config["effect_params"]["hue_color_span"]["period"];
      hue_color_span_compress = fx_config["effect_params"]["hue_color_span"]["compress"];
      
      include_vertical = fx_config["effect_params"]["hue_color_span"]["include_vertical"];
      include_horizontal = fx_config["effect_params"]["hue_color_span"]["include_horizontal"];
      
      if (strcmp(effect_name, hue_color_span_rainbow) == 0) {
        if (strcmp(hue_color_span_direction, vertical) == 0) {
          living_room.build_list_straight_vertical(include_vertical, include_horizontal);
        } else {
          living_room.build_list_circle_horizontal(include_vertical, include_horizontal);
        }
      } else {
        living_room.build_list_single_element(include_vertical, include_horizontal);
      }
      
    } else if (strcmp(fx_config["effect"], static_color) == 0) {
      static_red = fx_config["effect_params"]["static"]["red"];
      static_green = fx_config["effect_params"]["static"]["green"];
      static_blue = fx_config["effect_params"]["static"]["blue"];
    }
    
    
    // HWSerial.println(effect_name);
    // Serial.println(effect_name);
    start_time = millis();
    HWSerial.flush(); 
  }

  if (strcmp(effect_name, hue_color_span_rainbow) == 0 && fx_config["enabled"]) {
    
    living_room.set_hue_color_span_rainbow(hue_color_span_starting_hue, hue_color_span_ending_hue, hue_color_span_period, hue_color_span_compress , (float) (millis() - start_time) / 1000.0f);
    
  } else if (strcmp(effect_name, hue_color_span_cycle) == 0 && fx_config["enabled"]){

    living_room.set_hue_color_span_cycle(hue_color_span_starting_hue, hue_color_span_ending_hue, hue_color_span_period, (float) (millis() - start_time) / 1000.0f);
    
  } else if (strcmp(effect_name, christmas_animation) == 0 && fx_config["enabled"]){
    
  } else if (strcmp(effect_name, static_color) == 0 && fx_config["enabled"]){

    living_room.set_all_rgb(static_red, static_green, static_blue);
    
  } else if (strcmp(effect_name, rave) == 0 && fx_config["enabled"]){
    
  } else if (strcmp(effect_name, audio) == 0 && fx_config["enabled"]){
    
  } else if (strcmp(effect_name, none) == 0 || !fx_config["enabled"]){
    living_room.turn_off();
  }
  living_room.update();
}
