#include "sensor.h"


Sensor::Sensor(){}
Sensor::~Sensor(){}

/*
Function that will calculate the position of the 5 sensors depending on
the center of the car and the angle of the car

return null

*/
void Sensor::setSensorPosition(sf::Vector2f point1, sf::Vector2f vel, float carAngle){

    sensor[0].position = point1; // center of car

    point2.x = point1.x + sensorSize * cos((sensorAngle * M_PI / 180) - (carAngle * M_PI / 180)) ;
    point2.y = point1.y - sensorSize * sin((sensorAngle * M_PI / 180) - (carAngle * M_PI / 180)) ;

    sensor[1].position = point2; // ending point

}

void Sensor::setAngle(float angle){
    sensorAngle = angle;
}

void Sensor::draw(sf::RenderWindow& window){
    window.draw(&sensor[0], 2, sf::Lines);
}

float Sensor::distanceFromWall(){
    return sqrt(pow((sensor[0].position.x - intersectX),2) + pow((sensor[0].position.y - intersectY),2));
}

void Sensor::cast(std::vector<sf::Vertex *> walls, sf::RenderWindow& window, int sensorNum){
    int i = 0,
        j = 1;
    
    auto    closestX = 0,
            closestY = 0;

    auto    record = INFINITY,
            x3 = sensor[0].position.x,
            y3 = sensor[0].position.y,
            x4 = point2.x,
            y4 = point2.y;

    // for(auto i = 0; i < walls.size() ; i++){
    for (int i = 0 ; i < 128; i++ ){
        if( i >= 126){
            break;
        }
        
        if( i >= 62 && i <= 63){
            continue;
        }

        
        auto    x1 = walls[0][i].position.x,
                y1 = walls[0][i].position.y,
                x2 = walls[0][i + 1].position.x,
                y2 = walls[0][i + 1].position.y,
                den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
                

        auto    t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4))/den,
                u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3))/den;
        
        if( t >= 0 && t <= 1 && u >= 0){
            intersectX = (x1 + t * (x2 - x1)),
            intersectY = (y1 + t * (y2 - y1));
            
            auto dist = distanceFromWall();

            if(dist < record and dist < sight){
                record = dist;
                closestX = intersectX;
                closestY = intersectY;
                
            }
        }

    }
    // draws circle at closest intersection points.
    if (closestX != 0 && closestY != 0){
        sf::CircleShape circle(5);
        circle.setOrigin(5,5);
        circle.setPosition(closestX,closestY);
        window.draw(circle);
        
        intersectX = closestX;
        intersectY = closestY;

        // *! this function call slows down the code a lot. it also shouldnt work missing switch case
        // displaySensorInfo(window, positionX, positionY);

    }
}

void Sensor::displaySensorInfo(sf::RenderWindow& window, float positionX, float positionY){
    
    auto sensorDistance = distanceFromWall();

    // display the sensor distance inside the window.
    sf::Font font;
    if(!font.loadFromFile("Fonts/Roboto-Medium.ttf")){
        std::cout<<"error"<<std::endl;
        system("pause");
    }
    sf::Text text;
    text.setFont(font);
    text.setString("Sensor Distance at " + std::to_string((int)sensorAngle) +" degrees : " + std::to_string(sensorDistance));
    text.setPosition({positionX, positionY});
    text.setCharacterSize(14);
    text.setColor(sf::Color::White);
    window.draw(text);

}