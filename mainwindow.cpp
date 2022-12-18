#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    device = new CESmc(this);


    currTime = -1;
    intensity = new Intensity();
    connection = new Connection(); //default connection value is off
    // Create database connection
    database = new db();

    // Create a user Profile
    currUser = database->getUser(1);

    //batteryLevel = 100.0;

    maxIntensityLevel = intensity->getIntensity();

    //connect UI sliders
    connect(ui->batterySlider, &QSlider::valueChanged, this, &MainWindow::changeBatteryLevel);
    ui->batterySlider->setValue(100);
    ui->batteryWarning->setVisible(false);

    mainMenu = new menu("MAIN MENU", {"START NEW SESSION","HISTORY"}, nullptr);
    rootMainMenu = mainMenu;
    initializeMainMenu(mainMenu);

    // Account for device being "off" on sim start
    connect(ui->powerButton, &QPushButton::released, this, &MainWindow::powerToggle);
    //button connections
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::upButtonClicked);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::downButtonClicked);
    connect(ui->selectButton, &QPushButton::pressed, this, &MainWindow::navigateSubMenu);
    connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::navigateBack);
    connect(ui->connectionCheck, &QCheckBox::stateChanged, this, &MainWindow::connectionButtonClicked);
    ui->screen->setVisible(false);

    recordings = database->getRecordings();
    for (int x = 0; x < recordings.size(); x++) {
        allRecordings += recordings[x]->toString();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::beginTherapyUI(therapy* t) {
    //Timer
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->screen->setVisible(true);
    ui->screen->setScene(scene);
    timeString = QString::number(t->getTime()/60) + ":00";
    ui->screen->scene()->addText(timeString)->setDefaultTextColor(Qt::white);
}

void MainWindow::initializeTimer(QTimer* t) {

    connect(t, &QTimer::timeout, this, &MainWindow::updateTimer);
    t->start(1000);

}

void MainWindow::changeBatteryLevel(double newLevel) {

    device->setBatteryCharge(newLevel);
    int newLevelInt = int(newLevel);
    ui->batteryLevelBar->setValue(newLevelInt);

    QString highBatteryHealth = "QProgressBar { selection-background-color: rgb(78, 154, 6); background-color: rgb(0, 0, 0); }";
    QString mediumBatteryHealth = "QProgressBar { selection-background-color: rgb(196, 160, 0); background-color: rgb(0, 0, 0); }";
    QString lowBatteryHealth = "QProgressBar { selection-background-color: rgb(164, 0, 0); background-color: rgb(0, 0, 0); }";

    if (newLevelInt >= 50) {
        ui->batteryLevelBar->setStyleSheet(highBatteryHealth);
    }
    else if (newLevelInt >= 20) {
        ui->batteryLevelBar->setStyleSheet(mediumBatteryHealth);
    }
    else {
        ui->batteryLevelBar->setStyleSheet(lowBatteryHealth);
    }
    if(device->getBatteryCharge() < 20){
        ui->batteryWarning->setVisible(true);
    }else{
        ui->batteryWarning->setVisible(false);
    }
}

void MainWindow::updateTimer() {
    QGraphicsScene* scene = new QGraphicsScene(this);
    device->updateTimer();
    ui->screen->setScene(scene);
    ui->screen->scene()->clear();
    if(!device->getInSession()){ //if the device is no longer in session turn the therapy UI off.
        ui->screen->setVisible(false);
        return;
    }
    int tempCurrTime = device->getCurrTime();
    timeString = QString::number(tempCurrTime/60) + ((tempCurrTime%60 < 10) ? + ":0" + QString::number(tempCurrTime%60) : + ":" + QString::number(tempCurrTime%60));
    ui->screen->scene()->addText(timeString)->setDefaultTextColor(Qt::white);
}

void MainWindow::initializeConnectionTestUI(bool connected){
    ui->screen->scene()->clear();
    if(connected){
        ui->screen->scene()->addText("DEVICE IS CONNECTED")->setDefaultTextColor(Qt::white);
    } else {
        ui->screen->scene()->addText("DEVICE IS NOT CONNECTED")->setDefaultTextColor(Qt::white);
    }
}

void MainWindow::navigateBack() {
    if (!device->getPower()){ //if the device has no power, start at the initial main menu.
        mainMenu = rootMainMenu;
    }
    //if( device->getInSession() ) {return;} //disables navigate back button during a session
    if (currTime != -1){
        //Save recording
        if (mainMenu->getParent()->getName() == "PROGRAMS") {
            recordings.last()->setDuration((currentTherapy->getTime())-currTime);
            recordings.last()->setPowerLevel(maxIntensityLevel);
            //database->addTherapyRecord(recordings.last()->getTreatment(),recordings.last()->getStartTime(),recordings.last()->getPowerLevel(),recordings.last()->getDuration());
        }
        else {
            recordings.last()->setDuration(currTime);
            recordings.last()->setPowerLevel(maxIntensityLevel);
            //database->addFrequencyRecord(recordings.last()->getTreatment(),recordings.last()->getStartTime(),recordings.last()->getPowerLevel(),recordings.last()->getDuration());
        }

        allRecordings += recordings.last()->toString();
        currTime = -1;
        currentTherapy->getTimer()->stop();
        currentTherapy->getTimer()->disconnect();
        currentTherapy = nullptr;
    }

    if (mainMenu->getName() == "MAIN MENU") {
        activeQListWidget->setCurrentRow(0);
    }
    else {
        mainMenu = mainMenu->getParent();
        updateMenu(mainMenu->getName(), mainMenu->getMenuItems());
    }
}

void MainWindow::drainBattery() {
    device->drainBattery();
    changeBatteryLevel(device->getBatteryCharge());
}

void MainWindow::changeIntensity(int i){
    if(i == 1){
        ui->powerLevel1->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel2->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel3->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel4->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel5->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel6->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel7->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel8->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
    }else if(i == 2){
        ui->powerLevel1->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel2->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel3->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel4->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel5->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel6->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel7->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel8->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
    }else if(i == 3){
        ui->powerLevel1->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel2->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel3->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel4->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel5->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel6->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel7->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel8->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
    }else if(i == 4){
        ui->powerLevel1->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel2->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel3->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel4->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel5->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel6->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel7->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel8->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
    }else if(i == 5){
        ui->powerLevel1->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel2->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel3->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel4->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel5->setStyleSheet("QLabel { font-weight: bold; color: orange; font-size: 15pt;}");
        ui->powerLevel6->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel7->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel8->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
    }else if(i == 6){
        ui->powerLevel1->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel2->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel3->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel4->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel5->setStyleSheet("QLabel { font-weight: bold; color: orange; font-size: 15pt;}");
        ui->powerLevel6->setStyleSheet("QLabel { font-weight: bold; color: orange; font-size: 15pt;}");
        ui->powerLevel7->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
        ui->powerLevel8->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
    }else if(i == 7){
        ui->powerLevel1->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel2->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel3->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel4->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel5->setStyleSheet("QLabel { font-weight: bold; color: orange; font-size: 15pt;}");
        ui->powerLevel6->setStyleSheet("QLabel { font-weight: bold; color: orange; font-size: 15pt;}");
        ui->powerLevel7->setStyleSheet("QLabel { font-weight: bold; color: red; font-size: 15pt;}");
        ui->powerLevel8->setStyleSheet("QLabel { font-weight: bold; color: black; font-size: 15pt;}");
    }else{
        ui->powerLevel1->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel2->setStyleSheet("QLabel { font-weight: bold; color: green; font-size: 15pt;}");
        ui->powerLevel3->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel4->setStyleSheet("QLabel { font-weight: bold; color: yellow; font-size: 15pt;}");
        ui->powerLevel5->setStyleSheet("QLabel { font-weight: bold; color: orange; font-size: 15pt;}");
        ui->powerLevel6->setStyleSheet("QLabel { font-weight: bold; color: orange; font-size: 15pt;}");
        ui->powerLevel7->setStyleSheet("QLabel { font-weight: bold; color: red; font-size: 15pt;}");
        ui->powerLevel8->setStyleSheet("QLabel { font-weight: bold; color: red; font-size: 15pt;}");
    }
}

void MainWindow::softOffUpdate(){
    int i = device->getIntensity();
    while(i>0){
        QTest::qSleep(250);
        changeIntensity(i);
        //qInfo("\n\n\nat softoff %d", device->getIntensity());
        ui->powerLevel1->repaint();
        device->changeIntensity(false);
        i--;
    }
}

void MainWindow::powerToggle(){
    //LED painter
    int led_w = ui->LED->width();
    int led_h = ui->LED->height();
    QPixmap LEDpic(":/redSquare.png");
    ui->LED->setPixmap(LEDpic.scaled(led_w,led_h,Qt::KeepAspectRatio));

    device->togglePower();

    if(!device->getPower()){
        if(device->getInSession()){ //soft off only occurs if a session is happening
            softOffUpdate();
        }
        ui->screen->setVisible(false);
        if(ui->screen->scene() != nullptr){ui->screen->scene()->clear();} //prevents a crash from press on and off immediately
        activeQListWidget->clear();
    }else{
        activeQListWidget = ui->mainDisplay;
        activeQListWidget->addItems(mainMenu->getMenuItems());
        activeQListWidget->setCurrentRow(0);
        changeIntensity(device->getIntensity()); //lets you see intensity on power on
    }
    //enable sliders only on power on
    ui->LED->setVisible(device->getPower());
    //ui->powerSlider->setEnabled(power);
    //ui->intensitySlider->setEnabled(power);
    ui->batterySlider->setEnabled(true);
    ui->powerLevel1->setVisible(device->getPower());
    ui->powerLevel2->setVisible(device->getPower());
    ui->powerLevel3->setVisible(device->getPower());
    ui->powerLevel4->setVisible(device->getPower());
    ui->powerLevel5->setVisible(device->getPower());
    ui->powerLevel6->setVisible(device->getPower());
    ui->powerLevel7->setVisible(device->getPower());
    ui->powerLevel8->setVisible(device->getPower());

    QString upButtonOn = "QPushButton { image: url(:/upButton.svg); background-color: white; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";
    QString downButtonOn = "QPushButton { image: url(:/downButton.svg); background-color: white; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";
    QString backButtonOn = "QPushButton { image: url(:/backButton.svg); background-color: white; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";
    QString selectButtonOn = "QPushButton { image: url(:/okButton.svg); background-color: white; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";
    QString powerButtonOn = "QPushButton { image: url(:/powerButton.svg); background-color: white; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";

    QString upButtonOff = "QPushButton { image: url(:/upButton.svg); background-color: black; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";
    QString downButtonOff = "QPushButton { image: url(:/downButton.svg); background-color: black; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";
    QString backButtonOff = "QPushButton { image: url(:/backButton.svg); background-color: black; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";
    QString selectButtonOff = "QPushButton { image: url(:/okButton.svg); background-color: black; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";
    QString powerButtonOff = "QPushButton { image: url(:/powerButton.svg); background-color: black; border-radius: 35px; } QPushButton:pressed { background-color: #ffd300; }";

    //activate buttons
    ui->upButton->setEnabled(device->getPower());
    ui->downButton->setEnabled(device->getPower());
    ui->selectButton->setEnabled(device->getPower());
    ui->backButton->setEnabled(device->getPower());

    //setStylesheets
    if(device->getPower()){
        ui->upButton->setStyleSheet(upButtonOn);
        ui->downButton->setStyleSheet(downButtonOn);
        ui->selectButton->setStyleSheet(selectButtonOn);
        ui->backButton->setStyleSheet(backButtonOn);
        ui->powerButton->setStyleSheet(powerButtonOn);
     }else{
        ui->upButton->setStyleSheet(upButtonOff);
        ui->downButton->setStyleSheet(downButtonOff);
        ui->selectButton->setStyleSheet(selectButtonOff);
        ui->backButton->setStyleSheet(backButtonOff);
        ui->powerButton->setStyleSheet(powerButtonOff);
    }

}

void MainWindow::initializeMainMenu(menu* m) {

    QStringList sessionList = {"20 MIN", "45 MIN", "USER DESIGNATED"};
    QStringList sessionTypeList = {"ALPHA", "BETA", "THETA", "DELTA"};

    menu* groups = new menu("START NEW SESSION", sessionList, m);
    menu* history = new menu("HISTORY", {"VIEW","CLEAR"}, m);
    menu* types = new menu("SESSION TYPES", sessionTypeList, groups);

    m->addChildMenu(groups);
    m->addChildMenu(history);

    for (QString mname : sessionList) { //add session types as a sub menu of the session groups so that it is shown after selecting a group.
        groups->addChildMenu(types);
    }
    for (QString mname : sessionTypeList) { //add session types as a sub menu of the session groups so that it is shown after selecting a group.
        types->addChildMenu(new menu(mname, {}, types));
    }

    //m->addChildMenu(types);


    menu* viewHistory = new menu("VIEW",allRecordings, history);
    menu* clearHistory = new menu("CLEAR", {"YES","NO"}, history);
    history->addChildMenu(viewHistory);
    history->addChildMenu(clearHistory);
}

void MainWindow::upButtonClicked(){
    //qInfo("\n\n\nat upbutton %d", intensity->getIntensity());
    if(ui->screen->isVisible()){
        device->changeIntensity(true);
        changeIntensity(device->getIntensity());
    }else{
        int nextIndex = activeQListWidget->currentRow() - 1;
        if (nextIndex < 0) {
            nextIndex = activeQListWidget->count() - 1;
        }
        activeQListWidget->setCurrentRow(nextIndex);
    }
}

void MainWindow::downButtonClicked(){
    if(ui->screen->isVisible()){
        device->changeIntensity(false);
        changeIntensity(device->getIntensity());
    }else{
        int nextIndex = activeQListWidget->currentRow() + 1;
        if (nextIndex > activeQListWidget->count() - 1) {
            nextIndex = 0;
        }
        activeQListWidget->setCurrentRow(nextIndex);
    }
}

void MainWindow::endSession(){

}

void MainWindow::connectionButtonClicked(){ //if you turn the device back on while connection is off the screen does not load.
    device->toggleConnection();
}

void MainWindow::selectSubmenu() {
    int index = activeQListWidget->currentRow();
    if (index < 0) return;
    if (mainMenu->getName() == "VIEW") {
        return;
    }
    if (mainMenu->getName() == "CLEAR") {
        if (mainMenu->getMenuItems()[index] == "YES") {
        }
    }
    if (mainMenu->get(index)->getMenuItems().length() > 0) {
        mainMenu = mainMenu->get(index);
        MainWindow::updateMenu(mainMenu->getName(), mainMenu->getMenuItems());
    }
    else if (mainMenu->get(index)->getName() == "VIEW") {
        mainMenu = mainMenu->get(index);
    }
}

void MainWindow::navigateSubMenu() {

    int index = activeQListWidget->currentRow();
    if (index < 0) return;

    // Select Therapy Options
    if (mainMenu->getName() == "START NEW SESSION") { //stores the user selection for group in an int that shows the amount of time requested ("20 MIN" -> 20)
        QString therapyGroupString = mainMenu->getMenuItems()[index];
        QList<int> relatedTimes = {20, 45};
        if(therapyGroupString != "USER DESIGNATED"){
            device->setTherapyGroup(relatedTimes[index]);
        } else {device->setTherapyGroup(0);}
    }
    else if (mainMenu->getName() == "SESSION TYPES") { device->setTherapyType(mainMenu->getMenuItems()[index]);} //stores user selection for session type (ALPHA, BETA, etc...)

    if (mainMenu->getName() == "CLEAR") {
        if (mainMenu->getMenuItems()[index] == "YES") {
            //database->deleteRecords();
            allRecordings.clear();

            for (int x = 0; x < recordings.size(); x++) {
                delete recordings[x];
            }
            recordings.clear();
            navigateBack();
            return;
        }
        else {
            navigateBack();
            return;
        }
    }

    //If the menu is a parent and clicking on it should display more menus.
    if (mainMenu->get(index)->getMenuItems().length() > 0) {
        mainMenu = mainMenu->get(index);
        MainWindow::updateMenu(mainMenu->getName(), mainMenu->getMenuItems());
    }
    //If the menu is not a parent and clicking on it should start a therapy
    else if (mainMenu->get(index)->getMenuItems().length() == 0 && (mainMenu->getName() == "SESSION TYPES")) {
        if (mainMenu->getName() == "SESSION TYPES") {
            mainMenu = mainMenu->get(index);
            MainWindow::updateMenu(device->getTherapyType(), {});
            device->runSession();
        }
    }
    //If the button pressed should display the device's recordings.
    else if (mainMenu->get(index)->getName() == "VIEW") {
        mainMenu = mainMenu->get(index);
        MainWindow::updateMenu("RECORDINGS", allRecordings);
    }
}

void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems) {
    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);
}

