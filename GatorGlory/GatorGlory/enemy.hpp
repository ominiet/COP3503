//
//  enemy.hpp
//  GatorGlory
//


#ifndef enemy_hpp
#define enemy_hpp

#include "entity.hpp"
#include <cstdlib>
#include "random.hpp"

class enemy: public entity
{
public:
    double Speed = .3;
    int attackDamage = 1;
    int walkCount = 0;
    int delayCount;
    int direction = 3; // Up = 1,Right = 2,Down = 3, Left = 4
    int health = 1;
    int randomDirec = 0;
    int randomWalk = 0; // used to make enemy walk in random direction for a certain length
    
    
    enemy();
    void update();
    void move(sf::Vector2f pos);
    void state2(sf::Vector2f pos, sf::Vector2u windowSize);
    int getDirection();
    void setSpeed(double speed);
};

#endif /* enemy_hpp */
