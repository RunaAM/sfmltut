#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <vector>
#include <cstdlib>


class Bullet{
public:
    sf::CircleShape shape;
    sf::Vector2f currValocity;
    float maxSpeed;
    int bulletCoolDown;

    Bullet(float radius = 5.f):currValocity(0.f,0.f),maxSpeed(15.f),bulletCoolDown{10}{
        this->shape.setRadius(radius);
        this->shape.setFillColor(sf::Color::Red);
    }
};

class Player{
    public:
    int hp;
    const float maxHp = 10.f;
    float speed;
    sf::Vector2f playerCenter;
    sf::CircleShape shape;
    float radius;
    Player(sf::Vector2u window):hp{10},speed{10.f},radius{25.f}{
        this->shape.setRadius(radius);
        this->shape.setFillColor(sf::Color::White);
        this->shape.setPosition(sf::Vector2f(window.x/2-radius,window.y/2-radius));
        playerCenter=sf::Vector2f(this->shape.getPosition().x + radius,this->shape.getPosition().y+radius);
    }
    void reCenter(){
        this->playerCenter=sf::Vector2f(this->shape.getPosition().x + radius,this->shape.getPosition().y+radius);
    }
    void Movement(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A )||sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->shape.move(-this->speed,0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            this->shape.move(this->speed,0.f);
        }       
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            this->shape.move(0.f,-this->speed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            this->shape.move(0.f,this->speed);
        }
    }
    void Colision(sf::Vector2u window){
        if(this->shape.getPosition().x < 0){
            this->shape.setPosition(0,this->shape.getPosition().y);
        }
        if(this->shape.getPosition().x +this->shape.getRadius()*2>= window.x){
            this->shape.setPosition(window.x-this->shape.getRadius()*2,this->shape.getPosition().y);
        }
        if(this->shape.getPosition().y <0){
            this->shape.setPosition(this->shape.getPosition().x, 0);
        }
        if(this->shape.getPosition().y + 2*this->shape.getRadius()>=window.y){
            this->shape.setPosition(this->shape.getPosition().x,window.y-2*this->shape.getRadius());
        }
    }
};

class Enemy{
    public:
    sf::RectangleShape shape;
    int spawnTimer;
    int totalSpawnTimer ;
    Enemy(sf::Vector2f size=sf::Vector2f{50.f,50.f}):spawnTimer{0},totalSpawnTimer{20}{
        this->shape.setSize(size);
        this->shape.setFillColor(sf::Color::Magenta);
    }

};

