#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ag.hpp"

using namespace std;

int main(){
    FILE *fd = fopen("image.pgm", "rb");

    fseek(fd, 0, SEEK_END);
    long fileSize = ftell(fd);
    
    //Pula cabecalho
    fseek(fd, 38, SEEK_SET);

    vector<unsigned char> img;
    unsigned char byte;
    while(ftell(fd) != fileSize) {
        fread(&byte, sizeof(unsigned char), 1, fd);
        img.push_back(byte);
    }  

    iniPop(img.size());

    do{
        avaliaPop(img);
        elitismo(img.size());
    } while (1);

    fclose(fd);
    return 0;
}