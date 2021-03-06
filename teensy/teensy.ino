#include <ArduinoJson.h>
#include "Room.cpp"
#define HWSerial Serial1
#define PicoSerial Serial2

DynamicJsonDocument fx_config(2048);

Room living_room;

const char* hue_color_span_rainbow = "hue_color_span_rainbow";
const char* hue_color_span_cycle = "hue_color_span_cycle";
const char* christmas_animation = "christmas_animation";
const char* static_color = "static";
const char* alis_random_equilibrium = "alis_random_equilibrium";
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
int ravecount;

float bins[NUM_BINS];

void setup() {
  HWSerial.setTX(1);
  HWSerial.setRX(0);
  HWSerial.begin(9600);

  PicoSerial.setTX(8);
  PicoSerial.setRX(7);
  PicoSerial.begin(115200);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n');
    deserializeJson(fx_config, received);
    effect_name =  fx_config["effect"];

    Serial.println(effect_name);
  }
  if (PicoSerial.available() > 0) {
    String str = PicoSerial.readStringUntil('\n');
    char * rec = str.c_str();
    char * strtokIndex;
    strtokIndex = strtok(rec, ",");
    bins[0] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[1] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[2] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[3] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[4] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[5] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[6] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[7] = atof(strtokIndex);
    strtokIndex = strtok(NULL, ",");
    bins[8] = atof(strtokIndex);
    strtokIndex = strtok(NULL, "\n");
    bins[9] = atof(strtokIndex);    
  }
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

  living_room.turn_off();

  if (strcmp(effect_name, hue_color_span_rainbow) == 0 && fx_config["enabled"]) {
    
    living_room.set_hue_color_span_rainbow(hue_color_span_starting_hue, hue_color_span_ending_hue, hue_color_span_period, hue_color_span_compress , (float) (millis() - start_time) / 1000.0f);
    
  } else if (strcmp(effect_name, hue_color_span_cycle) == 0 && fx_config["enabled"]){

    living_room.set_hue_color_span_cycle(hue_color_span_starting_hue, hue_color_span_ending_hue, hue_color_span_period, (float) (millis() - start_time) / 1000.0f);
    
  } else if (strcmp(effect_name, christmas_animation) == 0 && fx_config["enabled"]){
    
  } else if (strcmp(effect_name, static_color) == 0 && fx_config["enabled"]){

    living_room.set_all_rgb(static_red, static_green, static_blue);
    
  } else if (strcmp(effect_name, alis_random_equilibrium) == 0 && fx_config["enabled"]){
    ravecount++;
    if (ravecount == 1000) {
      ravecount =0;
      // living_room.turn_off();
    }

    if (ravecount%3 ==0) {
      for (int i = 0; i < 4; i++) {
        int randcolor1 = random(100);
        int randcolor2 = random(100);
        int randcolor3 = random(40);
        int randled = random(790);
        living_room.set_one_led(255,randcolor2,randcolor3,randled);
      }
    }
    if (ravecount%3 ==1) {
      for (int i = 0; i < 4; i++) {
        int randcolor1 = random(100);
        int randcolor2 = random(255);
        int randcolor3 = random(40);
        int randled = random(790);
        living_room.set_one_led(randcolor1,255,randcolor3,randled);
      }
    }
    if (ravecount%3 ==2) {
      for (int i = 0; i < 4; i++) {
        int randcolor1 = random(100);
        int randcolor2 = random(100);
        int randcolor3 = random(120);
        int randled = random(790);
        living_room.set_one_led(randcolor1,randcolor2,255,randled);
      }

      for (int i = 0; i < 4; i++) {
        int randled = random(790);
        living_room.set_one_led(255,255,255,randled);
      }
      for (int i = 0; i < 8; i++) {
        int randled = random(790);
        living_room.set_one_led(0,0,0,randled);
      }  
    }
  } else if (strcmp(effect_name, rave) == 0 && fx_config["enabled"]){
 
  } else if (strcmp(effect_name, audio) == 0 && fx_config["enabled"]){

    int bass_bins = fx_config["effect_params"]["audio"]["bass_bins"];
    int middle_bins = fx_config["effect_params"]["audio"]["middle_bins"];
    int high_bins = fx_config["effect_params"]["audio"]["high_bins"];

    living_room.audio_effect(bins, NUM_BINS, bass_bins, middle_bins, high_bins);
    
  } else if (strcmp(effect_name, none) == 0 || !fx_config["enabled"]){
    living_room.turn_off();
  }
  living_room.update();
}
