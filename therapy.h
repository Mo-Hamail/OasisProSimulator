#ifndef THERAPY_H
#define THERAPY_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDateTime>

// therapy object to be stored

class therapy: public QObject {

    Q_OBJECT

    public:
        therapy(QString therapyName, int t, int intensity);
        ~therapy();
        QString getName();
        int getTime();
        int getIntensity();
        QTimer* getTimer();

    private:
        int time;
        QString therapyName;
        QTimer* timer;
        int intensity;

};

#endif // therapy_H
