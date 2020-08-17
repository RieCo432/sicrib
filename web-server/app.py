from flask import Flask, render_template, flash, redirect, url_for
from forms import HueColorSpanForm
import json
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = 'you-will-never-guess'

effects = ["hue_color_span", "christmas_animation"]

fx_params = {"hue_color_span": {
                "starting_hue": 0.0,
                "ending_hue": 360.0,
                "speed": 60,
                "compress": 1,
                "start_index": 0}
            }

fx_config_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), os.pardir, "share", "fx_config.json")

def get_current_fx_data():
    return json.load(open(fx_config_path, "r"))


def set_current_fx_data(fx_config):
    json.dump(fx_config, open(fx_config_path, "w"))


@app.route("/")
@app.route("/index")
def index():
    return render_template("index.html", **get_current_fx_data())


@app.route("/on")
def on():
    fx_config = get_current_fx_data()
    fx_config["enabled"] = True
    set_current_fx_data(fx_config)
    return redirect(url_for('index'))


@app.route("/off")
def off():
    fx_config = get_current_fx_data()
    fx_config["enabled"] = False
    set_current_fx_data(fx_config)
    return redirect(url_for('index'))


@app.route("/sethuecolorspan", methods=["GET", "POST"])
def set_hue_color_span():
    fx_config = get_current_fx_data()
    form = HueColorSpanForm()
    if form.validate_on_submit():
        flash("Effect parameters accepted")
        fx_config["effect"] = "hue_color_span"
        fx_config["effect_params"]["start_index"] = form.start_index.data
        fx_config["effect_params"]["starting_hue"] = float(form.starting_hue.data)
        fx_config["effect_params"]["ending_hue"] = float(form.ending_hue.data)
        fx_config["effect_params"]["speed"] = float(form.speed.data)
        fx_config["effect_params"]["compress"] = form.compress.data
        set_current_fx_data(fx_config)
        print("data changed")
        return redirect(url_for('index'))
    else:
        form.start_index.data = fx_config["effect_params"]["start_index"]
        form.starting_hue.data = fx_config["effect_params"]["starting_hue"]
        form.ending_hue.data = fx_config["effect_params"]["ending_hue"]
        form.speed.data = fx_config["effect_params"]["speed"]
        form.compress.data = fx_config["effect_params"]["compress"]

        return render_template("huecolorspan.html", form=form)


@app.route("/setchristmasanimation")
def set_christmas_animation():
    fx_config = get_current_fx_data()
    fx_config["effect"] = "christmas_animation"
    set_current_fx_data(fx_config)
    return redirect(url_for('index'))


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80, debug=True)
