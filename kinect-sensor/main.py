from freenect2 import Device, FrameType
import cv2 as cv
import numpy as np
import requests
from copy import deepcopy

device = Device()
frame_height = 424
frame_width = 512

hallway_door_person_location = {'x1': 220,
                                'y1': 90,
                                'x2': 290,
                                'y2': 260}

doorway_states = {"kitchen": {"direction": 0, "progress": 0},
                              "hallway": {"direction": 0, "progress": 0}}
hallway_door_frame_dist = 3000

device.start()

for frame_type, frame in device:
    if frame_type == FrameType.Depth:
        frame_mm = frame.to_array()

        hallway_door_person = frame_mm[hallway_door_person_location['y1']:hallway_door_person_location['y2'],
                                       hallway_door_person_location['x1']:hallway_door_person_location['x2']]
        hallway_door_person_flat = hallway_door_person.flatten()
        hallway_door_person_relevant = [x for x in hallway_door_person_flat if hallway_door_frame_dist - 1000 < x < hallway_door_frame_dist + 1000]

        print(hallway_door_person_relevant)

        prev_state = deepcopy(doorway_states)

        if len(hallway_door_person_relevant) > 100:
            hallway_door_person_avg = np.average(hallway_door_person_relevant)
            dist_person_to_hallway_door = hallway_door_person_avg - hallway_door_frame_dist
            if dist_person_to_hallway_door < 0:
                direction = 1
            else:
                direction = 0

            progress = int(abs(dist_person_to_hallway_door / 1000)*100) / 100.0

            doorway_states = {"kitchen": {"direction": 0, "progress": 0}, "hallway": {"direction": direction, "progress": progress}}

        else:
            doorway_states = {"kitchen": {"direction": 0, "progress": 0},
                              "hallway": {"direction": 0, "progress": 0}}

        if prev_state != doorway_states:
            response = requests.post('http://192.168.178.11/setdoorwaystate', json=doorway_states)

            print("Status code: ", response.status_code)
            #print("Printing Entire Post Request")
            #print(response.json())

        frame_disp = cv.cvtColor((frame_mm / 8000.0 * 255).astype(np.uint8), cv.COLOR_GRAY2BGR)
        cv.rectangle(frame_disp, (hallway_door_person_location['x1'], hallway_door_person_location['y1']),
                     (hallway_door_person_location['x2'], hallway_door_person_location['y2']), (0, 0, 255), 1)

        cv.imshow("frame", frame_disp)
        if cv.waitKey(1) & 0xFF == ord('q'):
            break

device.close()

cv.destroyAllWindows()