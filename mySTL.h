#include <math.h>

namespace NSTL{
    class Perlin{
    private:
        int numberOfOctave = 7;
        double persistence = 0.5;

    public:
        
        Perlin();
        ~Perlin();
        double noise(int, int);
        double smoothedNoise(int, int);
        double Linear_interpolate(double, double, double);
        double interpolatedNoise(double, double);
        double perlinNoise_2D(double, double);

    };
}



