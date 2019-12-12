#pragma once
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>

class Individual{
    public:
        std::vector<int> chromosome;
        void mutate();
        Individual();
        bool isValid(int tam);
        Individual(std::vector<int> param);
};