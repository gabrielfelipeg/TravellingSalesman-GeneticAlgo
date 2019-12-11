#include <iostream>
#include <time.h>
#include <cstdlib>
#include "population.h"

int main(){
    srand(time(NULL));
    Population p;
    p.start(100, 1000);
    for(int i = 0; i < 2000; i++){
        if(i%100 == 0){
            std::cout << p.currentBest << std::endl;
        }
        p.nextGeneration();
    }
    std::cout << "Final result:" << std::endl;
    std::cout << p.currentBest << std::endl;
    return 0;
}