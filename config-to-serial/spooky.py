import phue
from random import randint
from time import sleep
import json
import os
from copy import copy

phuebridge = phue.Bridge("192.168.1.3")
phuebridge.connect()

fx_config_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "share", "fx_config.json")


def load_fx_config():
    while True:
        try:
            with open(fx_config_path, "r") as fin:
                return json.load(fin)
        except ValueError:
            pass


def write_fx_config(j):
    while True:
        try:
            with open(fx_config_path, "w") as fout:
                json.dump(j, fout)
        except Exception:
            pass


old_fx_config = None

turn_back_on = [True, True]

while True:
    x = randint(5, 10)
    sleep(x)
    fx_config = load_fx_config()

    turn_back_on[0] = phuebridge.get_light(1, 'on')
    turn_back_on[1] = copy(fx_config["enabled"])

    fx_config["enabled"] = False
    write_fx_config(fx_config)
    phuebridge.set_light([1, 2], 'on', False)
    
    y = randint(1, 2)
    sleep(y)
    if turn_back_on[1]:
        fx_config = load_fx_config()
        fx_config["enabled"] = True
        write_fx_config(fx_config)
    if turn_back_on[0]:
        phuebridge.set_light([1, 2], 'on', True)

