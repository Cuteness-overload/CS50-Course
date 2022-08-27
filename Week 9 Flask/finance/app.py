import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensurresponses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Getting the info from the DB
    # SUM and GROUP BY in case of multiple buys of the same share
    portfolio = db.execute(
        "SELECT id, symbol, name, price, SUM(shares) AS tshares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    acc_bal = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    # caclulate total balance of the account
    total_bal = acc_bal
    pricelist = {}
    for stock in portfolio:
        # getting current price
        price = lookup(stock["symbol"])["price"]
        total_bal += stock["tshares"] * price
        pricelist[stock["id"]] = price

    # Push everything to the page
    return render_template("index.html", portfolio=portfolio, acc_bal=acc_bal, total_bal=total_bal, pricelist=pricelist, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        response = lookup(symbol)
        user_id = session["user_id"]
        acc_bal = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # check if symbol was typed and valid
        if not symbol:
            return apology("missing symbol")
        elif not response:
            return apology("symbol does not exist")
        # try converting what was typed into an int and check if positive
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Please input an integer")
        if shares <= 0:
            return apology("shares should be at least one")

        # Get some info out into variables for future use
        name = response["name"]
        price = response["price"]
        total = price * shares

        # Check if user has enough money on his account
        if acc_bal < total:
            return apology("balance not high enough")
        # Buy the stocks and put all that info in the transactions DB
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", acc_bal - total, user_id)
            db.execute("INSERT INTO transactions(user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, name, shares, price, 'buy', symbol)
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    history = db.execute("SELECT type, symbol, shares, price, time FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", history=history, usd=usd)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

        response = lookup(request.form.get("symbol"))
        init_symbol = request.form.get("symbol")
        # Check if user input a symbol
        if not init_symbol:
            return apology("missing symbol", 400)
        # check if symbol exists
        elif not response:
            return apology("symbol does not exist", 400)
        # get the responses from the lookup function
        comp_name = response["name"]
        comp_price = usd(response["price"])
        comp_symbol = response["symbol"]

        return render_template("quoted.html", comp_name=comp_name, comp_price=comp_price, comp_symbol=comp_symbol)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # query_input = "SELECT username FROM users WHERE username = %s"
        usercheck = db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username"))
        hashed = generate_password_hash(request.form.get("password"), method='sha256', salt_length=6)
        user = request.form.get("username")

        # Ensure username is unique and was submitted
        if usercheck:
            return apology("username already in use", 400)
        elif not user:
            return apology("must provide username", 400)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        # Ensure password confirmation was submitted and same as password
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords must be identical", 400)
        # Hash password and insert user and hash into the DB
        db.execute("INSERT INTO users (username, hash) VALUES (?,?)", user, hashed)

        # go to the login and access the site
        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        # getting the user input and other info
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # account and share info
        price = lookup(symbol)["price"]
        totalprice = price * shares
        name = lookup(symbol)["name"]

        user_shares = db.execute(f"SELECT SUM(shares) FROM transactions WHERE user_id = {user_id} AND  symbol = '{symbol}' GROUP BY symbol")[
            0]["SUM(shares)"]
        acc_bal = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        print(user_shares, shares)
        # Making sure everything is in order
        if shares <= 0:
            return apology("shares must be a positive number")
        elif shares > user_shares:
            return apology("You don't have that many!")

        db.execute("UPDATE users SET cash = ? WHERE id = ?", acc_bal + totalprice, user_id)
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, name, -shares, price, 'sell', symbol)

        return redirect("/")
    else:
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", symbols=symbols)
