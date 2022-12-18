#include "therapy.h"

therapy::therapy(QString name, int t, int inten) {

    therapyName = name;
    intensity = inten;
    time = t;

    timer = new QTimer(this);
}


therapy::~therapy() {
    delete timer;
}

// getters
QString therapy::getName() { return therapyName; }
int therapy::getTime() { return time; }
int therapy::getIntensity() { return intensity; }
QTimer* therapy:: getTimer() { return timer; }
