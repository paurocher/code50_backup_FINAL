from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite show: ")

rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE problem = ?", favorite) # .execute is a function that comes in with the cs50 library
# the '?' is like a %s in a python string
# this gives us back a temp table that we store in 'rows'

print(rows[0]["n"])
