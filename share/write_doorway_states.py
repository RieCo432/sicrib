import json

doorway_states = {"kitchen": {"direction": 0,
                              "progress": 0.5},
                  "hallway": {"direction": 1,
                              "progress": 0.75}}
                              
json.dump(doorway_states, open("doorway_states.json", "w"))
