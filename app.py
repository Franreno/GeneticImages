import matplotlib.pyplot as plt
import numpy as np
import os
import argparse

outputPath = "./Graficos/"


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
    mean = []

    for element in file:
        element = element.split(',')
        generations.append(int(element[0]))
        fit.append(float(element[1]))
        mean.append(float(element[2]))

    return generations, fit, mean


def plotSimplesComMedia(g, f, m, name):
    fig, ax = plt.subplots()
    fig.set_figheight(8)
    fig.set_figwidth(20)

    ax.plot(g, f, color='b', label="Fitness")
    ax.plot(g, m, color='orange', label="Mean")
    ax.legend()
    ax.set_title(name + " with mean")
    ax.set_xlabel("Generations")
    ax.set_ylabel("Fitness")
    plt.savefig(outputPath + name + '_WithMean.png')


def plotSimplesSemMedia(g, f, name):
    fig, ax = plt.subplots()
    fig.set_figheight(8)
    fig.set_figwidth(20)

    ax.plot(g, f, color='b', label="Fitness")
    ax.legend()
    ax.set_title(name)
    ax.set_xlabel("Generations")
    ax.set_ylabel("Fitness")
    plt.savefig(outputPath + name + '.png')


def plotConjuntoTotal(g, f, names, save_name):
    fig, ax = plt.subplots()
    fig.set_figheight(8)
    fig.set_figwidth(20)

    for gen, fit, name in zip(g, f, names):

        ax.plot(gen, fit, label=name)
        ax.legend()
        ax.set_xlabel("Generations")
        ax.set_ylabel("Fitness")

    plt.savefig(outputPath + save_name + '.png')


def main(content: list, fpath: str):

    content = [e for e in content if not e.endswith(".png")]

    allGen = []
    allFit = []
    allName = []

    eli_Gen = []
    eli_Fit = []
    eli_names = []

    tor_Gen = []
    tor_Fit = []
    tor_names = []

    for filename in content:

        generations, fit, mean = parseFile(fpath + filename)
        name = filename.replace(".txt", "")
        if(name.startswith("eli")):
            eli_Gen.append(generations)
            eli_Fit.append(fit)
            eli_names.append(name)
        else:
            tor_Gen.append(generations)
            tor_Fit.append(fit)
            tor_names.append(name)

        allGen.append(generations)
        allFit.append(fit)
        allName.append(filename.replace(".txt", ""))

        plotSimplesComMedia(generations, fit, mean, name)
        plotSimplesSemMedia(generations, fit, name)

    plotConjuntoTotal(allGen, allFit, allName, "Todas")
    plotConjuntoTotal(eli_Gen, eli_Fit, eli_names, "SoElitismo")
    plotConjuntoTotal(tor_Gen, tor_Fit, tor_names, "soTorneio")

    # fig = plt.figure(constrained_layout=True)
    # rows = 0
    # if(len(content) % 2 == 0):
    #     rows = int(len(content)/2)
    # else:
    #     rows = int(int(len(content) / 2) + 1)

    # ax = fig.subplots(rows, 2)

    # counter = 0
    # for i in range(rows):
    #     for j in range(2):
    #         generations, fit = parseFile(fpath+content[counter])
    #         ax[i,j].plot(generations, fit)
    #         ax[i,j].set_title(content[counter].replace(".txt", ""))

    #         counter+=1
    #         if(counter >= len(content)):
    #             break

    # plt.plot(generations, fit, color='b')
    # plt.plot(generations, mean, color='orange')
    # plt.title(content[0].replace(".txt", ""))
    # plt.xlabel("Geracao")
    # plt.ylabel("Fitness")
    # plt.show()
if '__main__' == __name__:
    path = "./data/"

    main(os.listdir(path), path)

    pass
