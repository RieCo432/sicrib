//#define FASTLED_FORCE_SOFTWARE_SPI
#include <FastLED.h>
#include <string>
#include <math.h>
// #include "arduinoFFT.h"

#define DATA_PIN 11
#define CLOCK_PIN 13

#define NUM_LEDS        790
#define VERTICAL_LENGTH  69
#define SHORT_LENGTH    108
#define LONG_LENGTH     149
#define SAMPLES 1024
#define NUM_BINS 10


class Room {
	public:
		int south_east[70] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, -1};
		int south[150] = {69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, -1};
		int south_west[70] = {218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, -1};
		int west[109] = {287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, -1};
		int north_west[70] = {395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, -1};
		int north[150] = {464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 512, 513, 514, 515, 516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 526, 527, 528, 529, 530, 531, 532, 533, 534, 535, 536, 537, 538, 539, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 573, 574, 575, 576, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602, 603, 604, 605, 606, 607, 608, 609, 610, 611, 612, -1};
		int north_east[70] = {613, 614, 615, 616, 617, 618, 619, 620, 621, 622, 623, 624, 625, 626, 627, 628, 629, 630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 640, 641, 642, 643, 644, 645, 646, 647, 648, 649, 650, 651, 652, 653, 654, 655, 656, 657, 658, 659, 660, 661, 662, 663, 664, 665, 666, 667, 668, 669, 670, 671, 672, 673, 674, 675, 676, 677, 678, 679, 680, 681, -1};
		int east[109] = {682, 683, 684, 685, 686, 687, 688, 689, 690, 691, 692, 693, 694, 695, 696, 697, 698, 699, 700, 701, 702, 703, 704, 705, 706, 707, 708, 709, 710, 711, 712, 713, 714, 715, 716, 717, 718, 719, 720, 721, 722, 723, 724, 725, 726, 727, 728, 729, 730, 731, 732, 733, 734, 735, 736, 737, 738, 739, 740, 741, 742, 743, 744, 745, 746, 747, 748, 749, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759, 760, 761, 762, 763, 764, 765, 766, 767, 768, 769, 770, 771, 772, 773, 774, 775, 776, 777, 778, 779, 780, 781, 782, 783, 784, 785, 786, 787, 788, 789, -1};
			
		int * all_clockwise[8] = {south_east, south, south_west, west, north_west, north, north_east, east};
		int * vertical_clockwise[4] = {south_east, south_west, north_west, north_east};
		int * horizontal_clockwise[4] = {south, west, north, east};
			
		int * list_of_leds[NUM_LEDS];
		int list_of_leds_length;

    CRGB leds[NUM_LEDS];

    int bin_peaks[NUM_BINS];
    int led_count[NUM_BINS];

    Room() {
      FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    }

    void turn_off() {
       for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(0, 0, 0);    
      }
    }
    
    void set_all_hue(uint8_t hue) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue, 255, 255);
      }
    }

    void set_all_rgb(uint8_t red, uint8_t green, uint8_t blue) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(red, green, blue);
      }
    }
    
    void set_one_led(uint8_t red, uint8_t green, uint8_t blue, int lednum) {
        leds[lednum] = CRGB(red, green, blue);
    }
    void update(){
      LEDS.show();
    }
	
		void build_list_circle_horizontal(bool include_vertical, bool include_horizontal) {
      list_of_leds_length = 0;
      if (include_vertical) list_of_leds_length += 4;
      if (include_horizontal) list_of_leds_length += 2 * SHORT_LENGTH + 2 * LONG_LENGTH;
    
			for (int i = 0; i < NUM_LEDS; i++) {
			  list_of_leds[i] = NULL;
			}
			
			int list_index = 0;
		
			if (include_vertical) {
				list_of_leds[list_index] = south_east;
				list_index++;
			}
  
			if (include_horizontal) {
				for (int i = 0; i < LONG_LENGTH; i++) {
					int *small_list = (int*) malloc(2 * sizeof(int));
					small_list[0] = south[i];
					small_list[1] = -1;
					list_of_leds[list_index] = small_list;
					list_index++;
				}
			}
  
			if (include_vertical) {
				list_of_leds[list_index] = south_west;
				list_index++;
			}
  
			if (include_horizontal) {
				for (int i = 0; i < SHORT_LENGTH; i++) {
					int *small_list = (int*) malloc(2 * sizeof(int));
					small_list[0] = west[i];
					small_list[1] = -1;
					list_of_leds[list_index] = small_list;
					list_index++;
				}
			}
  
			if (include_vertical) {
				list_of_leds[list_index] = north_west;
				list_index++;
			}
  
			if (include_horizontal) {
				for (int i = 0; i < LONG_LENGTH; i++) {
					int *small_list = (int*) malloc(2 * sizeof(int));
					small_list[0] = north[i];
					small_list[1] = -1;
					list_of_leds[list_index] = small_list;
					list_index++;
				}
			}
  
			if (include_vertical) {
				list_of_leds[list_index] = north_east;
				list_index++;
			}
  
			if (include_horizontal) {
				for (int i = 0; i < SHORT_LENGTH; i++) {
					int *small_list = (int*) malloc(2 * sizeof(int));
					small_list[0] = east[i];
					small_list[1] = -1;
					list_of_leds[list_index] = small_list;
					list_index++;
				}
			}
  
		};

    void build_list_straight_vertical(bool include_vertical, bool include_horizontal) {
      list_of_leds_length = 0;
      if (include_vertical) list_of_leds_length += VERTICAL_LENGTH;
      if (include_horizontal) list_of_leds_length += 1;
      
      for (int i = 0; i < NUM_LEDS; i++) {
        list_of_leds[i] = NULL;
      }
      
      int list_index = 0;
  
      if (include_vertical) {
        for (int i = 0; i < VERTICAL_LENGTH; i++) {
          int *small_list = (int*) malloc(5 * sizeof(int));
          small_list[0] = south_east[i];
          small_list[1] = south_west[i];
          small_list[2] = north_west[i];
          small_list[3] = north_east[i];
          small_list[4] = -1;
          list_of_leds[list_index] = small_list;
          list_index++;
        }
      }

      if (include_horizontal) {
        int *small_list = (int*) malloc((2 * LONG_LENGTH + 2 * SHORT_LENGTH + 1) * sizeof(int));
        int led_index = 0;
        for (int i = 0; i < SHORT_LENGTH; i++) {
          small_list[led_index] = west[i];
          led_index++;
          small_list[led_index] = east[i];
          led_index++;
        }

        for (int i = 0; i < LONG_LENGTH; i++) {
          small_list[led_index] = south[i];
          led_index++;
          small_list[led_index] = north[i];
          led_index++;
        }

        small_list[led_index] = -1;
        list_of_leds[list_index] = small_list;
        list_index++;
      }
    }

      

		void print_circle_list_indexes() {
			std::string res = "";
			int main_it = 0;
			while (list_of_leds[main_it] != NULL) {
				int * inside_list = list_of_leds[main_it];
				int second_it = 0;
				while (inside_list[second_it] != -1) {
					second_it++;
				}
			main_it++;
			}
		};

    void build_list_single_element(bool include_vertical, bool include_horizontal) {
      list_of_leds_length = 1;
      
      int number_of_leds_in_element = 1;
      if (include_horizontal) number_of_leds_in_element += 2 * LONG_LENGTH + 2 * SHORT_LENGTH;
      if (include_vertical) number_of_leds_in_element += 4 * VERTICAL_LENGTH;
    
      for (int i = 0; i < NUM_LEDS; i++) {
        list_of_leds[i] = NULL;
      }

      list_of_leds[0] = (int*) malloc(number_of_leds_in_element * sizeof(int));
      int list_index = 0;
      
      if (include_vertical) {
        
        int edge_index = 0;
        while (south_east[edge_index] != -1) {
          list_of_leds[0][list_index] = south_east[edge_index];
          edge_index++;
          list_index++;
        }

        edge_index = 0;
        while (south_west[edge_index] != -1) {
          list_of_leds[0][list_index] = south_west[edge_index];
          edge_index++;
          list_index++;
        }

        edge_index = 0;
        while (north_west[edge_index] != -1) {
          list_of_leds[0][list_index] = north_west[edge_index];
          edge_index++;
          list_index++;
        }

        edge_index = 0;
        while (north_east[edge_index] != -1) {
          list_of_leds[0][list_index] = north_east[edge_index];
          edge_index++;
          list_index++;
        }
      }

      if (include_horizontal) {
        
        int edge_index = 0;
        while (south[edge_index] != -1) {
          list_of_leds[0][list_index] = south[edge_index];
          edge_index++;
          list_index++;
        }

        edge_index = 0;
        while (west[edge_index] != -1) {
          list_of_leds[0][list_index] = west[edge_index];
          edge_index++;
          list_index++;
        }

        edge_index = 0;
        while (north[edge_index] != -1) {
          list_of_leds[0][list_index] = north[edge_index];
          edge_index++;
          list_index++;
        }

        edge_index = 0;
        while (east[edge_index] != -1) {
          list_of_leds[0][list_index] = east[edge_index];
          edge_index++;
          list_index++;
        }
      }

      list_of_leds[0][list_index] = -1;

      
    }

		void set_hue_color_span_rainbow(float starting_hue, float ending_hue, float period, int compress, float time_elapsed) {
			float hue_diff = ending_hue - starting_hue;
			float total_degrees = hue_diff * compress;
			float hue_shift_per_second = 0;
			if (period != 0) {
				hue_shift_per_second = total_degrees / period;
			};
			float hue_diff_element = total_degrees / list_of_leds_length;
			if (fmod(abs(hue_diff), 360) != 0) {hue_diff_element *= 2; hue_shift_per_second *= 2;};
     
			uint8_t saturation = 255;
			uint8_t value = 255;
      
			for (int element_index = 0; element_index < list_of_leds_length; element_index++) {
        //Serial.println("inside2");
				int * inside_list = list_of_leds[element_index];
				int led_index = 0;
				while (inside_list[led_index] != -1) {
					float hue;
					if (fmod(abs(hue_diff), 360) == 0) hue = fmod((starting_hue + hue_diff_element * element_index + hue_shift_per_second * time_elapsed), 360);
					else {
						hue = fmod((hue_diff_element * element_index + hue_shift_per_second * time_elapsed), (2 * abs(hue_diff))) + starting_hue;
						if (hue_diff > 0 && hue > ending_hue) {
							float excess = hue - ending_hue;
							hue = ending_hue - excess;
						} else if (hue_diff < 0 && hue < ending_hue) {
              float gap = ending_hue - hue;
              hue = ending_hue + gap;
						}
					}
					uint8_t final_hue = round(255 * (hue / 360.0));
					leds[inside_list[led_index]] = CHSV(final_hue, saturation, value);
					led_index++;
				}
			}
		}

   void set_hue_color_span_cycle(float starting_hue, float ending_hue, float period, float time_elapsed) {
    float hue_diff = ending_hue - starting_hue;
    float hue_shift_per_second = 0;
    if (period != 0) {
      hue_shift_per_second = hue_diff / period;
    };
    if (fmod(abs(hue_diff), 360) != 0) hue_shift_per_second *= 2;
    uint8_t saturation = 255;
    uint8_t value = 255;
    float hue;
    if (fmod(abs(hue_diff), 360) == 0) hue = fmod((starting_hue + hue_shift_per_second * time_elapsed), 360);
    else {
      hue = fmod((hue_shift_per_second * time_elapsed), (2 * abs(hue_diff))) + starting_hue;
      if (hue_diff > 0 && hue > ending_hue) {
        float excess = hue - ending_hue;
        hue = ending_hue - excess;
      } else if (hue_diff < 0 && hue < ending_hue) {
        float gap = ending_hue - hue;
        hue = ending_hue + gap;
      }
    }
    int led_index = 0;
    uint8_t final_hue = round(255 * (hue / 360.0));
    while (list_of_leds[0][led_index] != -1) {
      leds[list_of_leds[0][led_index]] = CHSV(final_hue, saturation, value);
      led_index++;
    }
  }

  void audio_effect(float* bins, int total_bins, int bass_bins, int middle_bins, int high_bins) {

    int final_bins_num = bass_bins + middle_bins + high_bins;
    float normalized_bins[NUM_BINS];

    float div = 1.3;


    // !!! HUE VALUES GIVEN FROM 0-255, NOT 0 - 360!!!
    // define hue values for low, high and peak parts of the bar
    int low_hue = 170;
    int high_hue = 255;
    int peak_hue = 85;
    
    if (bass_bins == 2) {
      /*
       * THIS BLOCK IS CURRENTLY BEING USED TO TEST ALTERNATE COLORS FOR AUDIO EFFECT
       * ONLY AFFECTS LOWEST BASS BIN
      */
      // THESE 3 LINES DONT AFFECT COLOR
      normalized_bins[0] = sigmoid(bins[0]);
      led_count[0] = max(normalized_bins[0] * VERTICAL_LENGTH, led_count[0] / div);
      if (led_count[0] >= bin_peaks[0]) bin_peaks[0] = led_count[0]; else bin_peaks[0]--;


      // THIS BLOCK SETS THE MAIN PART OF THE BAR
      float hue_per_led = (high_hue - low_hue) / (VERTICAL_LENGTH / 3);  // HOW MUCH HUE DISTANCE NEEDS TO BE COVERED? PER LED, IT IS THAT DISTANCE DIVIDED BY A THIRD OF THE NUMBER OF LEDs, TO MAKE THE BAR REACH FINAL HUE BEFORE END OF BAR
      //Serial.print("HUE PER LED: ");
      //Serial.println(hue_per_led);
      //Serial.print("HUES: ");
      for (int i = 0; i < led_count[0]; i++) {
        int hue = low_hue + i * hue_per_led;
        if (hue > high_hue) hue = high_hue;
        //Serial.print(hue);
        //Serial.print(" ");
        leds[north_east[VERTICAL_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[north_west[VERTICAL_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      //Serial.println();

      // THIS BLOCK IS TO SET THE PEAK DOT
      if (bin_peaks[0] != 0) {
        leds[north_east[VERTICAL_LENGTH - bin_peaks[0]]] = CHSV(peak_hue, 255, 255);
        leds[north_west[VERTICAL_LENGTH - bin_peaks[0]]] = CHSV(peak_hue, 255, 255);
      }

      /*
       * BLOCK
       * END
       */

      
      
      normalized_bins[1] = sigmoid(bins[1]);

      led_count[1] = max(normalized_bins[1] * VERTICAL_LENGTH, led_count[1] / div);
      if (led_count[1] >= bin_peaks[1]) bin_peaks[1] = led_count[1]; else bin_peaks[1]--;
      for (int i = 0; i < led_count[1]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[south_east[VERTICAL_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[south_west[VERTICAL_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[1] != 0) {
        leds[south_east[VERTICAL_LENGTH - bin_peaks[1]]] = CHSV(170, 255, 255);
        leds[south_west[VERTICAL_LENGTH - bin_peaks[1]]] = CHSV(170, 255, 255);
      }
      
    } else if (bass_bins == 1) {
      normalized_bins[0] = sigmoid((bins[0] + bins[1]) / 2.0);

      led_count[0] = max(normalized_bins[0] * VERTICAL_LENGTH, led_count[0] / div);
      float hue_per_led = 85 / (VERTICAL_LENGTH / 3);
      if (led_count[0] >= bin_peaks[0]) bin_peaks[0] = led_count[0]; else bin_peaks[0]--;
      //Serial.println(led_count[0]);
      for (int i = 0; i < led_count[0]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[south_east[VERTICAL_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[south_west[VERTICAL_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[north_east[VERTICAL_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[north_west[VERTICAL_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[0] != 0) {
        leds[south_east[VERTICAL_LENGTH - bin_peaks[0]]] = CHSV(170, 255, 255);
        leds[south_west[VERTICAL_LENGTH - bin_peaks[0]]] = CHSV(170, 255, 255);
        leds[north_east[VERTICAL_LENGTH - bin_peaks[0]]] = CHSV(170, 255, 255);
        leds[north_west[VERTICAL_LENGTH - bin_peaks[0]]] = CHSV(170, 255, 255);
      }
    }

    if (middle_bins == 4) {
      int avail_leds = LONG_LENGTH / 2;
      float hue_per_led = 85 / (avail_leds / 3);
      normalized_bins[2] = sigmoid(bins[2]);

      led_count[2] = max(normalized_bins[2] * avail_leds, led_count[2] / div);
      if (led_count[2] >= bin_peaks[2]) bin_peaks[2] = led_count[2]; else bin_peaks[2]--;
      for (int i = 0; i < led_count[2]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[south[i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[2] != 0) {
        leds[south[bin_peaks[2]]] = CHSV(170, 255, 255);
      }
      
      normalized_bins[3] = sigmoid(bins[3]);

      led_count[3] = max(normalized_bins[3] * avail_leds, led_count[3] / div);
      if (led_count[3] >= bin_peaks[3]) bin_peaks[3] = led_count[3]; else bin_peaks[3]--;
      for (int i = 0; i < led_count[3]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[south[LONG_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[3] != 0) {
        leds[south[LONG_LENGTH - 1 - bin_peaks[3]]] = CHSV(170, 255, 255);
      }
      
      normalized_bins[4] = sigmoid(bins[4]);

      led_count[4] = max(normalized_bins[4] * avail_leds, led_count[4] / div);
      if (led_count[4] >= bin_peaks[4]) bin_peaks[4] = led_count[4]; else bin_peaks[4]--;
      for (int i = 0; i < led_count[4]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[north[i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[4] != 0) {
        leds[north[bin_peaks[4]]] = CHSV(170, 255, 255);
      }
      
      normalized_bins[5] = sigmoid(bins[5]);

      led_count[5] = max(normalized_bins[5] * avail_leds, led_count[5] / div);
      if (led_count[5] >= bin_peaks[5]) bin_peaks[5] = led_count[5]; else bin_peaks[5]--;
      for (int i = 0; i < led_count[5]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[north[LONG_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[5] != 0) {
        leds[north[LONG_LENGTH - 1 - bin_peaks[5]]] = CHSV(170, 255, 255);
      }
      
    } else if (middle_bins == 2) {
      normalized_bins[2] = sigmoid((bins[2] + bins[3]) / 2.0);
      normalized_bins[4] = sigmoid((bins[4] + bins[5]) / 2.0);


      int avail_leds = LONG_LENGTH / 2;
      float hue_per_led = 85 / (avail_leds / 3);

      led_count[2] = max(normalized_bins[2] * avail_leds, led_count[2] / div);
      if (led_count[2] >= bin_peaks[2]) bin_peaks[2] = led_count[2]; else bin_peaks[2]--;
      for (int i = 0; i < led_count[2]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[south[i]] = CHSV(hue, 255, 255);
        leds[south[LONG_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[2] != 0) {
        leds[south[bin_peaks[2]]] = CHSV(170, 255, 255);
        leds[south[LONG_LENGTH - 1 - bin_peaks[2]]] = CHSV(170, 255, 255);
      }
      
      led_count[4] = max(normalized_bins[4] * avail_leds, led_count[4] / div);
      if (led_count[4] >= bin_peaks[4]) bin_peaks[4] = led_count[4]; else bin_peaks[4]--;
      for (int i = 0; i < led_count[4]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[north[i]] = CHSV(hue, 255, 255);
        leds[north[LONG_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[4] != 0) {
        leds[north[bin_peaks[4]]] = CHSV(170, 255, 255);
        leds[north[LONG_LENGTH - 1 - bin_peaks[4]]] = CHSV(170, 255, 255);
      }
      
      
    } else if (middle_bins == 1) {
      normalized_bins[2] = sigmoid((bins[2] + bins[3] + bins[4] + bins[5]) / 4.0);


      int avail_leds = LONG_LENGTH / 2;
      float hue_per_led = 85 / (avail_leds / 3);

      led_count[2] = max(normalized_bins[2] * avail_leds, led_count[2] / div);
      if (led_count[2] >= bin_peaks[2]) bin_peaks[2] = led_count[2]; else bin_peaks[2]--;
      for (int i = 0; i < led_count[2]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[south[i]] = CHSV(hue, 255, 255);
        leds[south[LONG_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[north[i]] = CHSV(hue, 255, 255);
        leds[north[LONG_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[2] != 0) {
        leds[south[bin_peaks[2]]] = CHSV(170, 255, 255);
        leds[south[LONG_LENGTH - 1 - bin_peaks[2]]] = CHSV(170, 255, 255);
        leds[north[bin_peaks[2]]] = CHSV(170, 255, 255);
        leds[north[LONG_LENGTH - 1 - bin_peaks[2]]] = CHSV(170, 255, 255);
      }
    }

    if (high_bins == 4) {
      int avail_leds = SHORT_LENGTH / 2;
      float hue_per_led = 85 / (avail_leds / 3);
      
      normalized_bins[6] = sigmoid(bins[6]);

      led_count[6] = max(normalized_bins[6] * avail_leds, led_count[6] / div);
      if (led_count[6] >= bin_peaks[6]) bin_peaks[6] = led_count[6]; else bin_peaks[6]--;
      for (int i = 0; i < led_count[6]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[east[SHORT_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[6] != 0) {
        leds[east[SHORT_LENGTH - 1 - bin_peaks[6]]] = CHSV(170, 255, 255);
      }
      
      normalized_bins[7] = sigmoid(bins[7]);

      led_count[7] = max(normalized_bins[7] * avail_leds, led_count[7] / div);
      if (led_count[7] >= bin_peaks[7]) bin_peaks[7] = led_count[7]; else bin_peaks[7]--;
      for (int i = 0; i < led_count[7]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[east[i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[7] != 0) {
        leds[east[bin_peaks[7]]] = CHSV(170, 255, 255);
      }

      normalized_bins[8] = sigmoid(bins[8]);

      led_count[8] = max(normalized_bins[8] * avail_leds, led_count[8] / div);
      if (led_count[8] >= bin_peaks[8]) bin_peaks[8] = led_count[8]; else bin_peaks[8]--;
      for (int i = 0; i < led_count[8]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[west[i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[8] != 0) {
        leds[west[bin_peaks[8]]] = CHSV(170, 255, 255);
      }
      
      normalized_bins[9] = sigmoid(bins[9]);

      led_count[9] = max(normalized_bins[9] * avail_leds, led_count[9] / div);
      if (led_count[9] >= bin_peaks[9]) bin_peaks[9] = led_count[9]; else bin_peaks[9]--;
      for (int i = 0; i < led_count[9]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[west[SHORT_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[9] != 0) {
        leds[west[SHORT_LENGTH - 1 - bin_peaks[9]]] = CHSV(170, 255, 255);
      }
      
    } else if (high_bins == 2) {
      int avail_leds = SHORT_LENGTH / 2;
      float hue_per_led = 85 / (avail_leds / 3);
      normalized_bins[6] = sigmoid((bins[6] + bins[7]) / 2.0);

      led_count[6] = max(normalized_bins[6] * avail_leds, led_count[6] / div);
      if (led_count[6] >= bin_peaks[6]) bin_peaks[6] = led_count[6]; else bin_peaks[6]--;
      for (int i = 0; i < led_count[6]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[east[SHORT_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[east[i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[6] != 0) {
        leds[east[SHORT_LENGTH - 1 - bin_peaks[6]]] = CHSV(170, 255, 255);
        leds[east[bin_peaks[6]]] = CHSV(170, 255, 255);
      }
      
      normalized_bins[8] = sigmoid((bins[8] + bins[9]) / 2.0);

      led_count[8] = max(normalized_bins[8] * avail_leds, led_count[8] / div);
      if (led_count[8] >= bin_peaks[8]) bin_peaks[8] = led_count[8]; else bin_peaks[8]--;
      for (int i = 0; i < led_count[8]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[west[SHORT_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[west[i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[8] != 0) {
        leds[west[SHORT_LENGTH - 1 - bin_peaks[8]]] = CHSV(170, 255, 255);
        leds[west[bin_peaks[8]]] = CHSV(170, 255, 255);
      }
      
    } else if (high_bins == 1) {
      int avail_leds = SHORT_LENGTH / 2;
      float hue_per_led = 85 / (avail_leds / 3);
      normalized_bins[6] = sigmoid((bins[6] + bins[7] + bins[7] + bins[8]) / 4.0);

      led_count[6] = max(normalized_bins[6] * avail_leds, led_count[6] / div);
      if (led_count[6] >= bin_peaks[6]) bin_peaks[6] = led_count[6]; else bin_peaks[6]--;
      for (int i = 0; i < led_count[6]; i++) {
        int hue = constrain(i * hue_per_led, 0, 85);
        leds[east[SHORT_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[east[i]] = CHSV(hue, 255, 255);
        leds[west[SHORT_LENGTH - 1 - i]] = CHSV(hue, 255, 255);
        leds[west[i]] = CHSV(hue, 255, 255);
      }
      if (bin_peaks[6] != 0) {
        leds[east[SHORT_LENGTH - 1 - bin_peaks[6]]] = CHSV(170, 255, 255);
        leds[east[bin_peaks[6]]] = CHSV(170, 255, 255);
        leds[west[SHORT_LENGTH - 1 - bin_peaks[6]]] = CHSV(170, 255, 255);
        leds[west[bin_peaks[6]]] = CHSV(170, 255, 255);
      }
    }

    
    
    
  }

  float sigmoid(float x) {
    //return (1.0 / (1 + exp(-40*(x-0.15))));
    return sqrt((2.0 / (1 + exp(-70 * x*x))) - 1.0);
  };
};
