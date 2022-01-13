#include<vector>

using namespace std;

#define TAMPOP 1000
#define TAXMUT 0.02
#define NUM_IND_TORNEIO 20

typedef vector<unsigned char> dataType;

void iniPop(long unsigned int size);
void avaliaPop(dataType img);
dataType elitismo(int size);
dataType torneio(int size, dataType img);
void printPop(dataType v);