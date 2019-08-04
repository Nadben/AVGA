#include "mySTL.h"


NSTL::Perlin::Perlin(){}
NSTL::Perlin::~Perlin(){}


double NSTL::Perlin::noise(int x, int y){
    int n = x + y * 57;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double NSTL::Perlin::smoothedNoise(int x, int y){
    auto corners = ( noise(x-1, y-1) + noise(x+1, y-1) + noise(x-1, y+1) + noise(x+1, y+1) ) / 16;
    auto sides = ( noise(x-1 , y) + noise(x+1, y) + noise(x, y-1) + noise(x, y+1))/8;
    auto center = noise(x, y)/4;
    return corners + sides + center;
}

double NSTL::Perlin::Linear_interpolate(double a, double b, double x){
    return a * (1 - x) + b * x;
}


double NSTL::Perlin::interpolatedNoise(double x, double y){
    int integerX = int(x);
    auto fractionalX = x - integerX;
    int integerY = int(y);
    auto fractionalY = y - integerY;    

    auto    v1 = smoothedNoise(integerX, integerY),
            v2 = smoothedNoise(integerX + 1, integerY),
            v3 = smoothedNoise(integerX, integerY +1),
            v4 = smoothedNoise(integerX + 1, integerY + 1);

    auto    i1 = Linear_interpolate(v1, v2, fractionalX),
            i2 = Linear_interpolate(v3, v4, fractionalX);

    return Linear_interpolate(i1, i2, fractionalY);

}

double NSTL::Perlin::perlinNoise_2D(double x, double y){
    double total = 0;
    double p = persistence;
    double n = numberOfOctave - 1;

    for( auto i = 0; i < n; i++){
        auto frequency = pow(2, i);
        auto amplitude = pow(p, i);
        total += interpolatedNoise(x * frequency, y * frequency)* amplitude;
    }

    return total;
}