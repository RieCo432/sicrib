import json

doorway_states = {"kitchen": {"direction": 0,
                              "progress": 0},
                  "hallway": {"direction": 1,
                              "progress": 0}}
                              
json.dump(doorway_states, open("doorway_states.json", "w"))
