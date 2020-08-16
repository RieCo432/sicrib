import time
from config import build_living_room
from datetime import datetime

living_room = build_living_room()

#led_list_in_order = living_room.build_list_horizontal_circle()
led_list_in_order = living_room.build_list_vertical_straight()

# setup hue span color cycle
timestamp_start = datetime.now()

# setup christmas animation
last_ceiling_stamp = last_vertical_stamp = datetime.now()
iter_duration_stamp = datetime.now()
iter_counter = 0
while True:

    # time_elapsed = (datetime.now() - timestamp_start).total_seconds()
    # living_room.set_hue_span_color_cycle(led_list_in_order, compress=4, speed=23, time_elapsed=time_elapsed)

    last_ceiling_stamp, last_vertical_stamp = living_room.christmas_animation(last_ceiling_stamp, last_vertical_stamp)


    living_room.set_led_rgb(464, (0,0,0))
    living_room.update()

    # speed analysis
    if iter_counter == 99:
        print(int(100 / (datetime.now() - iter_duration_stamp).total_seconds()), "updates per second")
        iter_counter = -1
        iter_duration_stamp = datetime.now()

    iter_counter += 1
