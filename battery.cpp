#include "battery.h"

double Battery::getCharge() const
{
    return charge;
}

void Battery::setCharge(double value)
{
    charge = value;
}

double Battery::getCrLevel() const
{
    return crLevel;
}

void Battery::setCrLevel(double value)
{
    crLevel = value;
}

Battery::Battery()
{
    charge = 100.0; // default battery charge when CES is ON
    crLevel = 10.0; // default critical charge level
}

Battery::Battery(double ch, double crL)
{
    charge = ch;
    crLevel = crL;
}
