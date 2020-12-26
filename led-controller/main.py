#! /usr/bin/python2.7

import json
import time
from config import build_living_room
from datetime import datetime
import os
from compass import DataFlow
from circular_list import CircularList
import pygame
from os import environ
from compass import Direction
import sys
import math

living_room = build_living_room()
leds_display_coords = []

if living_room.demo:
    environ['SDL_VIDEO_WINDOW_POS'] = "%d,%d" % (30, 30)
    pygame.init()
    screen = pygame.display.set_mode((living_room.length * 5+10, living_room.short * 5+10))
    leds_display_coords = [(0, 0)] * living_room.num_leds
    alpha = math.pi * 1/3

    for edge in living_room.all_edges_in_order:
        if edge.direction == Direction.N:
            for i in range(edge.length):
                leds_display_coords[edge.leds[i]] = (3 + (1+i)*5, 3)
        elif edge.direction == Direction.S:
            for i in range(edge.length):
                leds_display_coords[edge.leds[i]] = (screen.get_width() - 3 - (1+i)*5, screen.get_height() - 3)
        elif edge.direction == Direction.E:
            for i in range(edge.length):
                leds_display_coords[edge.leds[i]] = (screen.get_width() - 3, 3 + (1+i)*5)
        elif edge.direction == Direction.W:
            for i in range(edge.length):
                leds_display_coords[edge.leds[i]] = (3, screen.get_height() - 3 - (1+i) * 5)
        elif edge.direction == Direction.NE:
            for i in range(edge.length):
                leds_display_coords[edge.leds[i]] = (math.floor(screen.get_width() + (2+edge.length-i)*
                                                                5*math.cos(-math.pi/2 - alpha))
                                                     , math.floor(-(2+edge.length-i)*5*math.sin(-math.pi/2 - alpha)+5))
        elif edge.direction == Direction.NW:
            for i in range(edge.length):
                leds_display_coords[edge.leds[i]] = (math.floor((2+edge.length-i)*5*math.cos(-math.pi/2 + alpha)),
                                                     math.floor(-(2+edge.length-i)*5*math.sin(-math.pi/2 + alpha)+5))
        elif edge.direction == Direction.SW:
            for i in range(edge.length):
                leds_display_coords[edge.leds[i]] = (math.floor((2+edge.length-i) * 5 * math.cos(math.pi / 2 - alpha)),
                                                     math.floor(screen.get_height()-(2+edge.length-i) * 5 *
                                                                math.sin(math.pi / 2 - alpha)-5))
        elif edge.direction == Direction.SE:
            print(edge.leds[0])
            for i in range(edge.length):
                leds_display_coords[edge.leds[i]] = (math.floor(screen.get_width()+(2+edge.length-i)*
                                                                5*math.cos(math.pi/2 + alpha)),
                                                     math.floor(screen.get_height()-(2+edge.length-i)*
                                                                5*math.sin(math.pi/2 + alpha)-5))





    pygame.font.init()
    screen.fill(0)

living_room_horizontal_circle = living_room.build_list_horizontal_circle()
living_room_vertical_straight = living_room.build_list_vertical_straight()
living_room_horizontal_circle_no_vertical = living_room.build_list_horizontal_circle(include_vertical=False)
living_room_vertical_straight_no_horizontal = living_room.build_list_vertical_straight(include_horizontal=False)

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

        if fx_config["effect"] == "hue_color_span":
            # start by wiping all previous colors
            for led_num in range(living_room.num_leds):
                living_room.set_led_rgb(led_num, (0, 0, 0))

            time_elapsed = (datetime.now() - timestamp_start).total_seconds()
            compress = fx_config["effect_params"]["hue_color_span"]["compress"]
            #led_list = [i for i in range(living_room.num_leds)]
            led_list = CircularList()
            if fx_config["effect_params"]["hue_color_span"]["direction"] == "horizontal":
                for edge in living_room.all_edges_in_order:
                    if (edge.data_flow == DataFlow.CEIL_TO_FLOOR or edge.data_flow == DataFlow.FLOOR_TO_CEIL) and fx_config["effect_params"]["hue_color_span"]["include_vertical"]:
                        led_list.append(edge.leds)
                    elif edge.data_flow <= 7 and fx_config["effect_params"]["hue_color_span"]["include_horizontal"]:
                        for led_num in edge.leds:
                            led_list.append([led_num])

            elif fx_config["effect_params"]["hue_color_span"]["direction"] == "vertical":
                if fx_config["effect_params"]["hue_color_span"]["include_vertical"]:
                    for i in range(0, living_room.vertical_edges_up[0].length):
                        led_list.append([living_room.vertical_edges_up[0].leds[i],
                                         living_room.vertical_edges_up[1].leds[i],
                                         living_room.vertical_edges_up[2].leds[i],
                                         living_room.vertical_edges_up[3].leds[i]])
                if fx_config["effect_params"]["hue_color_span"]["include_horizontal"]:
                    ceiling_leds = []
                    for edge in living_room.ceiling_edges_clockwise:
                        for led_num in edge.leds:
                            ceiling_leds.append(led_num)
                    led_list.append(ceiling_leds)


            living_room.set_hue_span_color_cycle(led_list,
                                                 start_index=fx_config["effect_params"]["hue_color_span"]["start_index"],
                                                 compress=fx_config["effect_params"]["hue_color_span"]["compress"],
                                                 speed=fx_config["effect_params"]["hue_color_span"]["speed"],
                                                 starting_hue=fx_config["effect_params"]["hue_color_span"]["starting_hue"],
                                                 ending_hue=fx_config["effect_params"]["hue_color_span"]["ending_hue"],
                                                 time_elapsed=time_elapsed)

        elif fx_config["effect"] == "christmas_animation":
            last_ceiling_stamp, last_vertical_stamp = living_room.christmas_animation(last_ceiling_stamp,
                                                                                      last_vertical_stamp)

        elif fx_config["effect"] == "static":
            # start by wiping all previous colors
            for led_num in range(living_room.num_leds):
                living_room.set_led_rgb(led_num, (0, 0, 0))
            red = fx_config["effect_params"]["static"]["red"]
            green = fx_config["effect_params"]["static"]["green"]
            blue = fx_config["effect_params"]["static"]["blue"]
            led_list = []

            if fx_config["effect_params"]["static"]["include_horizontal"]:
                for edge in living_room.ceiling_edges_clockwise:
                    for led_num in edge.leds:
                        led_list.append(led_num)
            if fx_config["effect_params"]["static"]["include_vertical"]:
                for edge in living_room.vertical_edges_up:
                    for led_num in edge.leds:
                        led_list.append(led_num)

            for led_num in led_list:
                living_room.set_led_rgb(led_num, (red, green, blue))

        elif fx_config["effect"] == "none":
            for led_num in range(living_room.num_leds):
                living_room.set_led_rgb(led_num, (0, 0, 0))

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

    living_room.apply_brightness()
    living_room.update()

    if living_room.demo:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
        for i in range(living_room.num_leds):
            pygame.draw.circle(screen, living_room.leds[i], leds_display_coords[i], 2)
        pygame.display.update()

    # speed analysis
    if iter_counter == 99:
        fx_config = load_fx_config()
        living_room.brightness = fx_config["brightness"]
        iter_counter = -1
        iter_duration_stamp = datetime.now()

    iter_counter += 1
