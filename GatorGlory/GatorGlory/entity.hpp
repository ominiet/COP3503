//
//  entity.hpp
//  GatorGlory
//


#ifndef entity_hpp
#define entity_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>
#include "ResourcePath.hpp"
#include <cstdlib>
#include <functional>
#include <tgmath.h>
#include <deque>
#include <list>
#include <vector>
#include <unistd.h>
using namespace std;
//#include "randomFunction.h"

class entity
{
public:
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;
    
private:
protected:
};

#endif /* defined(__InstallingSFML__entity__) */