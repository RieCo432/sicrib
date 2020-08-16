import pickle

configs = {
    "enabled": False,
    "effect": "hue_color_span",
    "effect_params": {"start_index": 0,
                      "starting_hue": 120.0,
                      "ending_hue": 240.0,
                      "speed": 10,
                      "compress": 2},
    "addons": []
}

pickle.dump(configs, open("fx_config.p", "wb"))
