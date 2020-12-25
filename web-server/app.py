#! /usr/bin/python

from flask import Flask, render_template, flash, redirect, url_for, request
from forms import HueColorSpanForm, DoorwayTrackerForm, IndexForm, StaticForm
import json
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = 'you-will-never-guess'

# effects = ["hue_color_span", "christmas_animation", "static"]

fx_params = {"hue_color_span": {
                "starting_hue": 0.0,
                "ending_hue": 360.0,
                "speed": 60,
                "compress": 1,
                "start_index": 0
                },
            "static": {
                "red": 255,
                "green": 255,
                "blue": 255,
                "include_horizontal": True,
                "include_vertical": True
                }
            }

fx_config_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "share", "fx_config.json")
doorway_states_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "share", "doorway_states.json")



def get_current_fx_data():
    while True:
        try:
            return json.load(open(fx_config_path, "r"))
        except ValueError:
            pass

def set_current_doorway_states(doorway_states):
    while True:
        try:
            json.dump(doorway_states, open(doorway_states_path, "w"))
            break
        except:
            pass


def set_current_fx_data(fx_config):
    while True:
        try:
            json.dump(fx_config, open(fx_config_path, "w"))
            break
        except ValueError:
            pass


@app.route("/", methods=["GET", "POST"])
@app.route("/index", methods=["GET", "POST"])
def index():
    current_fx_config = get_current_fx_data()
    form = IndexForm()
    if form.validate_on_submit():
        flash("Changes applied")
        current_fx_config["enabled"] = form.enabled.data
        current_fx_config["brightness"] = float(form.brightness.data)
        current_fx_config["effect"] = form.effect.data
        set_current_fx_data(current_fx_config)
        return redirect(url_for("index"))
    else:
        form.enabled.data = current_fx_config["enabled"]
        form.brightness.data = current_fx_config["brightness"]
        form.effect.data = current_fx_config["effect"]
        return render_template("index.html", form=form)


@app.route("/sethuecolorspan", methods=["GET", "POST"])
def set_hue_color_span():
    fx_config = get_current_fx_data()
    form = HueColorSpanForm()
    if form.validate_on_submit():
        flash("Effect parameters accepted")
        fx_config["effect_params"]["hue_color_span"]["start_index"] = form.start_index.data
        fx_config["effect_params"]["hue_color_span"]["starting_hue"] = float(form.starting_hue.data)
        fx_config["effect_params"]["hue_color_span"]["ending_hue"] = float(form.ending_hue.data)
        fx_config["effect_params"]["hue_color_span"]["speed"] = float(form.speed.data)
        fx_config["effect_params"]["hue_color_span"]["compress"] = form.compress.data
        fx_config["effect_params"]["hue_color_span"]["direction"] = form.direction.data
        fx_config["effect_params"]["hue_color_span"]["include_vertical"] = form.include_vertical.data
        fx_config["effect_params"]["hue_color_span"]["include_horizontal"] = form.include_horizontal.data
        set_current_fx_data(fx_config)
        return redirect(url_for('index'))
    else:
        form.start_index.data = fx_config["effect_params"]["hue_color_span"]["start_index"]
        form.starting_hue.data = fx_config["effect_params"]["hue_color_span"]["starting_hue"]
        form.ending_hue.data = fx_config["effect_params"]["hue_color_span"]["ending_hue"]
        form.speed.data = fx_config["effect_params"]["hue_color_span"]["speed"]
        form.compress.data = fx_config["effect_params"]["hue_color_span"]["compress"]
        form.direction.data = fx_config["effect_params"]["hue_color_span"]["direction"]
        form.include_vertical.data = fx_config["effect_params"]["hue_color_span"]["include_vertical"]
        form.include_horizontal.data = fx_config["effect_params"]["hue_color_span"]["include_horizontal"]

        return render_template("huecolorspan.html", form=form)


@app.route("/setstatic", methods=["GET", "POST"])
def set_static():
    fx_config = get_current_fx_data()
    form = StaticForm()
    if form.validate_on_submit():
        flash("Effect paramters accepted")
        fx_config["effect_params"]["static"]["red"] = form.red.data
        fx_config["effect_params"]["static"]["green"] = form.green.data
        fx_config["effect_params"]["static"]["blue"] = form.blue.data
        fx_config["effect_params"]["static"]["include_horizontal"] = form.include_horizontal.data
        fx_config["effect_params"]["static"]["include_vertical"] = form.include_vertical.data
        set_current_fx_data(fx_config)
        return redirect(url_for("index"))
    else:
        form.red.data = fx_config["effect_params"]["static"]["red"]
        form.green.data = fx_config["effect_params"]["static"]["green"]
        form.blue.data = fx_config["effect_params"]["static"]["blue"]
        form.include_horizontal.data = fx_config["effect_params"]["static"]["include_horizontal"]
        form.include_vertical.data = fx_config["effect_params"]["static"]["include_vertical"]

        return render_template("static.html", form=form)


@app.route("/setdoorwaytracker", methods=["GET", "POST"])
def set_doorway_tracker():
    current_addons = []
    form = DoorwayTrackerForm()
    current_fx_config = get_current_fx_data()
    current_doorway_config = {"name": "doorway_tracker",
                              "enabled": True,
                              "style": "middle_out",
                              "blank_color": (0, 0, 0),
                              "enter_color": (0, 255, 0),
                              "exit_color": (255, 0, 0)}

    for addon in current_fx_config["addons"]:
        if addon["name"] != "doorway_tracker":
            current_addons.append(addon)
        else:
            current_doorway_config = addon
    
    if form.validate_on_submit():
        flash("Doorway Tracker Config updated")
        current_doorway_config["enabled"] = form.enabled.data
        current_doorway_config["style"] = form.style.data
        current_doorway_config["blank_color"] = (form.blank_color_red.data, form.blank_color_green.data,
                                                 form.blank_color_blue.data)
        current_doorway_config["enter_color"] = (form.enter_color_red.data, form.enter_color_green.data,
                                                 form.enter_color_blue.data)
        current_doorway_config["exit_color"] = (form.exit_color_red.data, form.exit_color_green.data,
                                                form.exit_color_blue.data)

        current_addons.append(current_doorway_config)
        current_fx_config["addons"] = current_addons
        set_current_fx_data(current_fx_config)

        return redirect(url_for("index"))

    else:
        form.enabled.data = current_doorway_config["enabled"]
        form.style.data = current_doorway_config["style"]
        
        blank_color = current_doorway_config["blank_color"]
        form.blank_color_red.data = blank_color[0]
        form.blank_color_green.data = blank_color[1]
        form.blank_color_blue.data = blank_color[2]

        enter_color = current_doorway_config["enter_color"]
        form.enter_color_red.data = enter_color[0]
        form.enter_color_green.data = enter_color[1]
        form.enter_color_blue.data = enter_color[2]

        exit_color = current_doorway_config["exit_color"]
        form.exit_color_red.data = exit_color[0]
        form.exit_color_green.data = exit_color[1]
        form.exit_color_blue.data = exit_color[2]

        return render_template("doorway_tracker.html", form=form)


@app.route("/setdoorwaystate", methods=["POST"])
def set_doorway_state():
    doorway_states = request.json
    set_current_doorway_states(doorway_states)

    return json.dumps({'success': True}), 200, {'ContentType': 'application/json'}

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80, debug=True)
