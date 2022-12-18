#include "cesmc.h"
#include <iostream>
CESmc::CESmc(MainWindow* window)
{
    this->window = window;

    battery = Battery();
    intensity = new Intensity(); // default value for any session.
    connection = new Connection(); //default connection value is off
    database = window->getDB();
    power = false; // if device is on or off
    inSession = false; //the session is not running.
    therapyGroup = 0; // how long the session should run for
    therapyType = "";
    maxIntensityLevel = intensity->getMaxIntensity();
}

void CESmc::togglePower(){
    if(power){
        if(inSession){ //if the user is in a session soft off
            currTime = 1; //move time remaining to 1 left.
            softOff(); //soft off the device.
        }
    }else{
        if(battery.getCharge() <= 0.0){
            return;
        }
    }
    power = !power;
}

void CESmc::toggleConnection(){ //toggles the connection on and off
   connection->setStatus(!connection->testConnection());
}


bool CESmc::InitCES()
{
    // CES initialization code under Power button in GUI
    // should be transfered to this method.
    // better not to repeat writing code.
    return true;
}

void CESmc::runSession()
{
    if(runConnectionTest()){
        beginTherapy();
    } else {
        window->navigateBack();
    }
}

bool CESmc::runConnectionTest(){
    /*if(!inSession){ //if the session has started, do not use the UI.
        window->initializeConnectionTestUI(connection->testConnection());
    }*/
    return connection->testConnection();
}

void CESmc::beginTherapy() {
    inSession = true;
    currentTherapy = new therapy(therapyType, therapyGroup, intensity->getIntensity());
    currTime = currentTherapy->getTime();
    timeString = QString::number(currTime/60) + ((currTime%60 < 10) ? + ":0" + QString::number(currTime%60) : + ":" + QString::number(currTime%60));
    //timeString = QString::number(currTime/60) + ":00";
    window->beginTherapyUI(currentTherapy);
    window->initializeTimer(currentTherapy->getTimer());
    record* newR = new record(currentTherapy->getName(), QDateTime::currentDateTime(), 0, 0);
    recordings.append(newR);
    maxIntensityLevel = intensity->getIntensity();
}

void CESmc::changeIntensity(bool state){
    if(state){
        intensity->increaseIntensity();
    } else {
        intensity->decreaseIntensity();
    }
}

void CESmc::updateTimer() {
    if(connection->testConnection()){
        window->drainBattery();
        if (currentTherapy->getTime() == 0) {
            currTime += 1;
        }
        else {
            currTime -= 1;
        }

        timeString = QString::number(currTime/60) + ((currTime%60 < 10) ? + ":0" + QString::number(currTime%60) : + ":" + QString::number(currTime%60));
    }
    if (currTime == 0 && currentTherapy->getTime() != 0) {
        inSession = false;
        //Save record
        recordings.last()->setDuration(currentTherapy->getTime());
        recordings.last()->setPowerLevel(maxIntensityLevel);
        //database->addTherapyRecord(recordings.last()->getTreatment(),recordings.last()->getStartTime(),recordings.last()->getPowerLevel(),recordings.last()->getDuration());
        allRecordings += recordings.last()->toString();
        currTime = -1;
        currentTherapy->getTimer()->stop();
        currentTherapy->getTimer()->disconnect();
        currentTherapy = nullptr;
        window->navigateBack();
    }
}

void CESmc::drainBattery() {
    battery.setCharge(  (intensity->getIntensity() == 0) ? battery.getCharge() - 0.05 : qMax(battery.getCharge() - intensity->getIntensity()/10.0, 0.0)  );
}

void CESmc::softOff(){
    while(getIntensity() > 1){
        QTest::qSleep(250);
        changeIntensity(false);
        window->softOffUpdate();
    }
}

bool CESmc::getPower(){return power;}
int CESmc::getIntensity(){return intensity->getIntensity();}
void CESmc::setTherapyGroup(int i){therapyGroup = i;}
void CESmc::setTherapyType(QString type){therapyType = type;}
QString CESmc::getTherapyType(){return therapyType;}

void CESmc::setBatteryCharge(double newLevel){
    if (newLevel >= 0.0 && newLevel < 100.0) {
        if (newLevel == 0.0 && getPower() == true) {
            togglePower();
            battery.setCharge(0.0);
        }else{
            battery.setCharge(newLevel);
        }
    } else {
        if (getPower() == true) {
            togglePower();
            battery.setCharge(0.0);
           }
    }
}

double CESmc::getBatteryCharge(){return battery.getCharge();}
bool CESmc::getInSession(){return inSession;}
int CESmc::getCurrTime(){return currTime;}
