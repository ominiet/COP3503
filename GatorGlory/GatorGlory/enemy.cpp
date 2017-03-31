//
//  enemy.cpp
//  GatorGlory
//


#include "enemy.hpp"

enemy::enemy()
{
    rect.setSize(sf::Vector2f(47,54));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(sf::Vector2f(200,200));
    sprite.setTextureRect(sf::IntRect(0,0,60,60));
}
void enemy::update(){
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
void enemy::move(sf::Vector2f pos){//state 1 walk towards player
    if (abs(rect.getPosition().x-pos.x) > abs(rect.getPosition().y-pos.y)){
        if (rect.getPosition().x < pos.x){//right
            rect.setSize(sf::Vector2f(36,58));
            rect.move(Speed,0);
            sprite.setTextureRect(sf::IntRect(60*walkCount,120,60,60));
            direction = 2;
        }
        if (rect.getPosition().x > pos.x){//left
            rect.setSize(sf::Vector2f(36,58));
            sprite.setTextureRect(sf::IntRect(60*walkCount,60,60,60));
            rect.move(-Speed,0);
            direction = 4;
        }
    }
    else{
        if (rect.getPosition().y > pos.y){//up
            rect.setSize(sf::Vector2f(47,54));
            sprite.setTextureRect(sf::IntRect(60*walkCount,180,60,60));
            rect.move(0,-Speed);
            direction = 1;
            
        }
        if (rect.getPosition().y < pos.y){//down
            rect.setSize(sf::Vector2f(47,54));
            sprite.setTextureRect(sf::IntRect(60*walkCount,0,60,60));
            rect.move(0,Speed);
            direction = 3;
        }
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
void enemy::state2(sf::Vector2f pos, sf::Vector2u window){
    if (randomDirec == 0){
        randomDirec = myrandomInt(4) + 1;//picks one of the 4 directions
        randomWalk = myrandomInt(100)+75;//lets length be equal to a max of 35 and min of 10
    }
    switch(randomDirec){
        case 0: cout<< "0 chosen\n";
            break;//just in case 0 is allowed
        case 1:rect.setSize(sf::Vector2f(47,54));
            sprite.setTextureRect(sf::IntRect(60*walkCount,180,60,60));
            rect.move(0,-Speed);
            direction = 1;
            break;
        case 2:rect.setSize(sf::Vector2f(36,58));
            rect.move(Speed,0);
            sprite.setTextureRect(sf::IntRect(60*walkCount,120,60,60));
            direction = 2;
            break;
        case 3:rect.setSize(sf::Vector2f(47,54));
            sprite.setTextureRect(sf::IntRect(60*walkCount,0,60,60));
            rect.move(0,Speed);
            direction = 3;
            break;
        case 4:rect.setSize(sf::Vector2f(36,58));
            cout<<"4 chosen\n";
            sprite.setTextureRect(sf::IntRect(60*walkCount,60,60,60));
            rect.move(-Speed,0);
            direction = 4;
            break;
    }
    if (rect.getPosition().x < 0){//prevents enemy from walking off of map
        rect.move(Speed,0);//moves rect back onto map
        randomWalk = 0;//ends cycle of walking in that direction and chooses new one
    }
    if ((rect.getPosition().x + rect.getSize().x) > window.x){
        rect.move(-Speed,0);
        randomWalk = 0;
    }
    if (rect.getPosition().y < 0){
        rect.move(0,Speed);
        randomWalk = 0;
    }
    if ((rect.getPosition().y + rect.getSize().y) > window.y){
        rect.move(0,-Speed);
        randomWalk = 0;
    }

    randomWalk --;
    if (randomWalk <= 0) randomDirec = 0;//sets random Direc back to 0 if the length has been reached
    
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
void enemy::setSpeed(double speed){
    this->Speed = speed;
}
