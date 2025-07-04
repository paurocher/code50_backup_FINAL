from flask import Flask, redirect, render_template, request, session
from flask_session import Session

app = Flask(__name__)

# Get sessions working in a recommended manner
app.config["SESSION_PERMANENT"] = False  # seletes everything in the session once the session ends when closing the browser or the tab. It's a session cookie.
app.config["SESSION_TYPE"] = "filesystem"  # ensures the contents of the shopping cart are stored in the server and not locally
Session(app)  # activates the session on this app

@app.route("/")
def index():
    return render_template("index.html", name=session.get("name"))


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        # the session var is a dict
        session["name"] = request.form.get("name")
        return redirect("/")  # redirect the user back to the home page to see if they are in fact logged in at that point.
    return render_template("login.html")

@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")
