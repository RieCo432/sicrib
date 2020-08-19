import json

configs = {
    "enabled": True,
    "brightness": 1.0,
    "effect": "hue_color_span",
    "effect_params": {"start_index": 0,
                      "starting_hue": 120.0,
                      "ending_hue": 240.0,
                      "speed": 10,
                      "compress": 2,
                      "direction": "vertical",
                      "include_vertical": True,
                      "include_horizontal": True},
                      
    "addons": [{"name": "doorway_tracker",
                "enabled": True,
                "style": "middle_out",
                "blank_color": (255,255,255),
                "enter_color": (0, 255, 0),
                "exit_color": (255, 0, 0)}]
}

json.dump(configs, open("fx_config.json", "w"))
