#include "intensity.h"

Intensity::Intensity()
{
    minIntensity = MININTENS;
    maxIntensity = MAXINTENS;
    intensity    = 1;
}
Intensity::Intensity(int min, int max)
{
    minIntensity = min;
    maxIntensity = max;
    intensity    = 1;
}
void Intensity::setDefaultIntensity(int defaultIntens)
{
    intensity = defaultIntens;
}
int Intensity::increaseIntensity()
{
    if(intensity < maxIntensity)
        intensity++;
    return intensity;
}
int Intensity::decreaseIntensity()
{
    if(intensity > minIntensity)
        intensity--;
    return intensity;
}
int  Intensity::getIntensity()
{
    return intensity;
}
int  Intensity::getMinIntensity()
{
    return minIntensity;
}
int  Intensity::getMaxIntensity()
{
    return maxIntensity;
}
