import matplotlib.pyplot as plt
import numpy as np
import os
import argparse


def readfile(filename):
    buffer = None
    with open(filename, 'r') as f:
        buffer = f.read()

    buffer = buffer.split('\n')

    buffer.pop(-1)

    return buffer


def parseFile(filename: str):
    file = readfile(filename)
    generations = []
    fit = []

    for element in file:
        element = element.split(',')
        generations.append(int(element[0]))
        fit.append(int(element[1]))

    return generations, fit


def main(content: list, fpath: str):
    fig = plt.figure(constrained_layout=True)
    rows = 0
    if(len(content) % 2 == 0):
        rows = int(len(content)/2)
    else:
        rows = int(int(len(content) / 2) + 1)

    ax = fig.subplots(rows, 2)

    counter = 0
    for i in range(rows):
        for j in range(2):
            generations, fit = parseFile(fpath+content[counter])
            ax[i,j].plot(generations, fit)
            ax[i,j].set_title(content[counter].replace(".txt", ""))

            counter+=1
            if(counter >= len(content)):
                break
            


    # plt.plot(generations, fit)
    # plt.title(filename.replace(".txt", ""))
    # plt.xlabel("Geracao")
    # plt.ylabel("Fitness")
    plt.show()
if '__main__' == __name__:
    path = "./data/"

    main(os.listdir(path), path)

    pass