db* MainWindow::getDB(){ return this->database; }

//tests

int powerButtonX = 510;
int powerButtonY = 300;
QPoint pressPower = QPoint(powerButtonX, powerButtonY);

int selectButtonX = 630;
int selectButtonY = 90;
QPoint pressOK = QPoint(selectButtonX, selectButtonY);

int upButtonX = 540;
int upButtonY = 90;
QPoint pressUp = QPoint(upButtonX, upButtonY);

int downButtonX = 540;
int downButtonY = 90;
QPoint pressDown = QPoint(downButtonX, downButtonY);

void MainWindow::testBasic(){
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressPower, 100); //turn on the device
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "start a new session"
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "20 mins"
    ui->connectionCheck->setChecked(true);
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "alpha"
    QCOMPARE(ui->screen->isVisible(), true);
}

void MainWindow::testConnection(){
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressPower, 100); //turn on the device
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "start a new session"
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "20 mins"
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "alpha"
    QCOMPARE(ui->screen->isVisible(), false); //make certain user can't start unless device is connected
    ui->connectionCheck->setChecked(true);
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "alpha"
    QCOMPARE(ui->screen->isVisible(), true);
}

void MainWindow::testSoftOff(){
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressPower, 100); //turn on the device
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "start a new session"
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "20 mins"
    ui->connectionCheck->setChecked(true);
    QTest::mouseClick (this, Qt::LeftButton, Qt::NoModifier, pressOK, 100); //select "alpha"
    ui->batterySlider->setValue(0); //set battery to zero to turn off
    QCOMPARE(intensity->getIntensity(), 0);
}
