#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
int main(){
    float size = 50.f;
    float move_x ,move_y,screen_width=640.f,screen_height = 400.f ;
    bool game = true;
    bool pause = false;
    int circle_size = 60;
    const int FPS = 60;
    sf::Color colors[7] ={sf::Color::Cyan,sf::Color::Red,sf::Color::Yellow,sf::Color::White,sf::Color::Black,sf::Color::Green,sf::Color::Magenta};
    int color =0;
    sf::RenderWindow window(sf::VideoMode(screen_width,screen_height),"SFML works!",sf::Style::Default);
    window.setFramerateLimit(FPS);
    sf::CircleShape shape(size);
    sf::CircleShape cerc(size);
    //shape.setPosition(sf::Vector2f((screen_width-circle_size)/2,(screen_height-circle_size)/2));
    sf::RectangleShape pauseMenu(sf::Vector2f(640.f,400.f));
    shape.setFillColor(sf::Color::Red);   
    while (window.isOpen()){
        
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Z){
                    color = (color == 6)? 0 :color+1;
                    shape.setFillColor(colors[color%7]);
                }
                else if(event.key.code == sf::Keyboard::Escape){
                    if(pause == false){
                        pause = true;
                    }
                    else{
                        pause = false;
                    }
                }
                switch(event.key.code){
                case sf::Keyboard::A:
                    move_x = -1.f;
                    break;
                case sf::Keyboard::D:
                    move_x = 1.f;
                    break;
                
                case sf::Keyboard::S:
                    move_y = 1.f;
                    break;
                case sf::Keyboard::W:
                    move_y = -1.f;
                    break;
                }
            }
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S){
                    move_y = 0;
                }
                else if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::A){
                    move_x = 0;
                }
            }
            if(event.type == sf::Event::LostFocus){
                pause = true;
            }
            if(event.type == sf::Event::GainedFocus){
                pause = false;
            
            }
               
        }
        shape.move(move_x,move_y);
        window.clear(sf::Color::Blue);
        window.draw(shape);
        window.draw(cerc);
        if(pause == true){
            window.draw(pauseMenu);
        }
        
        
        window.display();
    }
    return 0;
}