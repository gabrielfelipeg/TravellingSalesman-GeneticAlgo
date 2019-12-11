#pragma once
#include "individual.h"
#include <iostream>
#include <cassert>

class Population{
    bool resetStatus;
    long long F(int x);
    void select();
    void reproduce();
    int tam;
    std::pair< Individual, Individual > crossingOver(Individual &a, Individual &b);
    static bool comparator(std::pair<long long, Individual> a, std::pair<long long, Individual> b);
    public:
        long long currentBest;
        std::vector <Individual> population;
        std::vector < std::vector <long long> > weight;
        Population();
        void start(int k, int size);
        void reset();
        void nextGeneration();
};