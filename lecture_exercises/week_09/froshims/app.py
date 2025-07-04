from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee",
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():
    """This code is valid for the pulldown menu. It has to be tweaked for the checkboxes and radio buttons.
    request.form.getlist() to get all checkboxes or radio buttons."""
    if not request.form.get("name") or not request.form.get("sport") in SPORTS:
        return render_template("failure.html")
    return render_template("success.html")

