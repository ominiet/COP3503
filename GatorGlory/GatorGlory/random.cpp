//
//  random.cpp
//  GatorGlory
//


#include "random.hpp"


int myrandomInt(int max){//gives a number [0,max)
    int randomNumber = rand();
    float random = (randomNumber % max);
    int myRandom = random;
    return myRandom;
    
}
