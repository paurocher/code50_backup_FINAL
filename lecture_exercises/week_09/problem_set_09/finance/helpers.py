import requests

from flask import redirect, render_template, session
from functools import wraps
from cs50 import SQL

DB = SQL("sqlite:///finance.db")


def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""
    url = f"https://finance.cs50.io/quote?symbol={symbol.upper()}"
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an error for HTTP error responses
        quote_data = response.json()
        return {
            "name": quote_data["companyName"],
            "price": quote_data["latestPrice"],
            "symbol": symbol.upper()
        }
    except requests.RequestException as e:
        print(f"Request error: {e}")
    except (KeyError, ValueError) as e:
        print(f"Data parsing error: {e}")
    return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"


def get_history(session):
    """Get the history rows for this user."""
    return DB.execute("SELECT * FROM history WHERE user_id == ?", session["user_id"])


def get_cash_total():
    try:
        cash = DB.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]["cash"]
        transactions_total = DB.execute(
            "SELECT total_price FROM history WHERE user_id == ?", session["user_id"])[0]["total_price"]
    except IndexError:
        cash = 10000
        transactions_total = 0
    print("fffffffff", cash, transactions_total)

    return cash, cash + transactions_total
    # return 11, 22
