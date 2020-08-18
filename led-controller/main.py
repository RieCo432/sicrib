#! /usr/bin/python2.7

import json
import time
from config import build_living_room
from datetime import datetime
import os

living_room = build_living_room()

led_list_in_order = living_room.build_list_horizontal_circle()
#led_list_in_order = living_room.build_list_vertical_straight()

# setup hue span color cycle
timestamp_start = datetime.now()
# setup christmas animation
last_ceiling_stamp = last_vertical_stamp = datetime.now()
iter_duration_stamp = datetime.now()

iter_counter = 0
living_room.brightness = 1.0

fx_config_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "share", "fx_config.json")

fx_config = json.load(open(fx_config_path, "r"))

while True:

    if fx_config["enabled"]:

        if fx_config["effect"] == "hue_color_span":
            time_elapsed = (datetime.now() - timestamp_start).total_seconds()
            compress = fx_config["effect_params"]["compress"]
            living_room.set_hue_span_color_cycle(led_list_in_order,
                                                 start_index=fx_config["effect_params"]["start_index"],
                                                 compress=fx_config["effect_params"]["compress"],
                                                 speed=fx_config["effect_params"]["speed"],
                                                 starting_hue=fx_config["effect_params"]["starting_hue"],
                                                 ending_hue=fx_config["effect_params"]["ending_hue"],
                                                 time_elapsed=time_elapsed)

        elif fx_config["effect"] == "christmas_animation":
            last_ceiling_stamp, last_vertical_stamp = living_room.christmas_animation(last_ceiling_stamp, last_vertical_stamp)


        for i in range(98, 131):
            living_room.set_led_rgb(i, (255, 255, 255))

        for i in range(315, 349):
            living_room.set_led_rgb(i, (255, 255, 255))


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
