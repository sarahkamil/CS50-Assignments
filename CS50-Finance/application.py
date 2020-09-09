import os
import datetime

from cs50 import SQL
import sqlite3
db = SQL("sqlite:///finance.db")
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    rows = db.execute("SELECT * FROM transactions WHERE username = ?", (session["username"]))
    stock_amounts = {}
    for row in rows:
        if row["stock_symbol"] not in stock_amounts.keys():
            stock_amounts[row["stock_symbol"]] = row["num_shares"]
        else:
            stock_amounts[row["stock_symbol"]] += row["num_shares"]
    new_rows = []
    grand_total = 0
    for k in stock_amounts.keys():
            if stock_amounts[k] > 0:
                new_rows.append({"num_shares":stock_amounts[k],
                                 "stock_symbol":k,
                                 "stock_name":lookup(k)["name"],
                                 "stock_price":round(lookup(k)["price"], 2),
                                 "total":round(stock_amounts[k]*lookup(k)["price"], 2)
                })
                grand_total += stock_amounts[k]*lookup(k)["price"]
    current_user_cash = db.execute("SELECT * FROM users WHERE username = ?", (session["username"]))[0]["cash"]
    new_rows.append({"num_shares":"",
                             "stock_symbol":"CASH",
                             "stock_name":"",
                             "stock_price":"",
                             "total":round(current_user_cash, 2)
            })
    grand_total += current_user_cash
    new_rows.append({"num_shares":"",
                             "stock_symbol":"",
                             "stock_name":"",
                             "stock_price":"",
                             "total":round(grand_total, 2)
            })

    total = db.execute("SELECT (num_shares * stock_price) FROM transactions")
    return render_template("index.html", rows=new_rows)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":

        #Get form input
        symbol = request.form.get("symbol")
        num_shares = request.form.get("shares")

        if symbol == '' or num_shares == '':
            return render_template("apology.html", message="You have to enter both fields.")

        num_shares = int(num_shares)
        if num_shares <= 0:
            return render_template("apology.html", message="Please enter a positive number.")

        #Check if symbol valid
        stock_info = lookup(symbol)
        if stock_info == None:
            return render_template("apology.html", message="Please enter a valid stock symbol.")

        stock_name = stock_info["name"]
        total_price = num_shares * stock_info["price"]

        query_result = db.execute("SELECT cash FROM users WHERE username = ?", (session["username"]))
        mycash = query_result[0]["cash"]

        if total_price > mycash:
            return render_template("apology.html", message=f"You have ${mycash}, but the purchase costs ${total_price}.")
        else:
            #update user's cash in users table
            new_cash = mycash - total_price
            db.execute("UPDATE users SET cash = ? WHERE username = ?", (new_cash, session["username"]))
            db.execute("INSERT INTO transactions VALUES (?, ?, ?, ?, ?, ?, ?)",
                      (None,
                      session["username"],
                      symbol,
                      stock_name,
                      num_shares,
                      stock_info["price"],
                      datetime.datetime.now()))
            #return index page with transaction table
            return redirect("/")


@app.route("/history")
@login_required
def history():
    rows = db.execute("SELECT * FROM transactions WHERE username = ?", (session["username"]))
    return render_template("history.html", rows=rows)

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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = request.form.get("username")

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
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        stock_info = lookup(symbol)
        print(stock_info)
        if stock_info == None:
            return render_template("quoted.html", stock_info="Please enter a valid stock symbol.")
        else:
            return render_template("quoted.html", stock_info=f"A share of {stock_info['name']} costs {stock_info['price']}.")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirm_password")
        query_result=db.execute("SELECT username FROM users")
        userlist=[]
        for result in query_result:
            userlist.append(result['username'])
        if not username or not password or not confirm_password:
            return render_template("apology.html", message="You must provide a username and password.")
        if len(password) < 8:
            return render_template("apology.html", message="Your password must be at least 8 characters long.")
        if username in userlist:
            return render_template("apology.html", message="This username is already taken. Please choose a new one.")
        if password != confirm_password:
            return render_template("apology.html", message="Your passwords must match.")
        else:
            print("all good")
            db.execute("INSERT INTO users(username, hash) VALUES (:username, :password_hash)", username=username, password_hash=generate_password_hash(password))
            return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        return render_template("sell.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        num_shares = request.form.get("shares")
        if symbol == '' or num_shares == '':
            return render_template("apology.html", message="You have to enter both fields.")

        num_shares = int(num_shares)
        if num_shares <= 0:
            return render_template("apology.html", message="Please enter a positive number.")

        stock_info = lookup(symbol)
        if stock_info == None:
            return render_template("apology.html", message="Please enter a valid stock symbol.")

        stock_name = stock_info["name"]
        total_price = num_shares * stock_info["price"]

        query_result = db.execute("SELECT cash FROM users WHERE username = ?", (session["username"]))
        mycash = query_result[0]["cash"]

        stocknames = db.execute("SELECT stock_name FROM transactions WHERE username = ?", (session["username"]))

        count_stocks = db.execute("SELECT SUM(num_shares) FROM transactions WHERE stock_name = ?", stock_name)
        if count_stocks[0]["SUM(num_shares)"] == None:
            return render_template("apology.html", message="Please enter a stock that you actually own.")
        else:
            counted_stocks = count_stocks[0]["SUM(num_shares)"]
            if num_shares > counted_stocks:
                return render_template("apology.html", message="You are trying to sell more shares of this stock than you own.")
            else:
                 #update user's cash in users table
                new_cash = mycash + total_price
                db.execute("UPDATE users SET cash = ? WHERE username = ?", (new_cash, session["username"]))
                db.execute("INSERT INTO transactions VALUES (?, ?, ?, ?, ?, ?, ?)",
                          (None,
                          session["username"],
                          symbol,
                          stock_name,
                          -num_shares,
                          stock_info["price"],
                          datetime.datetime.now()))
                #return index page with transaction table
                return redirect("/")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
