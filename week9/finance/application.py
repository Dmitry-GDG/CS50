import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
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
    """Show portfolio of stocks"""
    """return apology("TODO_index")"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id ORDER BY symbol ASC", user_id=session["user_id"])
    user = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    grand_total = 0.0
    profit = 10000.00

    for i in range(len(stocks)):
        stock = lookup(stocks[i]["symbol"])
        stocks[i]["company"] = stock["name"]
        stocks[i]["cur_price"] = "%.3f" % (stock["price"])
        grand_total += (float(stock["price"]) * float(stocks[i]["quantity"]))
        stocks[i]["cur_total"] = "%.2f" % (float(stock["price"]) * float(stocks[i]["quantity"]))
        stocks[i]["profit"] = "%.2f" % (float(stocks[i]["cur_total"]) - float(stocks[i]["total"]))
        stocks[i]["total"] = "%.2f" % (stocks[i]["total"])

    grand_total += float(user[0]["cash"])
    profit = grand_total - profit

    return render_template("index.html", stocks=stocks, cash=usd(user[0]["cash"]), grand_total=usd(grand_total), profit=usd(profit))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    """return apology("TODO_buy")"""
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Store the dictionary returned from the search in a variable
        stock = lookup(request.form.get("symbol"))

        # Store the shares inputed
        quantity = request.form.get("shares")

        # If the symbol searched or number of shares is invalid, return apology
        if stock == None:
            return apology("invalid symbol", 400)
        elif not quantity.isdigit() or int(quantity) < 1:
            return apology("share must be at least 1", 400)

        symbol = request.form.get("symbol").upper()
        user_id = session["user_id"]

        # calculate total price
        total_price = float(stock["price"]) * float(quantity)

        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)
        funds = float(user[0]["cash"])

        # check if user has enough funds
        if funds < total_price:
            return apology("not enough funds", 400)

        funds_left = funds - total_price

        # check if symbol is already owned
        stock_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                              user_id=user_id, symbol=symbol)

        # update with new price if already owned
        if len(stock_db) == 1:

            new_quantity = int(stock_db[0]["quantity"]) + int(quantity)
            new_total = float(stock_db[0]["total"]) + total_price
            new_pps = "%.2f" % (new_total / float(new_quantity))

            db.execute("UPDATE stocks SET quantity = :quantity, total = :total, pps = :pps WHERE user_id = :user_id AND symbol = :symbol",
                       quantity=new_quantity, total=new_total, pps=new_pps, user_id=user_id, symbol=symbol)

        # else create a new entry in db
        else:

            db.execute("INSERT INTO stocks (user_id, symbol, quantity, total, pps) VALUES (:user_id, :symbol, :quantity, :total, :pps)",
                       user_id=user_id, symbol=symbol, quantity=quantity, total=total_price, pps=stock["price"])

        # modify available funds
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=funds_left, id=user_id)

        # commit to history
        db.execute("INSERT INTO history (user_id, action, symbol, quantity, pps) VALUES (:user_id, :action, :symbol, :quantity, :pps)",
                   user_id=user_id, action=1, symbol=symbol, quantity=quantity, pps=stock["price"])

        # send a success message
        return render_template("success.html", action="bought", quantity=quantity,
                               name=stock["name"], total=usd(total_price), funds=usd(funds_left))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    """return apology("TODO_history")"""
    # retrieve history from db
    stocks = db.execute("SELECT * FROM history WHERE user_id = :user_id ORDER BY date DESC", user_id=session["user_id"])

    # calculate total price of transaction
    for i in range(len(stocks)):
        stocks[i]["total"] = "%.2f" % (float(stocks[i]["quantity"]) * float(stocks[i]["pps"]))

    # render table
    return render_template("history.html", stocks=stocks)


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
    """return apology("TODO")"""
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure a symbol was submited
        if not request.form.get("symbol"):
            return apology("write a symbol", 400)

        # request stock information
        stock = lookup(request.form.get("symbol"))

        if not stock:
            return apology("symbol not found", 400)

        return render_template("quoted.html", symbol=stock["symbol"], name=stock["name"], price=usd(stock["price"]))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    """return apology("TODO")"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        special_symbols = ['!', '#', '$', '%', '.', '_', '&']

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure the username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure the username doesn't exists
        elif len(rows) != 0:
            return apology("username already exists", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure confirmation password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide a confirmation password", 400)

        elif len(password) < 8:
            return apology("Your password must contain 8 or more characters", 400)

        elif not any(char.isdigit() for char in password):
            return apology("Your password must contain at least 1 number", 400)

        elif not any(char.isupper() for char in password):
            return apology("Your password must contain at least uppercase letter", 400)

        elif not any(char in special_symbols for char in password):
            return apology("Your password must contain at least 1 approved symbol", 400)

        # Ensure passwords match
        elif not password == confirmation:
            return apology("passwords must match", 400)

        else:
            # Generate the hash of the password
            hash = generate_password_hash(
                password, method="pbkdf2:sha256", salt_length=8
            )
            # Insert the new user
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?) ", username, hash,
            )

        # login user automatically and remember session
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        # redirect to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    """return apology("TODO_sell")"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id", user_id=session["user_id"])

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure quantity was submited
        if not request.form.get("shares") or int(request.form.get("shares")) < 1:
            return apology("share must be at least 1", 400)

        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()
        quantity = request.form.get("shares")

        # retrieve stock from db
        stock_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                              user_id=user_id, symbol=symbol)
        if stock_db:
            stock_db = stock_db[0]
        else:
            return render_template("sell.html", stocks=stocks)

        # retrieve user data from db
        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)

        # ensure quantity to be sold is available
        if int(quantity) > stock_db["quantity"]:
            return apology("not enough shares", 400)

        # lookup the stock to get current price
        stock = lookup(symbol)

        # calculate total price
        total_price = float(stock["price"]) * float(quantity)

        # modify number of shares owned or delete if < 1
        if int(quantity) == stock_db["quantity"]:
            db.execute("DELETE FROM stocks WHERE user_id = :user_id AND symbol = :symbol", user_id=user_id, symbol=symbol)
        else:
            new_quantity = int(stock_db["quantity"]) - int(quantity)
            new_total = float(new_quantity) * float(stock_db["pps"])
            db.execute("UPDATE stocks SET quantity = :quantity, total = :total WHERE user_id = :user_id AND symbol = :symbol",
                       quantity=new_quantity, total=new_total, user_id=user_id, symbol=symbol)

        # modify available funds
        funds_available = float(user[0]["cash"]) + total_price
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=funds_available, id=user_id)

        # commit to history
        db.execute("INSERT INTO history (user_id, action, symbol, quantity, pps) VALUES (:user_id, :action, :symbol, :quantity, :pps)",
                   user_id=user_id, action=0, symbol=symbol, quantity=quantity, pps=stock["price"])

        # send a success message
        return render_template("success.html", action="sold", quantity=quantity,
                               name=stock["name"], total=usd(total_price), funds=usd(funds_available))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

# add githubkey
#