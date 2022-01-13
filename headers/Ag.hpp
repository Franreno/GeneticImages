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
#define ACCEPTANCE 0.2
#define PREDATION_USES 6
#define LIMIT_GEN 20000

typedef vector<unsigned char> dataType;

class Ag {
    private:
        dataType imgMap;

        vector <dataType> pop;
        vector <float> fitness;
        int countWithouMutation;
        float mutationRate;
        int generation;

        //Melhor de todos
        int bestIndex;
        float bestScore;
        dataType best;

        float avg;
        float acceptance;
        int bit;

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
        void defineMutationRate(int);
        void genocide();   
        void syntheticPredation();
        void randomPredation();

        void print();
        dataType getBest();
        int getGeneration();
};

#endif