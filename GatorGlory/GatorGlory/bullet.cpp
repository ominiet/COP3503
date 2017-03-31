//
//  bullet.cpp
//  GatorGlory
//


#include "bullet.hpp"

bullet::bullet()
{
    rect.setSize(sf::Vector2f(34,20));
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(sf::Vector2f(0,0));
    sprite.setTextureRect(sf::IntRect(0,0,34,20));
}
void bullet::setDirection(int direc)
{
    direction = direc;

}
void bullet::update(){
    sprite.setPosition(rect.getPosition());
}
void bullet::move(){
    if (direction == 1){//up
        rect.move(0,-Speed);
    }
    if (direction == 2){//right
        rect.move(Speed,0);
    }
    if (direction == 3){//down
        rect.move(0,Speed);
    }
    if (direction == 4){//left
        rect.move(-Speed,0);
    }
    
}
void bullet::UporDown(){
    if (direction == 1){
        sprite.rotate(-90);
        rect.rotate(-90);
        rect.move(rect.getSize().x/2-rect.getSize().y/2, rect.getSize().y/2+rect.getSize().x/2);
    }
    if (direction == 3){
        sprite.rotate(90);
        rect.rotate(90);
        rect.move(rect.getSize().x/2+rect.getSize().y/2, rect.getSize().y/2-rect.getSize().x/2);
    }
}
void bullet::reverseUporDown(){
    if (direction == 1){
        sprite.rotate(90);
        rect.rotate(90);
        
    }
    if (direction ==3){
        sprite.rotate(-90);
        rect.rotate(-90);
        
    }
}