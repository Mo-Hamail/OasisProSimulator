#include "frequency.h"

std::string Frequency::getName() const
{
    return name;
}

void Frequency::setName(const std::string &value)
{
    name = value;
}

float Frequency::getLFreq() const
{
    return lFreq;
}

void Frequency::setLFreq(float value)
{
    lFreq = value;
}

float Frequency::getUFreq() const
{
    return uFreq;
}

void Frequency::setUFreq(float value)
{
    uFreq = value;
}

Frequency::Frequency()
{

}

Frequency::Frequency(const std::string &frqName, float lValue, float uValue)
{
    name = frqName;
    lFreq = lValue;
    uFreq = uValue;
}
