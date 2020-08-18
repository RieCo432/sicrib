import math
from datetime import datetime
import time
import color_helper
from circular_list import CircularList
import six
from random import randint


class Room:

    def __init__(self, num_leds, s0, s45, s90, s135, s180, s225, s270, s315, init_philips_hue=False,
                 philips_hue_ip="0.0.0.0", light_names=None):

        # if no light names are specified, replace with empty list
        if light_names is None:
            light_names = []

        # get total number of leds by adding together all edge lengths
        self.num_leds = sum([s0.length, s45.length, s90.length, s135.length, s180.length, s225.length, s270.length,
                             s315.length])

        self.leds_hsv_colors = [(0, 0, 0)] * self.num_leds

        self.brightness = 1.0

        self.doorway_led_numbers = {}

        # try importing the adafruit library and initialize strip. If it fails, demo mode will be used and the strip
        # is just a list of color tuples
        try:
            if six.PY3:
                import adafruit_ws2801 as af
                import board
                self.leds = af.WS2801(board.SCK, board.MOSI, self.num_leds, auto_write=False)
            elif six.PY2:
                import RPi.GPIO as GPIO
                import Adafruit_WS2801 as af
                import Adafruit_GPIO.SPI as SPI
                SPI_PORT = 0
                SPI_DEVICE = 0

                self.leds = af.WS2801Pixels(self.num_leds, spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE), gpio=GPIO)
            self.demo = False
        except ImportError:
            print("running in demo mode")
            time.sleep(1)
            self.demo = True
            self.leds = [(0, 0, 0)] * self.num_leds

        # set up philips hue, if fails, features won't be used
        self.phue_setup_done = False
        if init_philips_hue:
            try:
                import phue  # import the python hue library
                try:
                    self.phuebridge = phue.Bridge(philips_hue_ip)  # setup bridge
                    self.phuebridge.connect()  # connect to bridge
                    self.phue_light_names = []  # store all found lights
                    all_lights = self.phuebridge.get_light_objects()  # retrieve all light objects from bridge
                    # cycle through all lights, check if light name in list supplied to init function, then remove from
                    # user supplied list and append to list from above
                    for light in all_lights:
                        if light.name in light_names:
                            light_names.remove(light.name)
                            self.phue_light_names.append(light.name)
                    # if all lights were found, phue_setup_done set to true
                    if len(light_names) == 0:
                        self.phue_setup_done = True
                except phue.PhueRegistrationException:
                    print("Registration Error, link button not pressed in the past 30 seconds")
                    pass
                except phue.PhueRequestTimeout:
                    print("Connection error")
                    pass
            except ImportError:
                print("Error importing phue")
                pass

        # initialize list containing all color values
        self.colors = []
        for i in range(self.num_leds):
            self.colors.append((0, 0, 0))

        # associate supplied edges with correct attributes
        self.north = s0
        self.north_east = s45
        self.east = s90
        self.south_east = s135
        self.south = s180
        self.south_west = s225
        self.west = s270
        self.north_west = s315

        # initialize empty lists for various sets
        self.all_edges_in_order = None
        self.ceiling_edges_clockwise = None
        self.vertical_edges_up = None

    def set_sequences(self, a1, a2, a3, a4, a5, a6, a7, a8, c1, c2, c3, c4, v1, v2, v3, v4):
        # create circular lists for each set with corresponding edges
        self.all_edges_in_order = CircularList((a1, a2, a3, a4, a5, a6, a7, a8))
        self.ceiling_edges_clockwise = CircularList((c1, c2, c3, c4))
        self.vertical_edges_up = CircularList((v1, v2, v3, v4))

    def allocate_leds(self):
        # count up to number of LEDs and assign the number to the correct edges
        # p.ex. number 0 is supplied to first edge in the list, it will count from 0 to whatever its length is, then
        # return that number to be used as first for the next edge
        first = 0
        for edge in self.all_edges_in_order:
            first = edge.allocate_leds(first)

    def register_doorway(self, name, start_led, end_led):
        self.doorway_led_numbers[name] = [i for i in range(start_led, end_led + 1)]

    def display_doorway_progress_bar_left_to_right(self, name, color, progress):
        leds_length = len(self.doorway_led_numbers[name])
        leds_to_turn_on = math.ceil(progress * leds_length)
        base_led = self.doorway_led_numbers[name][0]
        for led_num in range(base_led, base_led + leds_to_turn_on):
            self.set_led_rgb(led_num, color)

    def display_doorway_progress_bar_middle_out(self, name, color, progress):
        leds_length = len(self.doorway_led_numbers[name])
        leds_to_turn_on = math.ceil(progress * leds_length)
        base_led = self.doorway_led_numbers[name][leds_length // 2]
        for led_num in range(base_led - leds_to_turn_on // 2, base_led + leds_to_turn_on // 2 + 1):
            self.set_led_rgb(led_num, color)

    # build a list of lists of LEDs, enabling horizontal circular effect with or without vertical elements
    def build_list_horizontal_circle(self, include_vertical=True):
        list_of_leds = CircularList()

        if include_vertical:
            # iterate through all edges in order and add LED numbers of ceiling strips to list, add list of LEDs in
            # vertical edges as list so they function as a single LED
            for edge in self.all_edges_in_order:
                if edge in self.ceiling_edges_clockwise:
                    for led in edge.leds:
                        list_of_leds.append([led])
                else:
                    list_of_leds.append(edge.leds)
        else:
            # iterate through edges and add the led numbers to the circular list
            for edge in self.ceiling_edges_clockwise:
                for led in edge.leds:
                    list_of_leds.append([led])

        return list_of_leds

    # build a list of lists of LEDs, enabling vertical upwards effect with or without horizontal elements
    def build_list_vertical_straight(self, include_horizontal=True):
        list_of_leds = CircularList()

        for i in range(0, self.vertical_edges_up[0].length):
            list_of_leds.append([self.vertical_edges_up[0].leds[i], self.vertical_edges_up[1].leds[i],
                                self.vertical_edges_up[2].leds[i], self.vertical_edges_up[3].leds[i]])

        if include_horizontal:
            all_horizontal = []
            for edge in self.ceiling_edges_clockwise:
                for n in edge.leds:
                    all_horizontal.append(n)

            list_of_leds.append(all_horizontal)

        return list_of_leds

    def update(self):
        if not self.demo:
            self.leds.show()
        else:
            print(self.leds)

    def set_led_rgb(self, led_num, color):
        self.leds_hsv_colors[led_num] = color_helper.rgb_to_hsv(color)
        if six.PY3 or self.demo:
            self.leds[led_num] = color
        elif six.PY2:
            self.leds.set_pixel_rgb(led_num, color[0], color[1], color[2])

    def set_led_hsv(self, led_num, color):
        self.leds_hsv_colors[led_num] = color
        color_rgb = color_helper.hsv_to_rgb(color[0], color[1], color[2])
        if six.PY3 or self.demo:
            self.leds[led_num] = color_rgb
        elif six.PY2:
            self.leds.set_pixel_rgb(led_num, color_rgb[0], color_rgb[1], color_rgb[2])

    def get_led_rgb(self, led_num):

        if six.PY3 or self.demo:
            return self.leds[led_num]
        elif six.PY2:
            return self.leds.get_pixel_rgb(led_num)

    def apply_brightness(self):
        for led_num in range(self.num_leds):
            color = (self.leds_hsv_colors[led_num][0], self.leds_hsv_colors[led_num][1], self.leds_hsv_colors[led_num][2] * self.brightness)
            self.set_led_hsv(led_num, color)



    # # turn off hue lights
    # def hue_off(self):
    #     if self.phue_setup_done:
    #         self.phuebridge.set_light(self.phue_light_names, "on", False)
    #
    # # turn on hue lights
    # def hue_on(self):
    #     if self.phue_setup_done:
    #         self.phuebridge.set_light(self.phue_light_names, "on", True)

    # start is the index where the starting hue is applied
    # speed is how many seconds each color should take for one rotation
    # starting hue determines which color is used at the main point, hue is in degrees (0 is red, 120 is green,
    # 240 is green)
    def set_hue_span_color_cycle(self, list_of_leds, start_index=0, starting_hue=0.0, ending_hue=360.0, speed=60, compress=1, time_elapsed=0):

        total_elements = len(list_of_leds)
        hue_diff = ending_hue - starting_hue
        total_degrees = (ending_hue - starting_hue) * compress
        hue_shift_per_second = total_degrees / speed
        hue_diff_element = total_degrees / total_elements
        if hue_diff != 360.0:
            hue_diff_element *= 2
            hue_center = (ending_hue - starting_hue) / 2

        # find index of starting led in list and shift backwards so starting LED is at the beginning
        list_of_leds.shiftBackwardN(start_index)

        saturation = 1.0
        value = self.brightness

        for element_index in range(len(list_of_leds)):
            for led_num in list_of_leds[element_index]:
                if hue_diff == 360.0:
                    hue = (starting_hue + hue_diff_element * element_index + time_elapsed * hue_shift_per_second) % 360
                else:
                    hue = (hue_diff_element * element_index + time_elapsed * hue_shift_per_second) % (2 * hue_diff) + starting_hue
                    if hue > ending_hue:
                        excess = hue - ending_hue
                        hue = ending_hue - excess

                self.set_led_hsv(led_num, (hue, saturation, value))

    def christmas_animation(self, last_ceiling_stamp, last_vertical_stamp):

        ceiling_led_list = CircularList()

        for edge in self.ceiling_edges_clockwise:
            for led_number in edge.leds:
                ceiling_led_list.append(led_number)

        if (datetime.now() - last_ceiling_stamp).total_seconds() >= 1:
            for i in ceiling_led_list:
                color = (0, 0, 0)
                color_pick = randint(1, 10)
                if color_pick == 0:
                    color = (0, 0, 255)
                elif 1 <= color_pick <= 6:
                    color = (255, 0, 0)
                elif 7 <= color_pick <= 10:
                    color = (0, 255, 0)
                self.set_led_rgb(i, color)

            ceiling_led_list.shiftForward()
            last_ceiling_stamp = datetime.now()

        if (datetime.now() - last_vertical_stamp).total_seconds() >= 0.05:
            for edge in self.vertical_edges_up:
                for i in range(edge.length):
                    offset = 2 * i
                    self.set_led_rgb(edge.leds[i], (255, max(0, min(255, offset + randint(-15, 15))), 0))
            last_vertical_stamp = datetime.now()

        self.apply_brightness()

        return last_ceiling_stamp, last_vertical_stamp





