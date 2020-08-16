import time
from config import build_living_room
from datetime import datetime

living_room = build_living_room()
time.sleep(2)

led_list_in_order = living_room.build_list_horizontal_circle()
#led_list_in_order = living_room.build_list_vertical_straight()

timestamp_start = datetime.now()
while True:
    time_elapsed = (datetime.now() - timestamp_start).total_seconds()
    living_room.set_hue_span_color_cycle(led_list_in_order, compress=4, speed=23, time_elapsed=time_elapsed)
    living_room.set_led_rgb(464, (0,0,0))
    #living_room.set_led_rgb(121, (255, 255, 255))
    living_room.update()
