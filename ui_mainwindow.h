/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *powerButton;
    QPushButton *downButton;
    QPushButton *upButton;
    QLabel *label;
    QLabel *canada;
    QPushButton *selectButton;
    QPushButton *backButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *intensityBar;
    QLabel *powerLevel8;
    QLabel *powerLevel7;
    QLabel *powerLevel6;
    QLabel *powerLevel5;
    QLabel *powerLevel4;
    QLabel *powerLevel3;
    QLabel *powerLevel2;
    QLabel *powerLevel1;
    QListWidget *mainDisplay;
    QLabel *LED;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QSlider *batterySlider;
    QLabel *batteryLabel;
    QProgressBar *batteryLevelBar;
    QCheckBox *connectionCheck;
    QSpacerItem *verticalSpacer;
    QGraphicsView *screen;
    QLabel *batteryWarning;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background-color: black;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background-color: black;\n"
"}"));
        powerButton = new QPushButton(centralwidget);
        powerButton->setObjectName(QString::fromUtf8("powerButton"));
        powerButton->setGeometry(QRect(510, 300, 71, 71));
        powerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/powerButton.svg);\n"
"background-color: black;\n"
"border-radius: 35px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #ffd300;\n"
"}"));
        downButton = new QPushButton(centralwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setGeometry(QRect(540, 190, 71, 71));
        downButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/downButton.svg);\n"
"background-color: black;\n"
"border-radius: 35px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #ffd300;\n"
"}"));
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setGeometry(QRect(540, 90, 71, 71));
        upButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/upButton.svg);\n"
"background-color: black;\n"
"border-radius: 35px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #ffd300;\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(620, 300, 111, 31));
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: white;\n"
"	font-size: 15pt;\n"
"}"));
        canada = new QLabel(centralwidget);
        canada->setObjectName(QString::fromUtf8("canada"));
        canada->setGeometry(QRect(620, 360, 111, 31));
        canada->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: white;\n"
"	font-size: 15pt;\n"
"}"));
        selectButton = new QPushButton(centralwidget);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        selectButton->setGeometry(QRect(630, 90, 71, 71));
        selectButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/okButton.svg);\n"
"background-color: black;\n"
"border-radius: 35px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #ffd300;\n"
"}"));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(630, 190, 71, 71));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"image: url(:/backButton.svg);\n"
"background-color: black;\n"
"border-radius: 35px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: #ffd300;\n"
"}"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 130, 381, 321));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        intensityBar = new QVBoxLayout();
        intensityBar->setObjectName(QString::fromUtf8("intensityBar"));
        powerLevel8 = new QLabel(layoutWidget);
        powerLevel8->setObjectName(QString::fromUtf8("powerLevel8"));
        powerLevel8->setMinimumSize(QSize(40, 20));
        powerLevel8->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: black;\n"
"	font-style: bold;\n"
"	font-size: 15pt;\n"
"}"));

        intensityBar->addWidget(powerLevel8);

        powerLevel7 = new QLabel(layoutWidget);
        powerLevel7->setObjectName(QString::fromUtf8("powerLevel7"));
        powerLevel7->setMinimumSize(QSize(40, 20));
        powerLevel7->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: black;\n"
"	font-style: bold;\n"
"	font-size: 15pt;\n"
"}"));

        intensityBar->addWidget(powerLevel7);

        powerLevel6 = new QLabel(layoutWidget);
        powerLevel6->setObjectName(QString::fromUtf8("powerLevel6"));
        powerLevel6->setMinimumSize(QSize(40, 20));
        powerLevel6->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: black;\n"
"	font-style: bold;\n"
"	font-size: 15pt;\n"
"}"));

        intensityBar->addWidget(powerLevel6);

        powerLevel5 = new QLabel(layoutWidget);
        powerLevel5->setObjectName(QString::fromUtf8("powerLevel5"));
        powerLevel5->setMinimumSize(QSize(40, 20));
        powerLevel5->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: black;\n"
"	font-style: bold;\n"
"	font-size: 15pt;\n"
"}"));

        intensityBar->addWidget(powerLevel5);

        powerLevel4 = new QLabel(layoutWidget);
        powerLevel4->setObjectName(QString::fromUtf8("powerLevel4"));
        powerLevel4->setMinimumSize(QSize(40, 20));
        powerLevel4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: black;\n"
"	font-style: bold;\n"
"	font-size: 15pt;\n"
"}"));

        intensityBar->addWidget(powerLevel4);

        powerLevel3 = new QLabel(layoutWidget);
        powerLevel3->setObjectName(QString::fromUtf8("powerLevel3"));
        powerLevel3->setMinimumSize(QSize(40, 20));
        powerLevel3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: black;\n"
