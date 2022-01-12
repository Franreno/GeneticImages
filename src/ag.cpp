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
int countNoMutation;
float taxMut;

uniform_int_distribution<unsigned short> distribution(0, 255);
random_device randomGenerator;

void iniPop(long unsigned int size)
{
    countNoMutation = 0;
    taxMut = TAXMUT;
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

void printPop(dataType v, int maxi)
{
    // for(auto byte: v){
    //     cout << (unsigned int) byte << endl;
    // }

    cout << gen << ", " << fit[maxi] << ", " << endl;
}

void avaliaPop(dataType img)
{
    dataType x;

    for (int i = 0; i < TAMPOP; i++)
    {
        fit.push_back(0);
        x = pop[i];
        fit[i] = 0;
        for (long unsigned int j = 0; j < img.size(); j++)
        {
            if (x[j] == img[j])
            {
                fit[i]++;
            }
        }
    }
}

void genocidio(int size, dataType img)
{
    pop.clear();
    pop.push_back(best);
    fit[0] = bestScore;

    for (int i = 1; i < TAMPOP; i++)
    {
        dataType v;
        for (int j = 0; j < size; j++)
        {
            v.push_back((unsigned char)distribution(randomGenerator));
        }
        pop.push_back(v);
    }

    avaliaPop(img);
}

void predacaoSintetica(int mini, int size, dataType img)
{
    fit[mini] = 0;

    dataType v;
    for (int j = 0; j < size; j++)
    {
        pop[mini][j] = 0;
        for (int i = 0; i < TAMPOP; i++)
        {
            pop[mini][j] += pop[i][j];
        }
        pop[mini][j] = (int)pop[mini][j] / TAMPOP;
    }

    for (long unsigned int j = 0; j < img.size(); j++)
    {
        if (pop[mini][j] == img[j])
        {
            fit[mini]++;
        }
    }
}

void predacaoRandomica(int mini, int size, dataType img)
{
    fit[mini] = 0;

    dataType v;
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < TAMPOP; i++)
        {
            pop[mini][j] = (unsigned char)distribution(randomGenerator);
        }
    }

    for (long unsigned int j = 0; j < img.size(); j++)
    {
        if (pop[mini][j] == img[j])
        {
            fit[mini]++;
        }
    }
}

dataType torneio(int size, dataType img)
{
    int maxi = 0, mini = 0;
    int prevBestScore = bestScore;

    bestScore = fit[0];

    int worstScore = fit[0];

    vector<dataType> backup;

    //selecao
    for (int i = 0; i < TAMPOP; i++)
    {
        backup.push_back(pop[i]);

        if (fit[i] > bestScore)
        {
            bestScore = fit[i];
            maxi = i;
        }
        else if (fit[i] < worstScore)
        {
            mini = i;
            worstScore = fit[i];
        }
    }

    best = pop[maxi];

    if (prevBestScore == bestScore)
    {
        countNoMutation++;

        switch (countNoMutation)
        {
        case 10:
        case 20:
            taxMut /= 2;
            break;
        case 30:
            taxMut *= 4;
            break;
        case 40:
        case 50:
        case 60:
        case 70:
        case 80:
        case 90:
            taxMut *= 2;
            break;
        case 500:
            countNoMutation = 0;
            taxMut = TAXMUT;
            genocidio(size, img);
            maxi = 0;
        }
    }
    else
    {
        countNoMutation = 0;
    }

    //torneio
    for (int i = 0; i < TAMPOP; i++)
    {
        if (i == maxi)
            continue;

        int a = distribution(randomGenerator) % TAMPOP;
        int b = distribution(randomGenerator) % TAMPOP;
        ;
        for (int j = 0; j < NUM_IND_TORNEIO - 2; j++)
        {
            if (fit[b] > fit[a])
            {
                a = b;
            }
            b = distribution(randomGenerator) % TAMPOP;
        }

        int c = distribution(randomGenerator) % TAMPOP;
        int d = distribution(randomGenerator) % TAMPOP;
        ;
        for (int j = 0; j < NUM_IND_TORNEIO - 2; j++)
        {
            if (fit[d] > fit[c])
            {
                c = d;
            }
            d = distribution(randomGenerator) % TAMPOP;
        }

        //crossover
        for (int j = 0; j < size; j++)
        {
            pop[i][j] = (pop[a][j] + pop[c][j]) / 2;
        }

        //mutacao
        unsigned char mut = 255 * taxMut;

        for (int j = 0; j < 1; j++)
        {
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
    }

    gen++;

    printPop(best, maxi);
    return best;
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

    printPop(best, maxi);
    return best;
}