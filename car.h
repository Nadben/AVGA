#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "sensor.h"


// Not C++ compliant
// Type safe tho
float const windowHeight = 940;
float const windowWidth = 940;
float const carHeight = 15;
float const carWidth  = 25;
float const maxVelocity = 0.5;
float const acceleration = 0.08; //declared in racegame.cpp but should really be inside class
float const maxSteerVel = 0.8;
float const brake = 0.0;

uint8_t const numberOfSensors = 9;


class Car {
private:
/*
    car class that contains specific car information like : acceleration, angle of steering, velocity
    could also contain a score specific for the car object created

    when created we create a Box of a specific size that i'll determine later with SFML library
    It shall also be instanciated with an array of sensors that will measure the distance between the car
    and the walls of the circuit.

    Move I'll need also a mover function a bit like draw to move the car relatively to velocity and steering angle 
*/

    Sensor carSensor[numberOfSensors];

    sf::RectangleShape carFrame;    
    sf::Vector2f vel;
    sf::Vector2f position;
    sf::Vector2f origin;
    sf::Vector2f accel;
    sf::Vector2f carSize;

    float angle = 0.0;
    float aVel = 0.0;
    float aAccel = 0.0;
    // float steeringAngle;

    //* brain input vec and output vec
    std::vector<double> inputs;
    std::vector<double> outputs;

    //this is where the brain is instanciated for the car...
    // MLP brain; (8 inputs with 4 outputs)

    //! this is the next thing I need to implement.
    int score;

public:

    Car(); // car constructor that will initialise a rectangle and array of sensors
    ~Car();

    void draw(sf::RenderWindow&);
    void update();

    //Accel Bloc 
    // void setVel(sf::Vector2f);
    void setAccel();
    void setBrakes();
    void stopAccel();

    //Steer Bloc
    void steerRight();
    void steerLeft();
    void stopSteering();


    sf::RectangleShape getFrame();
    Sensor* getSensor();

    float getAngle();
    void death(bool);

    /* todo
    
    int getScore();

    predict what the car is going to do with his brain and the 
    sensor inputs that will be parsed inside the cars brain 

    */

};