"	font-style: bold;\n"
"	font-size: 15pt;\n"
"}"));

        intensityBar->addWidget(powerLevel3);

        powerLevel2 = new QLabel(layoutWidget);
        powerLevel2->setObjectName(QString::fromUtf8("powerLevel2"));
        powerLevel2->setMinimumSize(QSize(40, 20));
        powerLevel2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: black;\n"
"	font-style: bold;\n"
"	font-size: 15pt;\n"
"}"));

        intensityBar->addWidget(powerLevel2);

        powerLevel1 = new QLabel(layoutWidget);
        powerLevel1->setObjectName(QString::fromUtf8("powerLevel1"));
        powerLevel1->setMinimumSize(QSize(40, 20));
        powerLevel1->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: black;\n"
"	font-style: bold;\n"
"	font-size: 15pt;\n"
"}"));

        intensityBar->addWidget(powerLevel1);


        horizontalLayout->addLayout(intensityBar);

        mainDisplay = new QListWidget(layoutWidget);
        mainDisplay->setObjectName(QString::fromUtf8("mainDisplay"));
        mainDisplay->setStyleSheet(QString::fromUtf8("QListWidget{\n"
"	color:white;\n"
"	font-size: 15pt;\n"
"}"));

        horizontalLayout->addWidget(mainDisplay);

        LED = new QLabel(centralwidget);
        LED->setObjectName(QString::fromUtf8("LED"));
        LED->setGeometry(QRect(530, 400, 21, 21));
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(790, 120, 381, 321));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        batterySlider = new QSlider(layoutWidget1);
        batterySlider->setObjectName(QString::fromUtf8("batterySlider"));
        batterySlider->setStyleSheet(QString::fromUtf8("QSlider{\n"
"	background-color: black;\n"
"}\n"
"\n"
"QSlider::handle{\n"
"	background-color: black;\n"
"	border: 1px solid white;\n"
"}"));
        batterySlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(batterySlider, 1, 2, 1, 1);

        batteryLabel = new QLabel(layoutWidget1);
        batteryLabel->setObjectName(QString::fromUtf8("batteryLabel"));
        batteryLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: white;\n"
"	font-size: 15pt;\n"
"}"));

        gridLayout->addWidget(batteryLabel, 1, 0, 1, 1);

        batteryLevelBar = new QProgressBar(layoutWidget1);
        batteryLevelBar->setObjectName(QString::fromUtf8("batteryLevelBar"));
        batteryLevelBar->setValue(0);

        gridLayout->addWidget(batteryLevelBar, 3, 2, 1, 1);

        connectionCheck = new QCheckBox(layoutWidget1);
        connectionCheck->setObjectName(QString::fromUtf8("connectionCheck"));
        connectionCheck->setStyleSheet(QString::fromUtf8("QCheckBox{\n"
"	background-color: black;\n"
"	font-size: 15pt;\n"
"	color: white;\n"
"}\n"
"\n"
"QCheckBox::indicator{\n"
"	border: 1px solid white;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked{\n"
"	background-color: white;\n"
"}"));
        connectionCheck->setTristate(false);

        gridLayout->addWidget(connectionCheck, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        screen = new QGraphicsView(centralwidget);
        screen->setObjectName(QString::fromUtf8("screen"));
        screen->setEnabled(true);
        screen->setGeometry(QRect(131, 130, 341, 321));
        batteryWarning = new QLabel(centralwidget);
        batteryWarning->setObjectName(QString::fromUtf8("batteryWarning"));
        batteryWarning->setGeometry(QRect(840, 450, 277, 37));
        batteryWarning->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font-size: 20pt;\n"
"	color: red;\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(batterySlider, SIGNAL(valueChanged(int)), batteryLevelBar, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        powerButton->setText(QString());
        downButton->setText(QString());
        upButton->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Oasis Pro", nullptr));
        canada->setText(QApplication::translate("MainWindow", "Canada", nullptr));
        selectButton->setText(QString());
        backButton->setText(QString());
        powerLevel8->setText(QApplication::translate("MainWindow", "-8-", nullptr));
        powerLevel7->setText(QApplication::translate("MainWindow", "-7-", nullptr));
        powerLevel6->setText(QApplication::translate("MainWindow", "-6-", nullptr));
        powerLevel5->setText(QApplication::translate("MainWindow", "-5-", nullptr));
        powerLevel4->setText(QApplication::translate("MainWindow", "-4-", nullptr));
        powerLevel3->setText(QApplication::translate("MainWindow", "-3-", nullptr));
        powerLevel2->setText(QApplication::translate("MainWindow", "-2-", nullptr));
        powerLevel1->setText(QApplication::translate("MainWindow", "-1-", nullptr));
        LED->setText(QString());
        batteryLabel->setText(QApplication::translate("MainWindow", "Battery", nullptr));
        connectionCheck->setText(QApplication::translate("MainWindow", "Connection Status", nullptr));
        batteryWarning->setText(QApplication::translate("MainWindow", "LOW BATTERY", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
