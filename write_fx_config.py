import pickle

configs = {
    "enabled": True,
    "effect": "hue_color_span",
    "effect_params": {"start_index": 0,
                      "starting_hue": 0.0,
                      "ending_hue": 360.0,
                      "speed": 60,
                      "compress": 1},
    "addons": []
}

pickle.dump(configs, open("fx_config.p", "wb"))