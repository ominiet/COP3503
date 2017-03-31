

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <array>
#include "ResourcePath.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "random.hpp"
using namespace std;

int main(int, char const**)
{
    int stateCount = 0;
    int walkCount = 0;
    double walkSpeed = .3;
    int delayCount = 1;
    int bullCount = 0;
    int iterCount;
    int waveCount = 0;
    int zombMult = 5;
    int randSide;
    int sackCount = 0;
    string stats = "HP:   Score:     Wave:    ";
    string finalString = "Final Score:     ";
    string hp;
    string score;
    string wave;
    bool start = true;
    
    
    sf::Clock clock;
    
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1334, 599), "GatorGlory");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "Gator_logo.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

   //Load Background Sprite
    sf::Texture backTexture;
    if(!backTexture.loadFromFile(resourcePath() + "Field.jpg")) {
       return EXIT_FAILURE;
    }
    sf::Sprite background(backTexture);
    
    
    //Load Player Sprite
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile(resourcePath() + "GatorPlayer.png")) {
        return EXIT_FAILURE;
    }
    //Load Football Sprite
    sf::Texture football;
    if(!football.loadFromFile(resourcePath() + "football.png")){
        return EXIT_FAILURE;
    }
    //Load Enemy Texture;
    sf::Texture enemyTexture;
    if(!enemyTexture.loadFromFile(resourcePath() + "Enemy.png")){
        return EXIT_FAILURE;
    }
    //Load Game Over Image
    sf::Texture gameOver;
    if(!gameOver.loadFromFile(resourcePath() + "GameOver1.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite endGame(gameOver);
    
    //Load Start Screen Image
    sf::Texture startScreen;
    if(!startScreen.loadFromFile(resourcePath() + "StartScreen.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite startSprite(startScreen);
    startSprite.setPosition(window.getSize().x/2-startSprite.getGlobalBounds().width/2,0);

    // Create Stats Line
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "font.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text(stats, font, 50);
    text.setColor(sf::Color::Blue);
    text.setPosition(0, 0);
    text.setStyle(sf::Text::Bold);
    
    //Final Score Line
    sf::Text finalScore(finalString,font,50);
    finalScore.setColor(sf::Color::Blue);
    finalScore.setPosition(0,0);
    finalScore.setStyle(sf::Text::Bold);
    
    sf::Text sackedLine("Sacked!!",font,75);
    sackedLine.setColor(sf::Color::Red);
    sackedLine.setPosition(window.getSize().x/2-sackedLine.getGlobalBounds().width/2,window.getSize().y/2-sackedLine.getGlobalBounds().height/2);
    
    // create file stream for highscore input
    
    fstream highScore;
    highScore.open(resourcePath() + "HighScore.txt");
    string list = "";
    array<string,10> scores = {};
    int hscount = 0;
    
    while (!highScore.eof()){
        getline(highScore, list);
        if (hscount < 10){
            scores[hscount] = list;
            hscount++;
        }
    }
    
    for (int x = 0; x < scores.size(); x++){
        cout << scores[x] << endl;
    }
    
    highScore.close();
    
    highScore.open(resourcePath() + "HighScore.txt", fstream::out | fstream::trunc);
    highScore << "how does this work" << endl;
    highScore.close();
    
    
    
    //create player
    class player player;
    player.sprite.setTexture(playerTexture);
    player.setPosition((window.getSize().x/2)-player.sprite.getGlobalBounds().width,(window.getSize().y/2)-player.sprite.getGlobalBounds().height);
    
    //create bullet Vector
    vector<bullet> bulletVect;
    
    //bullet object
    class bullet bullet1;
    bullet1.sprite.setTexture(football);
    
    //create enemy Vector
    vector<enemy> enemyVect;
    
    //enemy object
    class enemy seminole;
    seminole.sprite.setTexture(enemyTexture);
    
    
    //iterator creation for Vector deletion
    vector<enemy>::const_iterator iter;
    vector<bullet>::const_iterator iter2;
    //set frame rate
    window.setFramerateLimit(60);
    
    
    
    
        // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color::Blue);
        //start screen
        if (start == true){
            window.draw(startSprite);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                start = false;
            }
        }
        //endscreen
        else if (player.health < 1){
            window.clear();
            endGame.setPosition(window.getSize().x/2 - endGame.getGlobalBounds().width/2,window.getSize().y/2-endGame.getGlobalBounds().height/2);
            window.draw(endGame);
            finalString = finalString.replace(13,score.length(),score);
            finalScore.setString(finalString);
            window.draw(finalScore);
            }
        //Normal game
        else{
            sf::Time elapsed = clock.getElapsedTime();
            
            //checks for collision of bullet and enemy
            if (enemyVect.size() >= 1 && bulletVect.size() >=1){
                for (int i = 0; i < enemyVect.size(); i++){
                    for (int j = 0; j<bulletVect.size();j++){
                        if (bulletVect[j].rect.getGlobalBounds().intersects(enemyVect[i].rect.getGlobalBounds())){
                            enemyVect[i].health--;
                            bulletVect[j].contact = true;
                            player.score++;
                        }
                    }
                }
            }
            
            
            //removes enemy if health is 0
            iterCount = 0;
            if (enemyVect.size() >= 1){
                for (iter = enemyVect.begin(); iter != enemyVect.end(); iter++){
                    if (enemyVect[iterCount].health <= 0){
                        enemyVect.erase(iter);
                        break;
                    }
                    iterCount++;
                }
            }
            //removes bullet if contact is true
            iterCount = 0;
            if (bulletVect.size() >= 1 && enemyVect.size() >= 1){
                for (iter2 = bulletVect.begin(); iter2 != bulletVect.end(); iter2++){
                    if (bulletVect[iterCount].contact == true){
                        bulletVect.erase(iter2);
                        break;
                    }
                    iterCount++;
                }
            }
            
            //Checks for collision with player
            //kills seminole and subtracts 1 hp from player
            if (enemyVect.size() >= 1){
                for (int i = 0; i < enemyVect.size(); i++){
                    if (enemyVect[i].rect.getGlobalBounds().intersects(player.rect.getGlobalBounds())){
                        enemyVect[i].health--;
                        player.health--;
                        player.sacked = true;
                    }
                }
            }
            
            
            // Bullets
            
            if (elapsed.asSeconds() >= 0.3){
                
                ///clock.restart();  changed location to within the below if statement
                
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    bullet1.setDirection(player.getDirection());
                    bullet1.rect.setPosition(player.rect.getPosition().x + player.rect.getSize().x/2-bullet1.rect.getSize().x/2,player.rect.getPosition().y + player.rect.getSize().y/2 - bullet1.rect.getSize().y/2);
                    bullet1.UporDown();
                    bulletVect.push_back(bullet1);
                    bullet1.reverseUporDown();
                    clock.restart();
                }
                
            }
            
            //spawning enemies
            
            if (enemyVect.size()==0){
                waveCount ++;
                seminole.setSpeed(seminole.Speed + .2);
                for (int i = 0; i < waveCount*zombMult;i++){
                    randSide = myrandomInt(4);
                    switch (randSide){
                        case 0: //left
                            ///changed to account for enemy players randomly getting spawned in the bottom left corner
                            seminole.rect.setPosition(0,myrandomInt(window.getSize().y-seminole.rect.getGlobalBounds().height));
                            enemyVect.push_back(seminole);
                            break;
                        case 1://top
                            ///changed to account for enemy players randomly getting spawned in the top right corner
                            seminole.rect.setPosition(myrandomInt(window.getSize().x-seminole.rect.getGlobalBounds().width),0);
                            enemyVect.push_back(seminole);
                            break;
                        case 2://right
                            ///changed to account for enemy players randomly getting spawned in the bottom right corner
                            seminole.rect.setPosition((window.getSize().x-seminole.rect.getSize().x),myrandomInt(window.getSize().y-seminole.rect.getSize().y));
                            enemyVect.push_back(seminole);
                            break;
                        case 3://bottom
                            ///changed to account for enemy players randomly getting spawned in the bottom right corner
                            seminole.rect.setPosition(myrandomInt(window.getSize().x-seminole.rect.getSize().x),(window.getSize().y-(seminole.rect.getSize().y)));
                            enemyVect.push_back(seminole);
                            break;
                    }
                }
            }
            
            
            //UPDATE: Updates Player to rect location
            player.update();
            player.move();
            
            
            
            //Stop player from going off the window
            if (player.rect.getPosition().x < 0){
                player.rect.move(player.walkSpeed,0);
            }
            if ((player.rect.getPosition().x + player.rect.getSize().x) > window.getSize().x){
                player.rect.move(-player.walkSpeed,0);
            }
            if (player.rect.getPosition().y < 0){
                player.rect.move(0,player.walkSpeed);
            }
            if ((player.rect.getPosition().y + player.rect.getSize().y) > window.getSize().y){
                player.rect.move(0,-player.walkSpeed);
            }
            
            
            
            // Draw the background
            window.draw(background);
            
            if (enemyVect.size() >= 1)
            {
                for (int i = 0; i < enemyVect.size(); i ++){
                    if (abs(enemyVect[i].rect.getPosition().y-player.rect.getPosition().y) > 250 || abs(enemyVect[i].rect.getPosition().x-player.rect.getPosition().x) >250){
                        enemyVect[i].state2(player.rect.getPosition(),window.getSize());
                    }
                    else{
                    enemyVect[i].move(player.rect.getPosition());
                        //cout << "State1! " << stateCount <<"\n";
                        stateCount++;
                    }
                    enemyVect[i].update();
                    //window.draw(enemyVect[i].rect);
                    window.draw(enemyVect[i].sprite);
                }
            }
            
            
            
            
            //draw the footballs
            if (bulletVect.size() >= 1)
            {
                for (int i = 0; i < bulletVect.size(); i ++){
                    bulletVect[i].move();
                    bulletVect[i].update();
                    //window.draw(bulletVect[i].rect);
                    window.draw(bulletVect[i].sprite);
                }
            }
            
            //window.draw(player.rect);
            window.draw(player.sprite);
            
            //set stat string
            hp = to_string(player.health);
            score = to_string(player.score);
            wave = to_string(waveCount);
            
            stats = stats.replace(4,1,hp);
            stats = stats.replace(13,score.length(),score);
            stats = stats.replace(23,wave.length(),wave);
            
            text.setString(stats);
            
            // Display the stat string
            window.draw(text);
            
            if (player.sacked == true){
                window.draw(sackedLine);
                sackCount ++;
                if (sackCount == 60){
                    player.sacked = false;
                    sackCount = 0;
                }
            }
            
            

        }
        //Update window
        window.display();
        
    }

    return EXIT_SUCCESS;
}
