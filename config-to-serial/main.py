import json
import os
from time import sleep
import serial

fx_config_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "share", "fx_config.json")

connected = False
attempts_left = 60
while not connected and attempts_left > 1:
    try:
        ser = serial.Serial('/dev/serial0', 9600, timeout=2)
        ser.flush()
        connected = True
        print("connected!")
    except serial.serialutil.SerialException:
        sleep(5)
        attempts_left -= 1
        pass

if not connected:
    exit(1)

def load_fx_config():
    while True:
        try:
            with open(fx_config_path, "r") as fin:
                return json.load(fin)
        except ValueError:
            pass

old_fx_config = None

while True:
    fx_config = load_fx_config()
    if fx_config != old_fx_config or old_fx_config is None:
        old_fx_config = fx_config
        line = (json.dumps(fx_config) + "\n").encode('utf-8')
        ser.write(line)
        print("written:", line)
        if ser.in_waiting: 
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
    sleep(0.5)
