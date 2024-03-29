#include <ArduinoJson.h>
#include "Room.cpp"
#define HWSerial Serial1
#include <Audio.h>

#define RX_BUFFER_SIZE 2048

AudioInputAnalog         input;
AudioAnalyzeFFT1024    fft;
AudioOutputI2S         audioOutput;        // audio shield: headphones & line-out

AudioConnection patchCord1(input, 0, fft, 0);
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

const int myInput = AUDIO_INPUT_LINEIN;

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

char rx_buffer[RX_BUFFER_SIZE] = {'\0'};
char rx_total[RX_BUFFER_SIZE] = {'\0'};
int rx_buffer_index = 0;


void setup() {
  
  HWSerial.setTX(1);
  HWSerial.setRX(0);
  HWSerial.begin(9600);

  AudioMemory(24);

  Serial.begin(9600);
  Serial.println("Setup done!");
}

void loop() {
  // delay(100);
  // Serial.print(".");
  /*if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      rx_buffer[rx_buffer_index] = Serial.read();
      if (rx_buffer[rx_buffer_index] == '\n') {
        deserializeJson(fx_config, rx_buffer);
        effect_name =  fx_config["effect"];
        Serial.print("Effect: ");
        Serial.println(effect_name);
        Serial.println();
        for (int i = 0; i < RX_BUFFER_SIZE; i++) rx_buffer[i] = '\0'; 
        rx_buffer_index = 0;
      } else rx_buffer_index++;
    }
  }*/
  if (fft.available()) {
    //Serial.print(millis()    );
    //Serial.print("FFT: ");
    bins[0] =  fft.read(2, 3);
    bins[1] =  fft.read(4, 6) - 0.0005;
    bins[2] =  fft.read(7, 10) - 0.0005;
    bins[3] =  fft.read(11, 15) - 0.001;
    bins[4] =  fft.read(16, 22) - 0.002;
    bins[5] =  fft.read(23, 32) - 0.01;
    bins[6] =  fft.read(33, 46) - 0.01;
    bins[7] =  fft.read(47, 66) - 0.004;
    bins[8] = fft.read(67, 93) - 0.003;
    bins[9] = fft.read(94, 131) - 0.004;

    for(int i = 0; i < 10; i++) {
      if (bins[i] < 0.0012) bins[i] = 0.00;
      //Serial.print(1000 * bins[i]);
      //Serial.print("  ");
    }
  }
  if (HWSerial.available() > 0) {
        while (HWSerial.available() > 0) {
          rx_buffer[rx_buffer_index] = HWSerial.read();
          if (rx_buffer[rx_buffer_index] == (byte) '\n') {
            strcpy(rx_total, rx_buffer);
            Serial.println(rx_total);
            deserializeJson(fx_config, rx_total);

            effect_name = fx_config["effect"];
            
            for (int i = 0; i < RX_BUFFER_SIZE; i++) rx_buffer[i] = '\0';
            rx_buffer_index = 0;
            
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
            
            } else if (strcmp(effect_name, static_color) == 0) {
              static_red = fx_config["effect_params"]["static"]["red"];
              static_green = fx_config["effect_params"]["static"]["green"];
              static_blue = fx_config["effect_params"]["static"]["blue"];
            }
          start_time = millis();
          } else rx_buffer_index++;
      }
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

    bool show_peaks = fx_config["effect_params"]["audio"]["show_peaks"];
    float starting_base_hue = fx_config["effect_params"]["audio"]["starting_base_hue"];
    float ending_base_hue = fx_config["effect_params"]["audio"]["ending_base_hue"];
    float cycling_period = fx_config["effect_params"]["audio"]["cycling_period"];
    float low_hue_offset = fx_config["effect_params"]["audio"]["low_hue_offset"];
    float high_hue_offset = fx_config["effect_params"]["audio"]["high_hue_offset"];
    float peak_hue_offset = fx_config["effect_params"]["audio"]["peak_hue_offset"];
    char gradient_bar_length_mode[16] = {'\0'};
    strcpy(gradient_bar_length_mode, fx_config["effect_params"]["audio"]["gradient_bar_length_mode"]);
    float gradient_bar_length = fx_config["effect_params"]["audio"]["gradient_bar_length"];
    char bar_root[8] = {'\0'};
    strcpy(bar_root, fx_config["effect_params"]["audio"]["bar_root"]);

    /*Serial.print("peaks: ");
    Serial.print(show_peaks ? "true" : "false");
    Serial.print(" starting: ");
    Serial.print(starting_base_hue);
    Serial.print(" ending: ");
    Serial.print(ending_base_hue);
    Serial.print(" period: ");
    Serial.print(cycling_period);
    Serial.print(" low: ");
    Serial.print(low_hue_offset);
    Serial.print(" high: ");
    Serial.print(high_hue_offset);
    Serial.print(" peak: ");
    Serial.print(peak_hue_offset);
    Serial.print(" root: ");
    Serial.print(bar_root);
    Serial.println();*/

    /*Serial.print("Mode");
    Serial.print(gradient_bar_length_mode);
    Serial.print("Length");
    Serial.print(gradient_bar_length);
    Serial.println();*/
    
    living_room.audio_effect(bins, NUM_BINS, bass_bins, middle_bins, high_bins, show_peaks, starting_base_hue, ending_base_hue, cycling_period, low_hue_offset, high_hue_offset, peak_hue_offset, gradient_bar_length_mode, gradient_bar_length, bar_root, (float) (millis() - start_time) / 1000.0f);
    
  } else if (strcmp(effect_name, none) == 0 || !fx_config["enabled"]){
    living_room.turn_off();
  };
  float br = fx_config["brightness"];
  living_room.set_brightness(br);
  living_room.update();
}
