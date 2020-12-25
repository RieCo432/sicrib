from flask_wtf import FlaskForm
from wtforms import SubmitField, DecimalField, IntegerField, BooleanField, RadioField, StringField
#from wtforms.validators import DataRequired


class IndexForm(FlaskForm):
    enabled = BooleanField("enabled")
    brightness = DecimalField("brightness")
    effect = RadioField("effect", choices=["hue_color_span", "christmas_animation", "static", "none"])
    submit = SubmitField("Apply")


class HueColorSpanForm(FlaskForm):
    start_index = IntegerField("start_index") #, validators=[DataRequired()])
    starting_hue = DecimalField("Starting Hue") #, validators=[DataRequired()])
    ending_hue = DecimalField("Ending Hue") #, validators=[DataRequired()])
    speed = DecimalField("Speed") #, validators=[DataRequired()])
    compress = IntegerField("Compress") #, validators=[DataRequired()])
    direction = RadioField("Direction", choices=["horizontal", "vertical"])
    include_vertical = BooleanField("include_vertical")
    include_horizontal = BooleanField("include_horizontal")
    submit = SubmitField("Apply")


class StaticForm(FlaskForm):
    red = IntegerField("red")
    green = IntegerField("green")
    blue = IntegerField("blue")
    include_vertical = BooleanField("include_vertical")
    include_horizontal = BooleanField("include_horizontal")
    submit = SubmitField("Apply")


class DoorwayTrackerForm(FlaskForm):
    enabled = BooleanField("Enabled")
    style = RadioField("Style", choices=["middle_out", "left_to_right"])
    blank_color_red = IntegerField("blank_color_red")
    blank_color_green = IntegerField("blank_color_green")
    blank_color_blue = IntegerField("blank_color_blue")

    enter_color_red = IntegerField("enter_color_red")
    enter_color_green = IntegerField("enter_color_green")
    enter_color_blue = IntegerField("enter_color_blue")

    exit_color_red = IntegerField("exit_color_red")
    exit_color_green = IntegerField("exit_color_green")
    exit_color_blue = IntegerField("exit_color_blue")

    submit = SubmitField("Apply")
