#include "individual.h"

Individual::Individual(){
}

Individual::Individual(std::vector<int> param){
    chromosome = param;
}

void Individual::mutate(){
    int pos1 = rand() % chromosome.size();
    int pos2 = rand() % chromosome.size();
    std::swap(chromosome[pos1], chromosome[pos2]);
}

bool Individual::isValid(int tam){
    std::vector <int> freq(chromosome.size(), 0);
    for(int i = 0; i < chromosome.size(); i++){
        freq[chromosome[i]]++;
        if(freq[chromosome[i]] > 1)return false;    
    }
    return tam == chromosome.size();
}