void updateBars(sf::RectangleShape &hpBar,sf::RectangleShape &ammoBar,float hp,float maxHp,float ammoCoolDown,float barWidth,float barHeight);
void bulletsColision(std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, sf::RenderWindow &window);
void enemiesColision(std::vector<Enemy> &enemies,Player &Player);
void updateVectors(sf::Vector2f &mousePosWindow,sf::Vector2f &aimDir,sf::Vector2f &aimDirNorm,Player Player,sf::RenderWindow &window);
void updateBulletSpawn(int &spawnCounter, Player &Player,Bullet b1,std::vector<Bullet> &bullets,int &bulletCoolDown, sf::Vector2f &aimDirNorm);
void updateEnemySpawn(int &spawnCounter,std::vector<Enemy>&enemies,Enemy &enemy,sf::RenderWindow &window);
int main(){
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800,600), "360 shooter",sf::Style::Default);
    window.setFramerateLimit(60);

    float barWidth = 200.f;
    float barHeight = 20.f;
    int spawnCounter =20;

    Player Player(window.getSize());

    //HealthBar
    sf::RectangleShape hpBar;
    hpBar.setFillColor(sf::Color::Green);
    hpBar.setPosition(sf::Vector2f(window.getSize().x-Player.hp*(barWidth/Player.maxHp)-5.f,5.f));
    
    sf::RectangleShape hpBack;
    hpBack.setFillColor(sf::Color::Red);
    hpBack.setPosition(hpBar.getPosition());
    hpBack.setSize(sf::Vector2f(barWidth,20.f));

    //AmmoBar
    sf::RectangleShape bulletBar;
    bulletBar.setFillColor(sf::Color::Yellow);
    bulletBar.setPosition(sf::Vector2f(window.getSize().x-barWidth-5.f,barHeight+10.f));

    sf::RectangleShape bulletBack;
    bulletBack.setFillColor(sf::Color::Red);
    bulletBack.setPosition(bulletBar.getPosition());
    bulletBack.setSize(sf::Vector2f(barWidth,barHeight));

    //Bullets
    Bullet b1;

    std::vector<Bullet>bullets;
    int bulletCoolDown =0;

    Enemy enemy;
    
    std::vector<Enemy> enemies;
    
    //Vector
    
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;



    while(window.isOpen()&&Player.hp >0){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        updateVectors(mousePosWindow,aimDir,aimDirNorm,Player,window);
        updateBars(hpBar,bulletBar,Player.hp,Player.maxHp,bulletCoolDown,barWidth,barHeight);

        Player.Movement();
        Player.reCenter();


        updateBulletSpawn(spawnCounter,Player,b1,bullets,bulletCoolDown,aimDirNorm);
        updateEnemySpawn(spawnCounter,enemies,enemy,window);
        
        bulletsColision(bullets,enemies,window);
        enemiesColision(enemies,Player);
        
        
        Player.Colision(window.getSize());
        //Draw

        window.clear();

        window.draw(Player.shape);
        for(size_t i =0;i<bullets.size();i++){
            window.draw(bullets[i].shape);
        }
        for(size_t i =0;i<enemies.size();i++){
            window.draw(enemies[i].shape);
        }
        
        window.draw(hpBack);
        window.draw(hpBar);
        window.draw(bulletBack);
        window.draw(bulletBar);
        
        window.display();
    }

    return 0;
}
void updateBars(sf::RectangleShape &hpBar,sf::RectangleShape &ammoBar,float hp,float maxHp,float ammoCoolDown,float barWidth,float barHeight){
        hpBar.setSize(sf::Vector2f(hp*(barWidth/maxHp),barHeight));
        ammoBar.setSize(sf::Vector2f(ammoCoolDown*20.f,barHeight));
}
void bulletsColision(std::vector<Bullet> &bullets, std::vector<Enemy> &enemies, sf::RenderWindow &window){
    for(size_t i =0;i<bullets.size();i++){
            bullets[i].shape.move(bullets[i].currValocity);
            if(bullets[i].shape.getPosition().x <0 ||bullets[i].shape.getPosition().x >window.getSize().x ||
                bullets[i].shape.getPosition().y <0 || bullets[i].shape.getPosition().y >window.getSize().y){
                    bullets.erase(bullets.begin()+i);
                }
            //enemy colision
            
            for(size_t j=0;j<enemies.size();j++){
                if(enemies[j].shape.getGlobalBounds().intersects(bullets[i].shape.getGlobalBounds())){
                    enemies.erase(enemies.begin()+j);
                    bullets.erase(bullets.begin()+i);
                }
                    
                
            }
            
            
        }
}
void enemiesColision(std::vector<Enemy> &enemies,Player &Player){
    for(size_t i =0;i<enemies.size();i++){
            if(enemies[i].shape.getGlobalBounds().intersects(Player.shape.getGlobalBounds())){
                       enemies.erase(enemies.begin()+i);
                       Player.hp--; 
                    }
        }
}
void updateVectors(sf::Vector2f &mousePosWindow,sf::Vector2f &aimDir,sf::Vector2f &aimDirNorm,Player Player,sf::RenderWindow &window){
    mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window)); 
    aimDir = mousePosWindow - Player.playerCenter; 
    aimDirNorm=sf::Vector2f(aimDir.x/sqrt(pow(aimDir.x,2) +pow(aimDir.y,2)),aimDir.y/sqrt(pow(aimDir.x,2) +pow(aimDir.y,2))) ;             

}
void updateBulletSpawn(int &spawnCounter, Player &Player,Bullet b1,std::vector<Bullet> &bullets,int &bulletCoolDown, sf::Vector2f &aimDirNorm){
    if(bulletCoolDown <b1.bulletCoolDown){
            bulletCoolDown++;
        }
        if(bulletCoolDown >=b1.bulletCoolDown &&sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            b1.shape.setPosition(Player.playerCenter);
            b1.currValocity = aimDirNorm* b1.maxSpeed;
            bullets.push_back(Bullet(b1));
            bulletCoolDown =0;

        }
}
void updateEnemySpawn(int &spawnCounter,std::vector<Enemy> &enemies,Enemy &enemy,sf::RenderWindow &window){
    if(spawnCounter<50){
            spawnCounter++;
        }
    if(spawnCounter >=50&& enemies.size()<40){
        enemy.shape.setPosition(sf::Vector2f(rand()%window.getSize().x,rand()%window.getSize().y));
        enemies.push_back(Enemy(enemy));
        spawnCounter=0;
    }
}