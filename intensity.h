#ifndef INTENSITY_H
#define INTENSITY_H

#define MININTENS 1
#define MAXINTENS 8

class Intensity
{
private:
    int minIntensity;
    int maxIntensity;
    int intensity;
public:
    Intensity();
    Intensity(int, int);
    void setDefaultIntensity(int);
    int increaseIntensity();
    int decreaseIntensity();
    int getIntensity();
    int getMinIntensity();
    int getMaxIntensity();


};

#endif // INTENSITY_H
