#include<vector>

using namespace std;

#define TAMPOP 100
#define TAXMUT 0.2

typedef vector<unsigned char> dataType;

void iniPop(long unsigned int size);
void avaliaPop(dataType img);
void printPop(dataType v);
dataType elitismo(int size);