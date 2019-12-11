#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include "population.h"

int main(int argc, char *argv[]){
    if(argc != 4){
        std::cout << "./run graphSize populationSize epochs" << std::endl;
        exit(0);
    }
    int graphSize = atoi(argv[1]);
    int populationSize = atoi(argv[2]);
    int epochs = atoi(argv[3]);
    srand(time(NULL));
    Population p;
    p.start(graphSize, populationSize);
    std::vector <long long> parcialResults;
    for(int i = 0; i < epochs; i++){
        if(i%100 == 0){
            parcialResults.emplace_back(p.currentBest);
        }
        p.nextGeneration();
    }
    parcialResults.emplace_back(p.currentBest);
    std::cout << "Epochs, bestAnswer, Size" << std::endl;
    for(int i = 1; i < parcialResults.size(); i++){
        std::cout << (i * 100) << ", " << parcialResults[i] << ", " << graphSize << std::endl;
    }
    return 0;
}