#include "user.h"

user::user(int id, double batteryLvl, int powerLvl) {

    this->id = id;
    //this->batteryLvl = batteryLvl;
    this->powerLvl = powerLvl;
}


// getters
int user::getId() { return id; }
//double user::getBLvl() { return batteryLvl; }
int user::getPLvl() { return powerLvl; }

// setters
//void user::setBLvl(double newLvl) { batteryLvl = newLvl; }
void user::setPLvl(int newLvl) { powerLvl = newLvl; }
