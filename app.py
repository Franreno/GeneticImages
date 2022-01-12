import matplotlib.pyplot as plt
import numpy as np
import argparse


def readfile(filename):
    buffer = None
    with open(filename, 'r') as f:
        buffer = f.read()

    buffer = buffer.split('\n')

    buffer.pop(-1)

    return buffer


def main(filename: str):
    file = readfile(filename)
    generations = []
    fit = []

    for index, element in enumerate(file):
        element = element.split(',')
        generations.append(int(element[0]))
        fit.append(int(element[1]))

    plt.plot(generations, fit)
    plt.title(filename.replace(".txt", ""))
    plt.xlabel("Geracao")
    plt.ylabel("Fitness")
    plt.show()


if '__main__' == __name__:
    ap = argparse.ArgumentParser()
    ap.add_argument("-f", "--file", required=True,
                    help="Text Source for histogram")
    args = vars(ap.parse_args())

    main(args["file"])

    pass
