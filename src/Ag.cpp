#include "Ag.hpp"

Ag::Ag(dataType imgMap){
    this->imgMap = imgMap;
    this->bestIndex = -1;
    this->mutationRate = MUTATION_RATE;
    this->countWithouMutation = 0;
    this->bestScore = 0;


    uniform_int_distribution<unsigned short> dist1(0, 255);
    this->genesDistribution = dist1;

    exponential_distribution<float> dist2(3.5);
    this->mutationDistribution = dist2;

    uniform_int_distribution<int> dist3(0, imgMap.size() - 1);
    genesIndexDistribution = dist3;
}

/**
 * Constroi uma populacao randomica partindo do indice beginIndex
 */
void Ag::buildRandomPop(int beginIndex){
    
    /**
     * Constroi uma populacao aleatoria
     */
    for (int i = beginIndex; i < POPSIZE; i++){
        /**
         * Preenche um vector com dados aleatorios
         */
        dataType v;
        for (long unsigned int j = 0; j < imgMap.size(); j++){
            v.push_back((unsigned char) genesDistribution(randomGenerator));
        }

        //Inicializa o vector com fitness
        fitness.push_back(0);

        //adiciona na populacao
        pop.push_back(v);
    }
}

/**
 * Inicializa a populacao e algoritmos padrao
 */
void Ag::initialize(){
    //inicializa a geracao como 1
    generation = 1;

    /**
     * Constroi a populacao inicial
     */
    buildRandomPop(0);
}

/**
 * Avalia um elemento da populacao, de indica dado por parametro
 */
void Ag::evaluateElem(int index){
    fitness[index] = 0;
    
    /**
     * Percorre cada caracter da imagem e do elemento da populacao
     */
    for (long unsigned int j = 0; j < imgMap.size(); j++){
        // Verifica se o caracter atual da imagem eh igual ao do elemento analisado
        if (pop[index][j] == imgMap[j]){
            //Se sim, incrementa um
            fitness[index]++;
        }
    }
}

/**
 * Atribui uma nota (fitness) para a populacao.
 * A funcao retorna a quantidade de caracteres semelhantes entre a imagem e cada elemento da populacao
 */
void Ag::evaluatePop(){
    /**
     * Percorre a populacao
     */
    for (int i = 0; i < POPSIZE; i++){
        //Evita avaliar o melhor de todos novamente
        if(i == bestIndex) 
            continue;

        //Analisa o elemento em questao
        evaluateElem(i);
    }
}

void Ag::findBestElem(){
    /**
     * Encontra o melhor individuo
     */
    bestIndex = 0;
    bestScore = fitness[0];
    this->avg = bestScore;

    for(long unsigned int i = 1; i < fitness.size(); i++){
        if (fitness[i] > bestScore){
            bestScore = fitness[i];
            bestIndex = i;
        }
        this->avg += fitness[i];
    }

    //Calcula a media da populacao
    this->avg /= POPSIZE;
    //Armazena o melhor de todos.
    best = pop[bestIndex];
}

/**
 * Realiza o crossover entre dois elementos da populacao
 * "result" indica onde o crossover entre "elem1" e "elem2" dele ser armazenado
 */
void Ag::crossover(int result, int elem1, int elem2){
    /**
     * Percorre os dados dos elementos e realiza o crossover
     */
    for (long unsigned int i = 0; i < imgMap.size(); i++){
        pop[result][i] = (unsigned char) ((pop[elem1][i] + pop[elem2][i]) / 2);
    }
}


/**
 * Realiza a selecao por torneio
 */
int Ag::tournamentSelection(){
    //Gera um indice aleatorio
    int a = genesIndexDistribution(randomGenerator) % POPSIZE;

    /**
     * Realiza NUM_TOURNAMENT selecoes
     */
    for (int j = 0; j <= NUM_TOURNAMENT - 2; j++){
        //Gera um indice aleatorio
        int b = genesIndexDistribution(randomGenerator) % POPSIZE;
        
        //Verifica qual o melhor
        if (fitness[b] > fitness[a]){
            a = b;
        }
    }

    //retorna o indice do melhor
    return a;
}

/**
 * Realiza selecao por meio do Torneio
 */
void Ag::tournament(){
    int oldBestScore = bestScore;

    //Encontra o melhor individuo
    findBestElem();

    if (oldBestScore == bestScore){
        countWithouMutation++;

        //Define a taxa de mutacao
        defineMutationRate();
    } else {
        countWithouMutation = 0;
    }

    for (int i = 0; i < POPSIZE; i++){
        if(bestIndex == i){
            continue;
        }

        /**
         * Seleciona 2 individuos para realizar o crossover
         */
        int elem1 = tournamentSelection();
        int elem2 = tournamentSelection();

        //Realiza crossover.
        crossover(i, elem1, elem2);
        
        //Realiza mutacao
        mutation(i);
    }

    generation++;
}

