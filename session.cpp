#include "session.h"

int Session::getSTime() const
{
    return sTime;
}

void Session::setSTime(int value)
{
    sTime = value;
}

Frequency Session::getSFrequency() const
{
    return sFrequency;
}

void Session::setSFrequency(const Frequency &value)
{
    sFrequency = value;
}

Session::Session()
{

}
Session::Session(int t, Frequency f)
{
    sTime = t;
    sFrequency = f;
}
