#include "record.h"

record::record(const QString& treatment, const QDateTime& startTime, const int powerLevel, const int duration) {
    if (startTime.isValid()) {
        this->treatment = treatment;
        this->startTime = startTime;
        this->powerLevel = powerLevel;
        this->duration = duration;
    }
}


QString record::toString() { //format records into QStrings for display
    QString newString =
            startTime.toString("ddd h:mm ap") + "\n"
            + "   Therapy: " + treatment + "\n"
            + "   Power Level: " + QString::number(powerLevel) + "\n"
            + "   Duration: " + QString::number(duration/60) + ((duration%60 < 10) ? + ":0" + QString::number(duration%60) : + ":" + QString::number(duration%60));
    return newString;
}


// getters
QString record::getTreatment() { return treatment; }
QDateTime record::getStartTime() { return startTime; }
int record::getPowerLevel() { return powerLevel; }
int record::getDuration() { return duration; }


// setters
void record::setPowerLevel(int p) { powerLevel = p; }
void record::setDuration(int d) { duration = d; }
