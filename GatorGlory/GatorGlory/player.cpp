//
//  player.cpp
//  GatorGlory
//


#include "player.hpp"


player::player()
{
    rect.setSize(sf::Vector2f(47,54));
    rect.setFillColor(sf::Color::Cyan);
    rect.setPosition(sf::Vector2f(200,200));
    sprite.setTextureRect(sf::IntRect(0,0,60,60));
}
void player::update(){
    switch(direction){
        case 1:sprite.setPosition(rect.getPosition().x-6,rect.getPosition().y-6);
            break;
        case 2: sprite.setPosition(rect.getPosition().x-10,rect.getPosition().y-1);
            break;
        case 3:sprite.setPosition(rect.getPosition().x-6,rect.getPosition().y-2);
            break;
        case 4:sprite.setPosition(rect.getPosition().x-12,rect.getPosition().y);
            break;
    }
    //sprite.setPosition(rect.getPosition());
}
void player::move(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ //Down
        
        rect.move(0,walkSpeed);
        sprite.setTextureRect(sf::IntRect(60*walkCount,0,60,60));
        rect.setSize(sf::Vector2f(47,54));
        direction = 3;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ //Left
        rect.move(-walkSpeed,0);
        sprite.setTextureRect(sf::IntRect(60*walkCount,60,60,60));
        rect.setSize(sf::Vector2f(36,58));
        direction = 4;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ //Up
        
        rect.move(0,-walkSpeed);
        sprite.setTextureRect(sf::IntRect(60*walkCount,180,60,60));
        rect.setSize(sf::Vector2f(47,54));
        direction = 1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ //Right
        rect.move(walkSpeed,0);
        sprite.setTextureRect(sf::IntRect(60*walkCount,120,60,60));
        rect.setSize(sf::Vector2f(36,58));
        direction = 2;
    }
    delayCount ++;
    if (delayCount % 15 == 0){
        walkCount++;
    }
    if (walkCount == 16){
        walkCount = 0;
    }
    //walkCount++;
    if (walkCount == 4){
        walkCount = 0;
    }

    
}
int player::getDirection(){
    return direction;
}
void player::setPosition(int x, int y){
    rect.setPosition(x,y);
}
