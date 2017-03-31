//
//  player.hpp
//  GatorGlory


#ifndef player_hpp
#define player_hpp

#include "entity.hpp"

class player: public entity
{
public:
    double walkSpeed = 2;
    int attackDamage = 1;
    int walkCount = 0;
    int delayCount;
    int direction = 3; // Up = 1,Right = 2,Down = 3, Left = 4
    int health = 5;
    int score = 0;
    bool sacked = false;
    
    player();
    void update();
    void move();
    int getDirection();
    void setPosition(int x, int y);
};


#endif /* player_hpp */
