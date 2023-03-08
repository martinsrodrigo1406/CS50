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
    portfolio = db.execute("SELECT * FROM holds WHERE user_id = ? GROUP BY symbol ", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    prices = {}

    total = 0.0

    for index, row in enumerate(portfolio):
        prices = lookup(row["symbol"])
        portfolio[index]['price'] = prices["price"]
        portfolio[index]['eachsharetotal'] = prices["price"] * row["amount"]
        total = total + (prices["price"] * row["amount"])



    return render_template("index.html", userportfolio = portfolio, cashnow = cash[0]["cash"], total = total)




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        shareQuoted = {}
        newShares = 0

        if not request.form.get("symbol"):
            return apology("Sorry, please type a valid symbol", 400)

        shareQuoted = lookup(request.form.get("symbol"))
        if not shareQuoted:
            return apology("Not found. Type a valid symbol", 400)

        if not request.form.get("shares"):
            return apology("Sorry, please type a valid number of shares to buy", 400)

        while True:
            try:
                newShares = int(request.form.get("shares"))
                break
            except ValueError:
                return apology("Sorry, please type a valid number of shares to buy", 400)

        if newShares <= 0:
            return apology("Sorry, please type a valid number of shares to buy", 400)

        oldShares = db.execute("SELECT amount FROM holds WHERE user_id = :userid AND symbol = :symbol", userid = session["user_id"], symbol = shareQuoted["symbol"])

        if oldShares:
            totalShares = newShares + oldShares[0]["amount"]
        else:
            totalShares = newShares

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        price = shareQuoted["price"]


        if cash[0]["cash"] >= (price * newShares):
            remainingCash = cash[0]["cash"] - (price * newShares)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", remainingCash, session["user_id"])
            db.execute("INSERT OR REPLACE INTO holds(user_id, symbol, name, amount) VALUES(:userid, :symbol, :name, :sharesNum)", symbol = shareQuoted["symbol"], name = shareQuoted["name"], sharesNum = totalShares, userid = session["user_id"])

            db.execute("INSERT INTO transactions VALUES(?, ?, ?, ?, ?, DateTime('now'))", session["user_id"], shareQuoted["symbol"], "buy", newShares, price)

            # Redirect user to home page
            return redirect("/")
        else:
            return apology("Your cash is not enough, unfortunately", 400)

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY date", session["user_id"])
    return render_template("history.html", history = transactions)
    return apology("TODO")


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
        shareQuoted = {}
        shareQuoted = lookup(request.form.get("symbol"))
        if not shareQuoted:
            return apology("Not found. Type a valid symbol")
        return render_template("quoted.html", name=shareQuoted["name"], symbol=shareQuoted["symbol"], price=shareQuoted["price"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
     # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Typed password and password confirmation must be identical", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) >= 1:
            return apology("Username already exists", 400)

        newUser = db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        if newUser:
            # Redirect user to login form
            return redirect("/")

    else:
        return render_template("registration.html")

    return apology("Fatal error")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        soldShares = int(request.form.get("shares"))
        soldSymbol = request.form.get("symbol")
        if not soldSymbol:
            return apology("Please select a valid symbol")
        if not soldShares:
            return apology("Please enter a valid number of shares")

        available = db.execute("SELECT amount FROM holds WHERE user_id = ? AND symbol = ?", session["user_id"], soldSymbol)
        shareQuoted = lookup(soldSymbol)
        price = shareQuoted["price"]

        if available[0]["amount"] < soldShares:
            return apology("Not enough number of shares available to sell")
        amount = available[0]["amount"] - soldShares
        moneyGrab = soldShares * price
        print(moneyGrab)
        if available == 0:
            db.execute("DELETE FROM holds WHERE user_id = ? AND symbol = ?", session["user_id"], soldSymbol)
        else:
            db.execute("UPDATE holds SET amount = ? WHERE user_id = ? AND symbol = ?", amount, session["user_id"], soldSymbol)

        currentCash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        totalCash = currentCash[0]["cash"] + moneyGrab



        db.execute("UPDATE users SET cash = :updatedCash WHERE id = :userid", updatedCash = totalCash, userid = session["user_id"])

        db.execute("INSERT INTO transactions VALUES(?, ?, ?, ?, ?, DateTime('now'))", session["user_id"], shareQuoted["symbol"], "sell", soldShares, price)

        return redirect("/")

    else:
        symbols = db.execute("SELECT symbol FROM holds WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", symbolsInWallet = symbols)



@app.route("/passwordchange", methods=["GET", "POST"])
@login_required
def passwordchange():
    if request.method == "POST":
        if not request.form.get("password") or not request.form.get("newpassword") or not request.form.get("passwordCheck"):
            return apology("You must enter something in all password fields")

        if request.form.get("newpassword") != request.form.get("passwordCheck"):
            return apology("Typed new password and password confirmation must be identical", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(request.form.get("newpassword")), session["user_id"])
        return redirect("/")

    else:
        return render_template("passwordchange.html")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
