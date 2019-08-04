#include "track.h"



Track::Track() {

    auto offsetX = windowWidth/2;
    auto offsetY = windowHeight/2;
    auto i = 0,
         j = 0;

    sf::Vertex firstPoint;
    sf::Vertex firstPoint2;

    NSTL::Perlin pn;

    for(double a = 0; a < 2 * M_PI; a += 0.1){
        auto xOff = map(cos(a), -1.0, 1.0, 0.0, noiseMax);
        auto yOff = map(sin(a), -1.0, 1.0, 0.0, noiseMax);

        auto r = map((double) pn.perlinNoise_2D(xOff, yOff),  0.0,  1.0,  400.0,  500.0);
        auto x1 = offsetX + r * sin(a),
             y1 = offsetY + r * cos(a),
             x2 = offsetX + (r-100) * sin(a),
             y2 = offsetY + (r-100) * cos(a);
        
        if(a == 0){
            firstPoint.position = {x1, y1}; 
            firstPoint2.position = {x2, y2};
        }

        walls({x1, y1}, i, j, true);
        walls({x2, y2}, 63 + i, j, true);

        walls({x1, y1}, i, j, false);
        walls({x2, y2}, i, j + 1, false);


        i+=1;
        j+=2;
    
    }

    walls(firstPoint.position, 62, j, true);
    walls(firstPoint2.position, 126, j, true);

    circleTrack.push_back(wall);
    vecOfCheckpoints.push_back(checkPoint);

    startingPoint = {150, 600};
    endingPoint = {400, (400 + 350) / 2};

}
Track::~Track() {}

void Track::draw(sf::RenderWindow& window){

    for(auto cp : vecOfCheckpoints){
        window.draw(&cp[0], 127, sf::Lines);
    }

    for(auto it : circleTrack){
        window.draw(&it[0], 127, sf::LinesStrip);
    }
}

void Track::walls(sf::Vector2f pt1, int i, int j, bool check){

    if(check){
        wall[i].position = pt1;
        
    }else {
        checkPoint[j].position = pt1;
        checkPoint[j].color = sf::Color::Transparent;

    }
}


//calculates the line intersection of the rectangle with the walls
//formula used in the line to line intersection page on wikipedia
//returns if the car hits something
bool Track::carHitWall(Car myCar, sf::RenderWindow& window){
    bool hit = false;

    int i = 0,
        j = 1,
        k = 0;

    //4 coordinate to check (corners of the car)
    // we start with the top-left coordinate

    sf::Vector2f pt0 = myCar.getFrame().getTransform().transformPoint({0,0}), //top left
                 pt1 = myCar.getFrame().getTransform().transformPoint({myCar.getFrame().getSize().x,0}), //top right
                 pt3 = myCar.getFrame().getTransform().transformPoint({0,myCar.getFrame().getSize().y}), // bottom left
                 pt2 = myCar.getFrame().getTransform().transformPoint({myCar.getFrame().getSize().x,myCar.getFrame().getSize().y}), //bottom right
                 pt4 = pt0;

    // we input the coordinate of the car in the vector p
    std::vector<sf::Vector2f> p = {pt0, pt1, pt2, pt3, pt4};

    for (int i = 0; i < 128 ; i++){

        if( i >= 126 ){
            break;
        }

        if( i >= 62 && i <= 63){
            continue;
        }

        for(int offset = 0 ; offset < 4 ; offset++){

            auto    A1 = p[k + 1].y - p[k].y,
                    B1 = p[k].x - p[k + 1].x,
                    C1 = A1 * p[k].x + B1 * p[k].y,
                    A2 = circleTrack[0][i+1].position.y - circleTrack[0][i].position.y,
                    B2 = circleTrack[0][i].position.x - circleTrack[0][i+1].position.x,
                    C2 = A2 * circleTrack[0][i].position.x + B2 * circleTrack[0][i].position.y,
                    denominator = A1 * B2 - A2 * B1;

            auto    intersectX = (B2 * C1 - B1 * C2) / denominator,
                    intersectY = (A1 * C2 - A2 * C1) / denominator,
                    rx0 = (intersectX - p[k].x) / (p[k + 1].x - p[k].x),
                    ry0 = (intersectY - p[k].y) / (p[k + 1].y - p[k].y),
                    rx1 = (intersectX - circleTrack[0][i].position.x) / (circleTrack[0][i+1].position.x - circleTrack[0][i].position.x),
                    ry1 = (intersectY - circleTrack[0][i].position.y) / (circleTrack[0][i+1].position.y - circleTrack[0][i].position.y);
            k+=1;

            if( ((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) && 
                ((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1))){
                auto    x = intersectX,
                        y = intersectY;

                hit = true;
                break;
            }
        }

        k = 0;
        if(hit == true){
            break;
        }     

    }

    return hit;
}

std::vector<sf::Vertex *> Track::getVecOfWall(){
    return circleTrack;
}