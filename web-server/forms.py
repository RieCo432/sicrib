from flask_wtf import FlaskForm
from wtforms import SubmitField, DecimalField, IntegerField, BooleanField, RadioField
# from wtforms.validators import DataRequired


class IndexForm(FlaskForm):
    enabled = BooleanField("enabled")
    brightness = DecimalField("brightness")
    effect = RadioField("effect", choices=["hue_color_span_rainbow", "hue_color_span_cycle",
                                           "christmas_animation", "static", "rave", "alis_random_equilibrium", "none"])
    submit = SubmitField("Apply")


class HueColorSpanForm(FlaskForm):
    start_index = IntegerField("start_index")  # , validators=[DataRequired()])
    starting_hue = DecimalField("Starting Hue")  # , validators=[DataRequired()])
    ending_hue = DecimalField("Ending Hue")  # , validators=[DataRequired()])
    period = DecimalField("Period")  # , validators=[DataRequired()])
    compress = IntegerField("Compress")  # , validators=[DataRequired()])
    direction = RadioField("Direction", choices=["horizontal", "vertical"])
    include_vertical = BooleanField("include_vertical")
    include_horizontal = BooleanField("include_horizontal")
    submit = SubmitField("Apply")


class RaveForm(FlaskForm):
    include_n = BooleanField("Include North")
    include_ne = BooleanField("Include North East")
    include_e = BooleanField("Include East")
    include_se = BooleanField("Include South East")
    include_s = BooleanField("Include South")
    include_sw = BooleanField("Include South West")
    include_w = BooleanField("Include West")
    include_nw = BooleanField("Include North West")

    include_red = BooleanField("Include Red")
    include_green = BooleanField("Include Green")
    include_blue = BooleanField("Include Blue")
    include_turquoise = BooleanField("Include Turquoise")
    include_yellow = BooleanField("Include Yellow")
    include_magenta = BooleanField("Include Magenta")
    include_black = BooleanField("Include Black")
    include_white = BooleanField("Include White")

    min_edges = IntegerField("Minimum edges")
    max_edges = IntegerField("Maximum edges")

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
