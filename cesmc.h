#ifndef CESMC_H
#define CESMC_H

#include<battery.h>
#include <QListWidget>
#include <QVector>
#include <QStringList>
#include <QtTest/QTest>
#include "menu.h"
#include "therapy.h"
#include "db.h"
#include "user.h"
#include "intensity.h"
#include "connection.h"
#include "cesmc.h"
#include "mainwindow.h"

class MainWindow;

class CESmc
{
private:
    bool power; // machine on/off (true/false)

public:
    //Session mcSession;  // machine current session chosen

    MainWindow* window; //device can tell main window to update.

    Battery battery; // machine battery
    QVector<therapy*> programs;
    QVector<therapy*> frequencies;
    QVector<record*> recordings;
    QStringList allRecordings;
    therapy* currentTherapy;
    db* database;
    user* currUser;
    Intensity* intensity;
    Connection* connection;
    int currTime;
    QString timeString; //format the time for display
    int maxIntensityLevel; //max power according to user profile
    double batteryLevel; //battery power remaining in device
    int therapyGroup; // how long the session should run for
    QString therapyType;
    bool inSession;

    CESmc(MainWindow*);

    void togglePower(); //turn power on or off depending on what state it is currently in.
    void toggleConnection();
    bool InitCES(); // initialize CES after power ON
    void runSession(); // run session after selection
    bool runConnectionTest();
    void beginTherapy();
    void initializeTimer(QTimer*);
    void changeIntensity(bool); //if true intensity up, false down

    void updateTimer();
    void drainBattery();
    void softOff();

    bool getPower();
    int getIntensity(); //for displaying intensity
    void setTherapyGroup(int); //allows UI to set the group and type of therapy
    void setTherapyType(QString);
    QString getTherapyType(); //allows UI to display therapy type name
    void setBatteryCharge(double); //allows UI to change the battery charge
    double getBatteryCharge();
    bool getInSession();
    int getCurrTime();
};

#endif // CESMC_H
