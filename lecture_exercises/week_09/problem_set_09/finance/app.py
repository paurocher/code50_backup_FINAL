import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, get_history, get_cash_total

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
DB = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    cash = DB.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]

    symbols = DB.execute("SELECT symbol FROM history WHERE user_id == ?", session["user_id"])
    symbols = set([symbol["symbol"] for symbol in symbols])

    # get total shares of each symbol
    totals = []
    shares = []
    for symbol in symbols:
        share = {}
        a = DB.execute(
            "SELECT SUM(amount) FROM history where user_id IS ? AND symbol IS ?",
            session["user_id"],
            symbol
        )
        price = lookup(symbol)["price"]
        amount = a[0]["SUM(amount)"]
        total_price = price * amount

        share["symbol"] = symbol
        share["amount"] = amount
        share["share_price"] = price
        share["total_price"] = total_price
        shares.append(share)

        totals.append(total_price)

    user_name = DB.execute(
        "SELECT username FROM users WHERE id IS ?", session["user_id"]
    )[0]["username"]

    return render_template(
        "index.html",
        shares=shares,
        cash=usd(cash),
        total=usd(sum(totals) + cash),
        user_name=user_name
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares")
        if not shares.isdigit() or not shares.isdecimal():
            return apology("Invalid shares", 400)

        found = request.form.get("symbol").upper()
        found = lookup(found)
        if not found:
            return apology("Stock symbol not found")

        share_price = found["price"]
        # print(share_price, type(share_price))


        total_price = int(share_price) * int(shares)


        # check if enough funds available
        cash = int(DB.execute("SELECT cash FROM users WHERE id == ?",
                   session["user_id"])[0]["cash"])
        if cash > total_price:
            DB.execute(
                "INSERT INTO history (user_id, symbol, amount, share_price, total_price) VALUES (?, ?, ?, ?, ?)",
                session["user_id"],
                found["symbol"],
                shares,
                share_price,
                total_price
            )

            cash -= total_price
            DB.execute("UPDATE users SET cash = ? WHERE id IS ?", cash, session["user_id"])

            cash, total = get_cash_total()
            return index()
        else:
            flash(f"Transaction total: {usd(total_price)}, funds available: {usd(cash)}")
            return render_template("buy.html")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return render_template("history.html", history=get_history(session))


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = DB.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        found = request.form.get("symbol")
        found = lookup(found)
        if found:
            price = usd(found["price"])
            return render_template("quoted.html", found=found, price=price)
        else:
            # flash("Stock sybol mot found.")
            return apology("Stock sybol mot found.", 400)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        user_name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if user_name == "" or password == "" or confirmation == "":
            return apology(f"Must choose a user name.", 400)

        # verify password check
        if password != confirmation:
            return apology(f"Password and confirmation must match.", 400)

        # verify DB for for existing user
        if DB.execute("SELECT * FROM users WHERE username IS ?", user_name):
            return apology(f"User name {user_name} already exists.", 400)
        else:
            password_hash = generate_password_hash(password)
            DB.execute("INSERT INTO users (username, hash) VALUES (?, ?)", user_name, password_hash)
            # pass a flash message here
            flash('You were successfully registered!!\n  You may log in now :)')
            return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # check available amount of stock
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        available = int(
            DB.execute(
                "SELECT SUM(amount) FROM history WHERE user_id IS ? AND symbol IS ?",
                session["user_id"],
                symbol
            )[0]["SUM(amount)"]
        )

        # if not enough
        if shares > available:
            return apology(f"Available stock ({available}) lower than sell amount ({shares})")

        # there is enough stock to sell:
        found = request.form.get("symbol")
        found = lookup(found)

        share_price = found["price"]
        total_price = share_price * shares

        DB.execute(
            "INSERT INTO history (user_id, symbol, amount, share_price, total_price) VALUES (?, ?, ?, ?, ?)",
            session["user_id"],
            request.form.get("symbol"),
            -shares,
            share_price,
            -total_price
        )

        # return earned money back to the table
        cash = int(
            DB.execute(
                "SELECT cash FROM users WHERE id == ?",
                session["user_id"]
            )[0]["cash"]
        )
        cash += total_price
        DB.execute(
            "UPDATE users SET cash = ? WHERE id IS ?", cash, session["user_id"]
        )
        return index()

    rows = set([row["symbol"] for row in get_history(session)])
    return render_template("sell.html", rows=sorted(rows))


@app.route("/psswd_change", methods=["GET", "POST"])
@login_required
def psswd_change():
    if request.method == "POST":
        new = request.form.get("new_password")
        retype = request.form.get("retype_password")

        # check new and retype match
        if new != retype:
            return apology(f"Password and confirmation must match.", 401)

        password_hash = generate_password_hash(new)
        DB.execute("UPDATE users SET hash = ? WHERE id IS ?", password_hash, session["user_id"])
        flash("Password change successful.")
        return index()

    return render_template("psswd_change.html")
