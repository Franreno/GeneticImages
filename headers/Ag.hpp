#include <cstdlib>
#include <vector>
#include <random>
#include <cmath>
#include <iostream>

using namespace std;

#ifndef _AG_
#define _AG_

#define POPSIZE 100

#define MUTATION_RATE 0.02
#define MUTATION_RATE_VAR 2
#define NUM_TOURNAMENT 20

typedef vector<unsigned char> dataType;

class Ag {
    private:
        dataType imgMap;

        vector <dataType> pop;
        vector <int> fitness;
        int countWithouMutation;
        float mutationRate;
        int generation;

        //Melhor de todos
        int bestIndex;
        int bestScore;
        dataType best;

        float avg;

        random_device randomGenerator;
        uniform_int_distribution <unsigned short> genesDistribution;
        uniform_int_distribution <int> genesIndexDistribution;
        exponential_distribution <float> mutationDistribution;
    public:
        Ag(dataType imgMap);
        void buildRandomPop(int beginIndex);
        void initialize();
        void evaluatePop();
        void evaluateElem(int index);
        void findBestElem();

        void elitism();
        void tournament();
        int tournamentSelection();

        void crossover(int, int, int);
        void mutation(int index);
        void defineMutationRate();
        void genocide();   
        void syntheticPredation();
        void randomPredation();

        void print();
        dataType getBest();
};

#endif