//
//  bullet.hpp
//  GatorGlory


#ifndef bullet_hpp
#define bullet_hpp

#include "entity.hpp"

class bullet: public entity
{
public:
    double Speed = 6;
    int attackDamage = 1;
    int direction = 3;
    bool contact = false;
    
    bullet();
    void setDirection(int direc);
    void update();
    void move();
    void UporDown();
    void reverseUporDown();
};

#endif /* bullet_hpp */
