import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for
from tempfile import mkdtemp
from datetime import datetime

import matplotlib.pyplot as plt
import random
import io
import time
import copy
import requests
import numpy as np
import pandas as pd

from flask import Response
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure

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


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///generacion.db")

@app.route("/", methods=["GET", "POST"])
def modts():

    if request.method == "POST":
        if request.form['submit_button'] == 'gene':
            return render_template("index.html")
        else:
            db.execute("UPDATE gen SET gen = 1;")
            return render_template("index.html")
    else:
        return render_template("index.html")

@app.route('/plot.png')
def plot_png():
    fig = create_figure()
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    return Response(output.getvalue(), mimetype='image/png')

def str_to_list(ls):
    ls = ls[1:-1]
    return([int(s) for s in ls.split(',')])

def game_of_life(a,b):

    # Remover duplicados
    df = pd.DataFrame({"a":a,
      "b":b})
    df = df.drop_duplicates()
    a = df["a"].tolist()
    b = df["b"].tolist()

    m2 = [[False for j in range(101) ] for i in range(101)]
    m_aux = copy.deepcopy(m2)

    for i in range(len(a)):
        # print(str(a[i]) + " " + str(b[i]))
        m2[a[i]][b[i]] = True

    coords_i = []
    coords_j = []

    nlim = 100
    for i in range(len(a)):
        for j in range(len(a)):
            # Valoración
            # print(j+1)
            # print("Len j" + str(len(m2[i])) + " " + str(len(a)))

            i_1 = int((i+1)%(nlim))
            j_1 = int((j+1)%(nlim))

            i = int((i)%(nlim))
            j = int((j)%(nlim))

            vivos = [m2[i-1][j-1] == True, m2[i][j-1] == True, m2[i_1][j-1] == True,
                m2[i-1][j] == True, m2[i_1][j] == True,
                m2[i-1][j_1] == True, m2[i][j_1] == True, m2[i_1][j_1] == True]
            # print(vivos)
              #Si est{a viva y tiene dos o tres vecinas vivas, sigue viva
            if(m2[i][j] == True and sum(vivos) in [2,3]):
                m_aux[i][j] = True
                coords_i.append(i)
                coords_j.append(j)
            elif(m2[i][j] == False and sum(vivos) == 3):
                #Si tiene exactamente 3 vecinas vivas revive
                m_aux[i][j] = True
                coords_i.append(i)
                coords_j.append(j)
            else:
              #Otro caso muere
              m_aux[i][j] = False

    return(coords_i, coords_j)


def create_figure():

    db_gen = db.execute("SELECT gen FROM gen;")
    last_gen = db_gen[0]['gen']

    if(last_gen == 1):
        xs = list(range(100))
        den = db.execute("SELECT den FROM gen;")[0]['den']

        xs = list(np.repeat(xs, den))
        ys = [random.randint(1, 100) for x in xs]
        db.execute("UPDATE gen SET aux1 = :xs", xs = str((xs)))
        db.execute("UPDATE gen SET aux2 = :ys", ys = str(ys))
    else:
        xs = str_to_list(db.execute("SELECT aux1 FROM gen;")[0]['aux1'])
        ys = str_to_list(db.execute("SELECT aux2 FROM gen;")[0]['aux2'])
        #Mostrar la siguiente iteración
        xs, ys = game_of_life(xs, ys)
        if len(xs) != 0:
            db.execute("UPDATE gen SET aux1 = :xs", xs = str(list(xs)))
            db.execute("UPDATE gen SET aux2 = :ys", ys = str(ys))

    fig = Figure()
    axis = fig.add_subplot(1, 1, 1)

    axis.set_xlim(0, 101)
    axis.set_ylim(0, 101)
    axis.get_xaxis().set_visible(False)
    axis.get_yaxis().set_visible(False)
    axis.scatter(xs, ys, marker = "s")
    db.execute("UPDATE gen SET gen = gen + 1")

    return fig


@app.route('/suggestions')
def suggestions():
    text = request.args.get('jsdata')
    db_gen = db.execute("SELECT gen FROM gen;")
    last_gen = db_gen[0]['gen']
    suggestions_list = [last_gen]

    return render_template('suggestions.html', suggestions=suggestions_list)

@app.route('/rules')
def rules():
    return render_template('rules.html')

@app.route('/index_2', methods=["GET", "POST"])
def index_2():
    if request.method == "POST":

        den = int(request.form.get("density"))
        db.execute("UPDATE gen SET den = :den;",den = den)

        if request.form['submit_button_2'] == 'reset2':

            db.execute("UPDATE gen SET gen = 1;")
            return render_template("index_2.html")
        else:
            return render_template("index_2.html")
    else:
        return render_template('index_2.html')


