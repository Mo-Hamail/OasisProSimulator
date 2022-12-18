#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDateTime>
#include <QTime>

//record to display user history

class record {

public:
    record(const QString& treatment, const QDateTime& startTime, const int powerLevel, const int duration);
    void setPowerLevel(int p);
    void setDuration(int duration);

    QString toString();
    QString getTreatment();
    QDateTime getStartTime();
    int getPowerLevel();
    int getDuration();

private:
    QString treatment;
    QDateTime startTime;
    int powerLevel;
    int duration;

};

#endif // record_H
