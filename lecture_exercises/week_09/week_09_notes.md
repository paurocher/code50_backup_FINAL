#Flask
It's a web framework (a toolkit).
Python makes websites become much more dynamic. Handles interaction on the web via routes and http requests and renders HTM files.

#Requirements.txt is important!!


####Anatomy of a web address
http://: protocol (hyper text transfer protocol secure)
birthdays.com: domain
/: route, root page of the domain in this case

http://birthdays.com/about-us: here route is "/about-us"


We apply a decorator on the functions to bind the to the specific html files.
The decorator means: execute this function each time the user access this route.
```
from flask import Flask

# init the application
app = Flask(__name__)

# write the functions

@app.route("/")  # home page
def index():
    return "You are at the index page!"

@app.route("/sample")
def sample()
    return "You are at the sample page!"
```

#####To run the flask application in the cs50 ide:
In the terminal:
  1. `export FLASK_APP=application.py'  # (or wathever your app is named)
  2. `export FLASK_DEBUG=1'  # displays debug messages in the terminal
  3. `flask run`  # will give you the url to visit
(Steps 1 and 2 are not mandatory).


####Pass data from an URL

#####From the web address
```
@app.route("/show/<number>")
def show(number):
    return "You passed in {}".format(number)
```
When running, if we visit "../../../show/10" we will get a page that says "You passed in 10".

#####From an HTML form
POST and GET
GET is when the user wants to get a page or data from the server. It puts the request parameters in the url field.
POST is when the user sends data to the server. It does not put any data in the url field so the sent data can not be retrieved by a hacker reading the address bar or the request sent to the server.
We need to specify the request method on the function for it to get from POST or GET or both.
```
@app.route("/login", methods=["GET", "POST"])
def login():
    if not request.form.get("username"):
        return apology("must provide username")
```
`request.form.get("username")`: retrieve value from the from the field named "username". (This is not the dict.get() method)
This function can be tweaked to behave differently depending on the http request it got (post or get). For example if we get a get we can show the page with a form to log in, otherwise we assume they entered some login info and we show them another page.
`if request.method == "POST": ...`

####Pass data to an url from flask
`return render_template("index.html, birthdays=rows)` (example from the birthdays problem set)
Passes whatever row is to the name 'birthday' on on index.html in junja language: `{{ birthdays }}`


####Useful flask functions:
  - url_for()
  - redirect() takes you to another page
  - session() track variables
  - render_template() mixes html and python together (via jinja) via an html template
  -
  -
  -


###flask quickstart guide
http://flask.pocoo.org/docs/0.12/quickstart

###jinja user guide
http://jinja.pocoo.org/


###Forms
<form></form>


###SQL
To avoid sql injection attacks the cs50 library offers the "?" placeholder. This allows us to not use 'f' strings that are very vulnerable to those attacks.


###Jinja
in curly braces:
`{{ var_name }}` to get a variable passed from python via `return render_template("index.html, birthdays=rows)`

`{% code %}` to write more complex code like loops and whatnot.

