from flask import Flask, render_template, request, flash, redirect
from forms import HueColorSpanForm
import json

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

@app.route("/")
#def main():
#    return render_template("main.html", **templateData)
@app.route("/index")
def index():
    templateData = json.load(open("../fx_config.json", "r"))
    return render_template("index.html", **templateData)

@app.route("/sethuecolorspan", methods=["GET", "POST"])
def sethuecolorspan():
    fx_config = json.load(open("../fx_config.json", "r"))
    form = HueColorSpanForm()
    if form.validate_on_submit():
        flash("Effect parameters accepted")
        fx_config["effect"] = "hue_color_span"
        fx_config["effect_params"]["start_index"] = form.start_index.data
        fx_config["effect_params"]["starting_hue"] = float(form.starting_hue.data)
        fx_config["effect_params"]["ending_hue"] = float(form.ending_hue.data)
        fx_config["effect_params"]["speed"] = float(form.speed.data)
        fx_config["effect_params"]["compress"] = form.compress.data
        print(form.start_index.data)
        print(type(form.start_index.data))
        print(type(fx_config["effect_params"]["start_index"]))
        print(fx_config)
        json.dump(fx_config, open("../fx_config.json", "w"))
        print("data changed")
        return redirect("/index")
    else:
        form.start_index.data = fx_config["effect_params"]["start_index"]
        form.starting_hue.data = fx_config["effect_params"]["starting_hue"]
        form.ending_hue.data = fx_config["effect_params"]["ending_hue"]
        form.speed.data = fx_config["effect_params"]["speed"]
        form.compress.data = fx_config["effect_params"]["compress"]

        return render_template("huecolorspan.html", form=form)

if __name__ == "__main__":

    app.run(host="0.0.0.0", port=80, debug=True)
