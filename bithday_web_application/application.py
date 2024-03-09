import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database

        name = request.form.get("name")
        month = str(request.form.get("month"))
        day = str(request.form.get("day"))

        try:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        except:
            pass

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT name, month, day FROM birthdays")

        return render_template("index.html", BIRTHDAYS=birthdays)



@app.route("/erase", methods=["GET", "POST"])
def erase():
    if request.method == "POST":

        erase = request.form.get("name_erase")
        try:
            db.execute("DELETE FROM birthdays WHERE name = ?", erase)
        except:
            pass

        return redirect("/")

    else:
        return render_template("erase.html")

