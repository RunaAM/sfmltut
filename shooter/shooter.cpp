#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>

int main(){
    srand(std::time(NULL));
    sf::RenderWindow window(sf::VideoMode(640,400),"Shooter",sf::Style::Default);
    window.setFramerateLimit(60);
    sf::CircleShape player;
    sf::CircleShape projectile;
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;
    std::vector<sf::CircleShape> projectiles;
    sf::Vector2f playerCenter;
    int shootTimer = 0,enemyTimer =0; 

    enemy.setFillColor(sf::Color::Magenta);
    enemy.setSize(sf::Vector2f(30.f,30.f));

    projectile.setRadius(5.f);
    projectile.setFillColor(sf::Color::Red);

    player.setFillColor(sf::Color::Blue);
    player.setRadius(50.f);
    player.setPosition(sf::Vector2f(window.getSize().x/2 - player.getRadius(),window.getSize().y - player.getRadius()*2-5));
    projectiles.push_back(sf::CircleShape(projectile));
    enemies.push_back(sf::RectangleShape(enemy));
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        player.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x -player.getRadius(),player.getPosition().y));
        playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
        if(shootTimer <6){
            shootTimer++; //shootTimer = (shootTimer <3)? shootTimer +1 : shootTimer;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >=6){
            shootTimer = 0;
            projectile.setPosition(playerCenter);
            projectiles.push_back(sf::CircleShape(projectile));
        }
        for(size_t i =0;i<projectiles.size();i++){
            projectiles[i].move(sf::Vector2f(0,-10.f));
            if(projectiles[i].getPosition().y <=0){
                projectiles.erase(projectiles.begin()+i);
            }
        }

        if(enemyTimer < 20){
            enemyTimer++;
        }
        if(enemyTimer >=20){
            enemy.setPosition(rand()%window.getSize().x-enemy.getSize().x,0);
            enemies.push_back(sf::RectangleShape(enemy));
            enemyTimer = 0;
        }
        for(size_t i=0;i<enemies.size();i++){
            enemies[i].move(sf::Vector2f(0,5.f));
            if(enemies[i].getPosition().y + enemies[i].getSize().y ==window.getSize().y){
                enemies.erase(enemies.begin()+i);
            }
        }
        for(size_t i=0;i<enemies.size();i++){
            for(size_t j =0;j<projectiles.size();j++){
               if(enemies[i].getGlobalBounds().intersects(projectiles[j].getGlobalBounds())){
                    enemies.erase(enemies.begin()+i);
                    projectiles.erase(projectiles.begin()+j);
               }
            }
        }
        window.clear();
        window.draw(player);
        for(size_t i=0;i<enemies.size();i++){
            window.draw(enemies[i]);
        }
        for(size_t i =0;i<projectiles.size();i++){
            window.draw(projectiles[i]);
        }
        window.display(); 
    }
    return 0;
}
