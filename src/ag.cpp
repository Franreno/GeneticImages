#include <cstdlib>
#include <cmath>
#include <vector>
#include <random>
#include <iostream>

#include "ag.hpp"

/**
 * Variaveis Globais
 */
vector<dataType> pop;
vector<int> fit;
dataType best;
int bestScore;
int gen;

uniform_int_distribution<unsigned short> distribution(0, 255);
random_device randomGenerator;

void iniPop(long unsigned int size)
{
    for (int i = 0; i < TAMPOP; i++)
    {
        dataType v;
        for (long unsigned int j = 0; j < size; j++)
        {
            v.push_back((unsigned char)distribution(randomGenerator));
        }
        pop.push_back(v);
    }
    gen = 1;
}

void printPop(dataType v)
{
    for (auto byte : v)
    {
        cout << (unsigned int)byte << " ";
    }
    cout << endl << endl << endl;
}

void avaliaPop(dataType img)
{
    dataType x;

    for (int i = 0; i < TAMPOP; i++)
    {
        fit.push_back(0);
        x = pop[i];
        for (long unsigned int j = 0; j < img.size(); j++)
        {
            if (x[j] == img[j])
            {
                fit[i]++;
            }
        }

        fit[i] = 1000*fit[i] / 256;
        fit[i] = fit[i]*fit[i] / 1000;
    }

}

dataType elitismo(int size)
{
    int maxi = 0;
    bestScore = fit[0];

    //selecao
    for (int i = 1; i < TAMPOP; i++)
    {
        if (fit[i] > bestScore)
        {
            bestScore = fit[i];
            maxi = i;
        }
    }

    best = pop[maxi];

    for (int i = 0; i < TAMPOP; i++)
    {
        if (i == maxi)
            continue;

        //crossover
        for (int j = 0; j < size; j++)
        {
            pop[i][j] = (pop[i][j] + pop[maxi][j]) / 2;
        }

        //mutacao
        unsigned char mut = 255 * TAXMUT;
        unsigned char cromossomo = (unsigned char)distribution(randomGenerator);

        if ((unsigned char)distribution(randomGenerator) % 2 == 0)
        {
            pop[i][(int)cromossomo] += mut;
            if (pop[i][(int)cromossomo] > 255)
                pop[i][(int)cromossomo] = 255;
        }
        else
        {
            pop[i][(int)cromossomo] -= mut;
            if (pop[i][(int)cromossomo] < 0)
                pop[i][(int)cromossomo] = 0;
        }
    }
    gen++;

    printPop(best);

    return best;
}