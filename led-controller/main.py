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

fx_config = json.load(open(fx_config_path, "r"))

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

        living_room.display_doorway_progress_bar_left_to_right("kitchen", (255, 255, 255), 1.0)
        living_room.display_doorway_progress_bar_left_to_right("hallway", (255, 255, 255), 1.0)

        if "doorway_tracker" in fx_config["addons"]:
            doorway_states = json.load(open(doorway_states_path, "r"))

            for key in doorway_states.keys():
                color = (255, 255, 255)
                if doorway_states[key]["direction"] == 0:
                    color = (255, 0, 0)
                elif doorway_states[key]["direction"] == 1:
                    color = (0, 255, 0)
                living_room.display_doorway_progress_bar_left_to_right(key, color, doorway_states[key]["progress"])

        living_room.set_led_rgb(464, (0,0,0))

    else:
        for led_num in range(living_room.num_leds):
            living_room.set_led_rgb(led_num, (0, 0, 0))

    living_room.update()

    # speed analysis
    if iter_counter == 99:
        # print(int(100 / (datetime.now() - iter_duration_stamp).total_seconds()), "updates per second")
        fx_config = json.load(open(fx_config_path, "r"))
        iter_counter = -1
        iter_duration_stamp = datetime.now()

    iter_counter += 1
