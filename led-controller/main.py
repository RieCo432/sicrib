#! /usr/bin/python2.7

import json
import time
from config import build_living_room
from datetime import datetime
import os

living_room = build_living_room()

living_room_horizontal_circle = living_room.build_list_horizontal_circle()
living_room_vertical_straight = living_room.build_list_vertical_straight()

# setup hue span color cycle
timestamp_start = datetime.now()
# setup christmas animation
last_ceiling_stamp = last_vertical_stamp = datetime.now()
iter_duration_stamp = datetime.now()

iter_counter = 0
living_room.brightness = 1.0

fx_config_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "share", "fx_config.json")
doorway_states_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "share",
                                   "doorway_states.json")
def load_fx_config():
    while True:
        try:
            fx_config = json.load(open(fx_config_path, "r"))
            return fx_config
        except ValueError:
            pass

def load_doorway_states():
    while True:
        try:
            doorway_states = json.load(open(doorway_states_path, "r"))
            return doorway_states
        except ValueError:
            pass

fx_config = load_fx_config()

while True:

    if fx_config["enabled"]:

        if fx_config["effect"] == "hue_color_span_horizontal":
            time_elapsed = (datetime.now() - timestamp_start).total_seconds()
            compress = fx_config["effect_params"]["compress"]
            living_room.set_hue_span_color_cycle(living_room_horizontal_circle,
                                                 start_index=fx_config["effect_params"]["start_index"],
                                                 compress=fx_config["effect_params"]["compress"],
                                                 speed=fx_config["effect_params"]["speed"],
                                                 starting_hue=fx_config["effect_params"]["starting_hue"],
                                                 ending_hue=fx_config["effect_params"]["ending_hue"],
                                                 time_elapsed=time_elapsed)

        elif fx_config["effect"] == "hue_color_span_vertical":
            time_elapsed = (datetime.now() - timestamp_start).total_seconds()
            compress = fx_config["effect_params"]["compress"]
            living_room.set_hue_span_color_cycle(living_room_vertical_straight,
                                                 start_index=fx_config["effect_params"]["start_index"],
                                                 compress=fx_config["effect_params"]["compress"],
                                                 speed=fx_config["effect_params"]["speed"],
                                                 starting_hue=fx_config["effect_params"]["starting_hue"],
                                                 ending_hue=fx_config["effect_params"]["ending_hue"],
                                                 time_elapsed=time_elapsed)

        elif fx_config["effect"] == "christmas_animation":
            last_ceiling_stamp, last_vertical_stamp = living_room.christmas_animation(last_ceiling_stamp,
                                                                                      last_vertical_stamp)

        for addon in fx_config["addons"]:
            if addon["name"] == "doorway_tracker" and addon["enabled"]:
                doorway_states = load_doorway_states()

                for key in doorway_states.keys():
                    if doorway_states[key]["progress"] >= 0.01:
                        living_room.display_doorway_progress_bar_left_to_right(key, addon["blank_color"], 1.0)
                        color = addon["blank_color"]
                        if doorway_states[key]["direction"] == 0:
                            color = addon["exit_color"]
                        elif doorway_states[key]["direction"] == 1:
                            color = addon["enter_color"]
                        if addon["style"] == "middle_out":
                            living_room.display_doorway_progress_bar_middle_out(key, color, doorway_states[key]["progress"])
                        elif addon["style"] == "left_to_right":
                            living_room.display_doorway_progress_bar_left_to_right(key, color, doorway_states[key]["progress"])



        living_room.set_led_rgb(464, (0,0,0))

    else:
        for led_num in range(living_room.num_leds):
            living_room.set_led_rgb(led_num, (0, 0, 0))

    living_room.update()

    # speed analysis
    if iter_counter == 99:
        #print(int(100 / (datetime.now() - iter_duration_stamp).total_seconds()), "updates per second")
        fx_config = load_fx_config()
        iter_counter = -1
        iter_duration_stamp = datetime.now()

    iter_counter += 1
