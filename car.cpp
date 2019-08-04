#include "car.h"

Car::Car() : vel(0, 0), accel(0, 0), origin(carHeight/2, carWidth/2), position(150, 600){

    carSize.x = carHeight;
    carSize.y = carWidth;

    // we set the origin and the size of the car
    carFrame.setOrigin(origin); // car object origin point within the car (not the window origin point)
    carFrame.setPosition(position);// starting point of the car based on origin
    carFrame.setSize(carSize);

    float senseAngle = 0.0;
    for(auto i = 0; i < numberOfSensors; i++){
        carSensor[i].setAngle(senseAngle);
        senseAngle += 180/(numberOfSensors-1);
    }

    std::cout<<"car object created"<<std::endl;
    std::cout<<"car origin :" << carFrame.getOrigin().x<<" : "<< carFrame.getOrigin().y <<std::endl;
    std::cout<<"car position :" << carFrame.getPosition().x<<" : "<< carFrame.getPosition().y<<std::endl;
}

Car::~Car(){}


void Car::draw(sf::RenderWindow& window){
    //draws the car
    window.draw(carFrame);

}

void Car::update(){

    /*
        Updates the position every frame according to velocity and accel 
    */

    position.x -= vel.x * sin(angle * M_PI / 180);//angle in degree
    position.y += vel.y * cos(angle * M_PI / 180);
    vel.x += accel.x;
    vel.y += accel.y;

    //constrains velocity
    vel.x = vel.x > brake ? brake : vel.x;
    vel.x = vel.x < -maxVelocity ? -maxVelocity : vel.x;
    vel.y = vel.y > brake ? brake : vel.y;
    vel.y = vel.y < -maxVelocity ? -maxVelocity : vel.y;

    //constrains position
    position.x = position.x > windowHeight ? windowHeight: position.x;
    position.x = position.x < 0 ? 0 : position.x;
    position.y = position.y > windowWidth ? windowWidth: position.y;
    position.y = position.y < 0 ? 0 : position.y;

    angle += aVel;

    carFrame.setRotation(angle); //angle in radian
    carFrame.setPosition(position);

    for(auto i = 0; i < numberOfSensors; i++){
        carSensor[i].setSensorPosition(carFrame.getPosition(), vel, angle);
    }

}

// void Car::setVel(sf::Vector2f speed){
//     vel = speed;
// }

void Car::steerRight(){
    aVel = maxSteerVel;
}
void Car::steerLeft(){
    aVel = -maxSteerVel;
}
void Car::stopSteering(){
    aVel = 0;
}

void Car::stopAccel(){
    accel = {0, 0};
}

void Car::setAccel(){
    accel = {-acceleration, -acceleration};
}

void Car::setBrakes(){
    accel = {acceleration, acceleration};
}

/*  
    when the car Dies we delete the 
    Car for now i restart it to starting point 
    because easier to test
*/
void Car::death(bool dies){
    position.x = 150;
    position.y = 600;
    
    vel.x = 0;
    vel.y = 0;

    angle = 0;

    carFrame.setRotation(angle);
    carFrame.setPosition(position);
}


sf::RectangleShape Car::getFrame(){
    return carFrame;
}

Sensor* Car::getSensor(){
    return carSensor;
}

float Car::getAngle(){
    return angle;
}

// int Car::getScore(){

// }