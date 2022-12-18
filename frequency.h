// Frequency class for all types of different frequencies

#ifndef FREQUENCY_H
#define FREQUENCY_H

#include<string>

class Frequency
{
private:
    std::string name; // frequency name
    float lFreq;    // lower bound of the frequency range
    float uFreq;    // upper bound of the frequency range

public:
    Frequency();
    Frequency(const std::string &frqName, float lValue, float uValue);
    std::string getName() const;
    void setName(const std::string &value);
    float getLFreq() const;
    void setLFreq(float value);
    float getUFreq() const;
    void setUFreq(float value);
};

#endif // FREQUENCY_H
