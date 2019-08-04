#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class Sensor{
    private:
        sf::Vertex sensor[2];
        sf::Vector2f point2 = {0, 0};

        float intersectX = 0.0;
        float intersectY = 0.0;
        float sensorAngle = 0.0;
        int sight = 50;

        const int sensorSize = 50;
    
    public:
        Sensor();
        ~Sensor();
        
        void setSensorPosition(sf::Vector2f, sf::Vector2f, float); // update sensor position.
        void setAngle(float); // set angle of the sensors ont the car

        void draw(sf::RenderWindow&);// draw the sensors
        void cast(std::vector<sf::Vertex *>, sf::RenderWindow&, int);// Updates position from wall

        float distanceFromWall(); // returns the euclidean distance of the wall from the car center (coincides with sensor pt1);
        void displaySensorInfo(sf::RenderWindow&, float, float);

};