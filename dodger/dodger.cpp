#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
int main(){

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(720,500),"Cat do(d)ge");
    window.setFramerateLimit(60);

    int catSpawnTimer = 15;
    float hp =10;
    int bulletTimer = 0;
    int points = 0;
    float barHeight = 20.f;
    float barWidth = 200.f;
    const int maxBulletTimer = 80;
    const int maxCatSpawnTimer = 20;
    const int maxHp = 10;
    const float speed =5.f;

    sf::Texture catTex;
    sf::Sprite cat;
    sf::RectangleShape hpBar;
    sf::RectangleShape hpBack;
    sf::RectangleShape bullet;
    sf::RectangleShape bulletBar;
    sf::RectangleShape bulletBack;
    sf::Texture dogeTex;
    sf::Sprite doge;
    sf::Vector2f entitySize(0.3f,0.3f);
    

    hpBar.setFillColor(sf::Color::Green);
    hpBar.setPosition(window.getSize().x -hp*20.f-10.f,10.f);
    
    hpBack.setFillColor(sf::Color::Red);
    hpBack.setPosition(hpBar.getPosition());
    hpBack.setSize(sf::Vector2f(hp*(barWidth/maxHp),barHeight));

    bullet.setFillColor(sf::Color::Red);
    bullet.setSize(sf::Vector2f(15.f,15.f));
    std::vector<sf::RectangleShape> bullets;

    bulletBar.setFillColor(sf::Color::Yellow);
    bulletBar.setPosition(sf::Vector2f(hpBar.getPosition().x,hpBar.getPosition().y + barHeight + 5.f));

    bulletBack.setFillColor(sf::Color::Red);
    bulletBack.setPosition(bulletBar.getPosition());
    bulletBack.setSize(sf::Vector2f(barWidth,barHeight));
    if(!catTex.loadFromFile("Textures/cat.png")){
        throw "Could not load cat.png\n";
    }

    cat.setTexture(catTex);
    cat.setScale(entitySize);

    std::vector<sf::Sprite> cats;
    cats.push_back(sf::Sprite(cat));

    if(!dogeTex.loadFromFile("Textures/doge.png")){
        throw "Could not load doge.png\n";
    }
    doge.setTexture(dogeTex);
    doge.setScale(entitySize);

    while(window.isOpen() && hp >0){
        hpBar.setSize(sf::Vector2f(hp*(barWidth/maxHp),barHeight));
        bulletBar.setSize(sf::Vector2f(bulletTimer*(barWidth/maxBulletTimer),barHeight));

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        doge.setPosition(sf::Vector2f(doge.getPosition().x,sf::Mouse::getPosition(window).y));
        if(doge.getPosition().y > window.getSize().y-doge.getGlobalBounds().height){
            doge.setPosition(doge.getPosition().x,window.getSize().y - doge.getGlobalBounds().height);
        }
        if(doge.getPosition().y <0){
            doge.setPosition(doge.getPosition().x,0);
        }
        
        for(size_t i =0;i<cats.size();i++){
            cats[i].move(-speed,0.f);
            if(cats[i].getPosition().y + cats[i].getGlobalBounds().width <=0){
                cats.erase(cats.begin()+i);
            }
        }

        for(size_t i =0;i<bullets.size();i++){
            bullets[i].move(speed,0.f);
            if(bullets[i].getPosition().y + bullets[i].getGlobalBounds().width >=window.getSize().y){
                bullets.erase(bullets.begin()+i);
        }   }
        
        if(catSpawnTimer <maxCatSpawnTimer){
            catSpawnTimer ++;
        }
        if(catSpawnTimer >=maxCatSpawnTimer){
            cat.setPosition(window.getSize().x,rand()%window.getSize().y-cat.getGlobalBounds().height);
            cats.push_back(sf::Sprite(cat));
            catSpawnTimer =0;
        }
        if(bulletTimer <maxBulletTimer){
            bulletTimer++;
        }
        if(bulletTimer >=maxBulletTimer && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            bullet.setPosition(sf::Vector2f(doge.getPosition().x + doge.getGlobalBounds().width,doge.getPosition().y + doge.getGlobalBounds().height/2));
            bullets.push_back(sf::RectangleShape(bullet));
            bulletTimer = 1;
        }
        for(size_t i =0;i<cats.size();i++){
            if(doge.getGlobalBounds().intersects(cats[i].getGlobalBounds())){
                cats.erase(cats.begin()+i);
                hp--;
            }
            for(size_t j =0;j<bullets.size();j++){
                if(bullets[j].getGlobalBounds().intersects(cats[i].getGlobalBounds())){
                    if(hp <maxHp){
                        hp+=.2;
                        points +=1;
                    }
                    cats.erase(cats.begin()+i);
                    bullets.erase(bullets.begin()+j);
                }
            }
        }
        

        window.clear();
        
        window.draw(doge);
        for(size_t i =0;i<cats.size();i++){
            window.draw(cats[i]);
        }
        for(size_t i =0;i<bullets.size();i++){
            window.draw(bullets[i]);
        }
        window.draw(hpBack);
        window.draw(hpBar);
        window.draw(bulletBack);
        window.draw(bulletBar);
        std::cout<<hp<<" "<< points<<std::endl;
        window.display();
    }

    

    return 0;
}