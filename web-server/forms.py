from flask_wtf import FlaskForm
from wtforms import SubmitField, DecimalField, IntegerField
#from wtforms.validators import DataRequired


class HueColorSpanForm(FlaskForm):
    start_index = IntegerField("start_index") #, validators=[DataRequired()])
    starting_hue = DecimalField("Starting Hue") #, validators=[DataRequired()])
    ending_hue = DecimalField("Ending Hue") #, validators=[DataRequired()])
    speed = DecimalField("Speed") #, validators=[DataRequired()])
    compress = IntegerField("Compress") #, validators=[DataRequired()])
    submit = SubmitField("Apply")
