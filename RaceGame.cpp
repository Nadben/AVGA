#include <SFML/Graphics.hpp>
#include "RaceGame.h"
#include "track.h"

//Kinda Work except for the window size.

extern float const windowHeight;
extern float const windowWidth;


int main()
{
    sf::RenderWindow window(sf::VideoMode(windowHeight, windowWidth), "RaceGame!");
    sf::Clock clock;

    Car myCar;
    Track myTrack;

    bool dies = false;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            
            if(event.type == sf::Event::KeyPressed){
                // std::cout<<"key pressed"<<std::endl;
                switch (event.key.code)
                {
                case sf::Keyboard::Up :
                    myCar.setAccel();
                    break;

                case sf::Keyboard::Left :
                    myCar.steerLeft();
                    break;
                    
                case sf::Keyboard::Right :
                    myCar.steerRight();
                    break;

                case sf::Keyboard::Down :// breaks
                    myCar.setBrakes();
                    // myCar.setAccel({acceleration, acceleration});
                    break;

                
                default:
                    break;
                }
            }
            else if (event.type == sf::Event::KeyReleased){

             switch (event.key.code)
                {
                case sf::Keyboard::Up :
                    myCar.stopAccel();
                    break;

                case sf::Keyboard::Left :
                    myCar.stopSteering();
                    break;
                    
                case sf::Keyboard::Right :
                    myCar.stopSteering();
                    break;

                case sf::Keyboard::Down :
                    myCar.stopAccel();
                    break;

                
                default:
                    break;
                }

            }
        }

        window.clear();
        myCar.update();
        dies = myTrack.carHitWall(myCar, window);
        if(dies){
            myCar.death(dies);
        }

        //for each sensor, draw it and calculate distance from wall.
        for(uint8_t i = 0 ; i < 9; i++){
            myCar.getSensor()[i].draw(window);
            myCar.getSensor()[i].cast(myTrack.getVecOfWall(), window, i);
        }

        myCar.draw(window);
        myTrack.draw(window);
        window.display();
    }

    return 0;
}












