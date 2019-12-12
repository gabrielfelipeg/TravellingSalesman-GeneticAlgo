#include "population.h"

Population::Population(){resetStatus = true; currentBest = 1e18;}

void Population::reset(){
    if(!resetStatus){
        population.clear();
        weight.clear();
    }
    resetStatus = true;
    currentBest = 1e18;
}

void Population::start(int k, int size){
    if(!resetStatus)reset();
    resetStatus = false;
    tam = k;
    for(int i = 0; i < size; i++){
        std::vector<int> aux;
        for(int j = 0; j < k; j++){
            aux.emplace_back(j);
        }
        std::random_shuffle(aux.begin(), aux.end());
        population.emplace_back(Individual(aux));
        weight.emplace_back(std::vector<long long>(k, 0));
    }
    for(int i = 0; i < k; i++){
        for(int j = i + 1; j < k; j++){
            weight[i][j] = (rand() % 100000) + 122;
            weight[j][i] = weight[i][j];
        }
    }
}

long long Population::F(int x){
    long long ret = 0;
    for(int i = 0; i < population[x].chromosome.size() - 1; i++){
        int u = population[x].chromosome[i];
        int v = population[x].chromosome[i + 1];
        ret += weight[u][v];
    }
    return ret;
}

bool Population::comparator(std::pair<long long, Individual> a, std::pair<long long, Individual> b){
    return a.first < b.first;
}

void Population::select(){
    int elitism = population.size() * 0.1;
    std::vector <Individual> newPop;
    std::vector < std::pair<long long, Individual> > aux;
    for(int i = 0; i < population.size(); i++){
        aux.emplace_back(F(i), population[i]);
    }
    sort(aux.begin(), aux.end(), comparator);
    currentBest = std::min(currentBest, aux[0].first);
    for(int i = 0; i < elitism; i++){
        newPop.emplace_back(aux[i].second);    
    }
    int needed = ((int)population.size() / 2) - (int)newPop.size();
    std::vector <Individual> secondChance;
    for(int i = elitism; i < population.size() && needed; i++){
        double chance = (population.size() - i + elitism * 1.0) / ((double)population.size() * population.size() * 1.0 - population.size());
        double random = ((double)rand()) / RAND_MAX;
        if(chance >= random){
            newPop.emplace_back(aux[i].second);
            needed--;
        }else{
            secondChance.emplace_back(aux[i].second);
        }
    }
    int ind = 0;
    std::random_shuffle(secondChance.begin(), secondChance.end());
    while(needed > 0){
        needed--;
        newPop.emplace_back(secondChance[ind++]);
    }
    secondChance.clear();
    aux.clear();
    population.clear();
    population = newPop;
}

std::pair < Individual, Individual > Population::crossingOver(Individual &a, Individual &b){
    int left = rand()%a.chromosome.size();
    int right = std::min(left + (a.chromosome.size() / 3), a.chromosome.size() - 1);
    std::vector <int> freq1(a.chromosome.size(), 0);
    std::vector <int> freq2(a.chromosome.size(), 0);
    Individual ret1(std::vector<int>(a.chromosome.size(), -1));
    Individual ret2(std::vector<int>(a.chromosome.size(), -1));

    for(int i = left; i <= right; i++){
        ret1.chromosome[i] = a.chromosome[i];
        ret2.chromosome[i] = b.chromosome[i];
        freq1[ret1.chromosome[i]]++;
        freq2[ret2.chromosome[i]]++;
    }

    bool conflito = true;
    while(conflito){
        conflito = false;
        for(int i = 0; i < ret1.chromosome.size(); i++){
            if(ret1.chromosome[i] == -1 && freq1[b.chromosome[i]]){
                conflito = true;
                ret1.chromosome[i] = a.chromosome[i];
                freq1[ret1.chromosome[i]]++;
            }
        }
    }
    conflito = true;
    while(conflito){
        conflito = false;
        for(int i = 0; i < ret2.chromosome.size(); i++){
            if(ret2.chromosome[i] == -1 && freq2[a.chromosome[i]]){
                conflito = true;
                ret2.chromosome[i] = b.chromosome[i];
                freq2[ret2.chromosome[i]]++;
            }
        }
    }

    for(int i = 0; i < a.chromosome.size(); i++){
        if(ret1.chromosome[i] == -1){
            ret1.chromosome[i] = b.chromosome[i];
        }
        if(ret2.chromosome[i] == -1){
            ret2.chromosome[i] = a.chromosome[i];
        }
    }
    return {ret1, ret2};
}

void Population::reproduce(){
    std::random_shuffle(population.begin(), population.end());

    int sz = population.size();

    // crossing over
    for(int i = 0; i < sz; i += 2){
        std::pair < Individual, Individual > cross = crossingOver(population[i], population[i + 1]);
        population.emplace_back(cross.first);
        population.emplace_back(cross.second);
    }
    // mutation
    for(int i = 0; i < population.size(); i++){
        double random = ((double)rand()) / RAND_MAX;
        if(random <= 0.1){
            population[i].mutate();
        }
    }
}

void Population::nextGeneration(){
    select();
    reproduce();
}