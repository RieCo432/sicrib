import json
import numpy as np
from time import sleep

while True:
    for direction in range(2):
        for i in np.arange(0, 1.0, 0.01):
            doorway_states = {"kitchen": {"direction": direction,
                                          "progress": i},
                              "hallway": {"direction": direction,
                                          "progress": i}}
            json.dump(doorway_states, open("doorway_states.json", "w"))
            sleep(0.01)

    doorway_states = {"kitchen": {"direction": 0,
                                  "progress": 0.0},
                      "hallway": {"direction": 0,
                                  "progress": 0.0}}
    json.dump(doorway_states, open("doorway_states.json", "w"))
    sleep(2)
