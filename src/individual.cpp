#include "individual.h"

Individual::Individual(){
}

Individual::Individual(std::vector<int> param){
    sequence = param;
}

void Individual::mutate(){
    int pos1 = rand() % sequence.size();
    int pos2 = rand() % sequence.size();
    std::swap(sequence[pos1], sequence[pos2]);
}

bool Individual::isValid(int tam){
    std::vector <int> freq(sequence.size(), 0);
    for(int i = 0; i < sequence.size(); i++){
        freq[sequence[i]]++;
        if(freq[sequence[i]] > 1)return false;    
    }
    return tam == sequence.size();
}