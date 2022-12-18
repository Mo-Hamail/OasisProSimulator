#ifndef DB_H
#define DB_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QDateTime>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QList>
#include <QApplication>

#include "user.h"
#include "record.h"
#include "therapy.h"

class db {

public:
    const QString DATE_FORMAT = "yyyy-MM-dd hh:mm";
    static const QString DATABASE_PATH;

    db();
    ~db();
    bool addTherapyRecord(const QString& therapy, const QDateTime& time, int powerLevel, int duration);
    bool addFrequencyRecord(const QString& frequency, const QDateTime& time, int powerLevel, int duration);
    bool addUser(int id, double batterLvl, int powerLvl);
    bool deleteRecords();
    QList<QString>* frequencies();
    QList<therapy*>* therapies();

    user* getUser(int id);
    QVector<record*> getRecordings();


private:
    QSqlDatabase oasisDB;

    bool isValidRecord(const QString& recordType, const QDateTime& time, int powerLevel, int duration);
    bool addRecord(const QString& tableName, const QString& name, const QDateTime& time, int powerLevel, int duration);
    bool DBInit();

};

#endif // #ifndef db_H
