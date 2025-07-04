import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = int(request.form.get("month"))
        day = int(request.form.get("day"))
        print(day)

        if all([name, day, month]):
            if month in list(range(1, 13)) and day in list(range(1, 32)):
                db.execute(
                    "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
                    name,
                    month,
                    day
                )

        return redirect("/")

    else:
        rows = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=rows)


@app.route("/remove", methods=["POST"])
def remove():
    id = request.form.get("id")
    db.execute("DELETE FROM birthdays WHERE id = ?", id)
    rows = db.execute("SELECT * FROM birthdays")
    return render_template("index.html", birthdays=rows)
