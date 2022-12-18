#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QVector>
#include <QStringList>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QtTest/QTest>
#include "menu.h"
#include "therapy.h"
#include "db.h"
#include "user.h"
#include "intensity.h"
#include "connection.h"
#include "cesmc.h"

//

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CESmc;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QListWidget *activeQListWidget;
    menu* mainMenu;
    menu* rootMainMenu;

    CESmc* device;

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


    void softOffUpdate();
    void initializeTimer(QTimer*);
    void beginTherapyUI(therapy*);
    void updateTimer();
    void initializeConnectionTestUI(bool);
    void drainBattery();
    void navigateBack();
    void navigateSubMenu();

    db* getDB();

private slots:
    void upButtonClicked();
    void downButtonClicked();
    void powerToggle();
    void endSession();
    void initializeMainMenu(menu *);
    void selectSubmenu();
    void updateMenu(const QString selectedMenuItem, const QStringList menuItems);
    void changeBatteryLevel(double);
    void changeIntensity(int);
    void connectionButtonClicked();

    //tests
    void testBasic();
    void testConnection();
    void testSoftOff();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