/**
 * Executa o metodo de selecao de Elitismo
 */
void Ag::elitism(){
    //Encontra o melhor individuo
    findBestElem();

    for (int i = 0; i < POPSIZE; i++){
        if(bestIndex == i){
            continue;
        }

        //Realiza crossover.
        crossover(i, i, bestIndex);
        
        //Realiza mutacao
        mutation(i);
    }

    generation++;
}


/**
 * Realiza a mutacao de um individuo
 */
void Ag::mutation(int index){
    
    //Calcula a taxa de mutacao
    unsigned char mut = 255 * mutationRate;
    
    //Calcula a quantidade de mutacoes que irao ocorrer
    //int quantity = ceil(mutationDistribution(randomGenerator) * 3);
    int quantity = 1;
    //cout << quantity << endl;

    /**
     * Realiza a quantidade de mutacoes
     */
    for (int j = 0; j < quantity; j++){
        //Calcula o cromossomo que sera modificado
        int cromossomo = genesIndexDistribution(randomGenerator);
        
        //Calcula se deve ser somado ou subtraido do gene
        if (genesDistribution(randomGenerator) % 2 == 0){
            //Realiza a mutacao
            pop[index][cromossomo] += mut;

            //Verifica se esta no limite permitido. Senao, conserta.
            if (pop[index][cromossomo] > 255) 
                pop[index][cromossomo] = 255;
        }
        else{
            //Realiza a mutacao
            pop[index][cromossomo] -= mut;

            //Verifica se esta no limite permitido. Senao, conserta.
            if (pop[index][cromossomo] < 0) 
                pop[index][cromossomo] = 0;
        }
    }
}


/**
 * Executa genocidio na populacao
 */
void Ag::genocide(){
    //Limpa da memoria a populacao
    pop.clear();
    fitness.clear();

    //Insere na populacao o melhor de todos
    pop.push_back(best);

    //Insere o fitness do melhor de todos
    fitness.push_back(bestScore);

    //Modifica o indice do melhor de todos
    bestIndex = 0;

    //Constroi uma populacao aleatoria partindo da posicao 1 do array
    buildRandomPop(1);

    //Avalia a populacao criada
    evaluatePop();
}


/**
 * Predacao Sintetica
 */
void Ag::syntheticPredation(){
    
    /**
     * Encontra o pior elemento da populacao
     */
    int mini = 0;
    for(int i = 1; i < POPSIZE; i++){
        if(fitness[i] > mini){
            mini = i;
        }
    }

    //Define o fitness como zero
    fitness[mini] = 0;

    //Para cada posicao do pior, calcula o gene sintetico
    for (long unsigned int j = 0; j < imgMap.size(); j++){
        pop[mini][j] = 0;

        /**
         * Soma o gene de todos os elementos da populacao
         */
        for (int i = 0; i < POPSIZE; i++){
            pop[mini][j] += pop[i][j];
        }

        //Calcula a media
        pop[mini][j] = (int) pop[mini][j] / POPSIZE;
    }

    //Calcula o fitness para o pior
    evaluateElem(mini);
}


/**
 * Predacao Sintetica
 */
void Ag::randomPredation(){
    
    /**
     * Encontra o pior elemento da populacao
     */
    int mini = 0;
    for(int i = 1; i < POPSIZE; i++){
        if(fitness[i] > mini){
            mini = i;
        }
    }

    //Define o fitness como zero
    fitness[mini] = 0;

    /**
     * Gera um novo individuo aleatorio
     */
    for (long unsigned int j = 0; j < imgMap.size(); j++){
        pop[mini][j] = (unsigned char) genesDistribution(randomGenerator);
    }

    //Calcula o fitness para o pior
    evaluateElem(mini);
}


void Ag::defineMutationRate(){
    if(countWithouMutation % 10 != 0){
        return;
    }

    /**
     * Para cada faixa de inatividade no melhor de todos, estabelece uma taxa
     * de mutacao diferente, ate que executa genocidio.
     */
    if(countWithouMutation == 10 || countWithouMutation == 20){
        mutationRate /= MUTATION_RATE_VAR;
    } else if(countWithouMutation == 30){
        mutationRate *= MUTATION_RATE_VAR * MUTATION_RATE_VAR;
    } else if(countWithouMutation >= 40 && countWithouMutation <= 90){
        mutationRate *= MUTATION_RATE_VAR;
    } else if(countWithouMutation == 500){
        countWithouMutation = 0;
        mutationRate = MUTATION_RATE;
        cout << "OLAAAAAAAA" << endl;
        genocide();
    }
    
}

dataType Ag::getBest(){
    return best;
}

void Ag::print(){
    cout << generation << ", " << bestScore << ", " << this->avg << endl;
}