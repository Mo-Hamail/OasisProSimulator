// Battery Class conatins all Battery information.

#ifndef BATTERY_H
#define BATTERY_H


class Battery
{
private:
    double charge; // charge level in battery
    double crLevel; // critical level of battery charge
                 // that should the battery replaced at
public:
    Battery();
    Battery(double ch, double crL);
    double getCharge() const;
    void setCharge(double value);
    double getCrLevel() const;
    void setCrLevel(double value);
};

#endif // BATTERY_H
