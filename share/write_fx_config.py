import json

configs = {
    "enabled": True,
    "effect": "hue_color_span_horizontal",
    "effect_params": {"start_index": 0,
                      "starting_hue": 120.0,
                      "ending_hue": 240.0,
                      "speed": 10,
                      "compress": 2},
    "addons": []
}

json.dump(configs, open("fx_config.json", "w"))
