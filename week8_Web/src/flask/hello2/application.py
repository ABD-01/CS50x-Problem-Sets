from flask import Flask, render_template

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html", name="Emma")

@app.route("/goodbye")
def bye():
    return "Goodbye!"
