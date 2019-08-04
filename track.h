#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include "car.h"
#include "mySTL.h"

class Track{
private:
    /*
        Basically creating some line to have some cricuit 
        generated on the window.
    */
    double noiseMax = 40.0;  
    // double maxPoints = 63.0;

    std::vector<sf::Vertex*> vecOfCheckpoints;
    std::vector<sf::Vertex*> circleTrack;

    sf::Vector2f size;
    sf::Vector2f startingPoint;
    sf::Vector2f endingPoint;

    sf::Vertex wall[128];
    sf::Vertex checkPoint[128];

public:
    Track();
    ~Track();

    void draw(sf::RenderWindow&); // will draw the simple circuit in this function
    void walls(sf::Vector2f, int, int ,bool);
    bool carHitWall(Car, sf::RenderWindow&);

    std::vector<sf::Vertex *> getVecOfWall();

    //custom map function taken from Arduino Map example
    template <class myType>
    myType map(myType val, myType inputStart, myType inputEnd, myType outputStart, myType outputEnd){
        return (val -  inputStart) * (outputEnd - outputStart) / (inputEnd - inputStart) + outputStart; 
    }
};