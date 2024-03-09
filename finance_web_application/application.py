import os
import sqlite3

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, in_portfolio

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

# Global Variables
username = None


# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    global username
    stocks_dict = db.execute("SELECT stock, quantity FROM portfolio WHERE username = ?", username)
    carteira = db.execute("SELECT cash FROM users WHERE username = ?", username)
    carteira = carteira[0]["cash"]

    if not stocks_dict:
        return render_template("index.html", MENSAGEM="No Stocks yet", CARTEIRA=carteira)
    else:
        stocks = []
        for stock in stocks_dict:
            stocks.append(stock["stock"])
        quantities = []
        for quantity in stocks_dict:
            quantities.append(quantity["quantity"])
        prices = []
        try:
            for stock in stocks:
                prices.append(lookup(stock)["price"])
        except TypeError:
            pass

        return render_template("index_portfolio.html", STOCKS=stocks, QUANTITIES=quantities, PRICES=prices, CARTEIRA=carteira)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    global username
    if request.method == "POST":
        stock_quote = request.form.get("symbol")
        stock_quote = stock_quote.upper()
        try:
            quantity = int(request.form.get("quantity")) #
        except:
            return apology("Write quantity of stocks")
        try:
            stock_info = lookup(stock_quote)
        except:
            return apology("Stock does not exist")
        price = stock_info["price"]
        carteira = db.execute("SELECT cash FROM users WHERE username = ?", username)
        carteira = carteira[0]["cash"]


        if price * quantity > carteira:
            return apology("insufficient funds")

        else:
            db.execute("UPDATE users SET cash = ? WHERE username = ?", (carteira - quantity * price), username)
            db.execute("INSERT INTO transactions (stocks, quantity, price, operation, username) VALUES (?, ?,  ?,  'BUY', ?);", stock_quote, quantity, price, username) #
            portfolio = db.execute("SELECT stock FROM portfolio WHERE username = ?", username) #
            if in_portfolio(portfolio, stock_quote) == False:
                db.execute("INSERT INTO portfolio (stock, quantity, username) VALUES (?, ?, ?)", stock_quote, quantity, username) #
            else:
                try:
                    quantity_owned = db.execute("SELECT quantity FROM portfolio WHERE username = ? AND stock = ?", username, stock_quote)
                    quantity_own = quantity_owned[0]["quantity"]
                    db.execute("UPDATE portfolio SET quantity = ? WHERE username = ? AND stock = ?", (quantity_own + quantity), username, stock_quote)
                except IndexError:
                    return render_template("index.html", MENSAGEM=portfolio , CARTEIRA=carteira)
            return redirect("/")

    else:

        cash = db.execute("SELECT cash FROM users WHERE username = ?", username)
        carteira = cash[0]["cash"]

        return render_template("buy.html", CARTEIRA=carteira)



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    global username
    cash = db.execute("SELECT cash FROM users WHERE username = ?", username)
    carteira = cash[0]["cash"]
    transactions = db.execute("SELECT * FROM transactions WHERE username = ?", username)
    if not transactions:
        return(render_template("transactions.html", MESSAGE="You have no transactions yet", CARTEIRA=carteira))
    else:
        return(render_template("transactions.html", TRANSACTIONS=transactions, CARTEIRA=carteira))



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
        global username
        username = request.form.get("username")


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
        if not request.form.get("symbol"):
            return apology("Must input Symbol")
        else:
            symbol = request.form.get("symbol")
            result = lookup(symbol)
            if not result:
                return apology("Quote Symbol Invalid")
            else:
                return render_template("quoted.html", **result)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        if not request.form.get("username") or not request.form.get("password"):
            return apology("Must be username and password")


        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirm_password")

        if password != confirm_password:
            return apology("Passwords do not match")
        else:
            hashed_password = generate_password_hash(password)



    # Acessar a base de dados
        users = db.execute("SELECT username FROM users WHERE username = ?", username)


    # Checar se Usuário já existe e registrar usuário
        if len(users) != 1:
            db.execute("INSERT INTO users (username, hash) VALUES (:USER, :PASSWORD);", USER=username, PASSWORD=hashed_password)
            return redirect("/")
        else:
            return apology("Username already exists")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    global username
    if request.method == "POST":
        stock_quote = request.form.get("symbol")
        stock_quote = stock_quote.upper()
        try:
            quantity = int(request.form.get("quantity"))
        except:
            return apology("Write quantity of stocks")
        try:
            stock_info = lookup(stock_quote)
        except:
            return apology("Stock does not exist")
        price = stock_info["price"]
        carteira = db.execute("SELECT cash FROM users WHERE username = ?", username)
        carteira = carteira[0]["cash"]

        quantity_owned = db.execute("SELECT quantity FROM portfolio WHERE username = ? AND stock = ?", username, stock_quote)
        if quantity_owned:
            quantity_own = int(quantity_owned[0]["quantity"])
        else:
            return apology("You do not have the stocks to sell")

        # Check if quantity of stocks selected are in Portfolio database
        if quantity > quantity_own:
            return apology("You do not have the stocks to make this transaction")

        else:
            db.execute("UPDATE users SET cash = ? WHERE username = ?", (carteira + quantity * price), username)
            db.execute("INSERT INTO transactions (stocks, quantity, price, operation, username) VALUES (?, ?,  ?,  'SELL', ?);", stock_quote, quantity, price, username)

            db.execute("UPDATE portfolio SET quantity = ? WHERE username = ? AND stock = ?", (quantity_own - quantity), username, stock_quote)

            return redirect("/")

    else:

        cash = db.execute("SELECT cash FROM users WHERE username = ?", username)
        carteira = cash[0]["cash"]

        return render_template("sell.html", CARTEIRA=carteira)


    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
