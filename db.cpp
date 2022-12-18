#include "db.h"



const QString db::DATABASE_PATH = "/database/oasis.db";


/*
 * Create a new db to a existing oasis database, defined by db::DATABASE_PATH
 *
 * Throws:
 *  If the database could not be opened
 */
db::db() {

    oasisDB = QSqlDatabase::addDatabase("QSQLITE");
    oasisDB.setDatabaseName("oasis.db");

    if (!oasisDB.open()) {
        throw "Error: Database could not be opened";
    }

    if (!DBInit()) {
        throw "Error: Database could not be initialized";
    }
}


bool db::DBInit() {

    oasisDB.transaction();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ( pid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT, battery_level REAL NOT NULL, power_level INTEGER NOT NULL);");
    query.exec("CREATE TABLE IF NOT EXISTS frequencies ( name TEXT NOT NULL UNIQUE PRIMARY KEY);");
    query.exec("CREATE TABLE IF NOT EXISTS therapies  ( name TEXT NOT NULL UNIQUE PRIMARY KEY,  frequency TEXT NOT NULL REFERENCES frequencies, duration INTEGER NOT NULL);");
    query.exec("CREATE TABLE IF NOT EXISTS records ( rid INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,date TEXT NOT NULL,power_level INTEGER NOT NULL,duration INTEGER NOT NULL);");
    query.exec("CREATE TABLE IF NOT EXISTS therapy_records(name TEXT NOT NULL REFERENCES therapies,tid INTEGER NOT NULL REFERENCES records(rid) ON DELETE CASCADE, PRIMARY KEY (name, tid));");
    query.exec("CREATE TABLE IF NOT EXISTS frequency_records( name TEXT NOT NULL REFERENCES frequencies,fid INTEGER NOT NULL REFERENCES records(rid) ON DELETE CASCADE,PRIMARY KEY (name, fid));");

    // initialize device
    query.exec("INSERT OR REPLACE INTO frequencies VALUES ('10Hz'),('20Hz'),('60Hz'),('200Hz'),('7710');");
    query.exec("INSERT OR REPLACE INTO therapies VALUES('PAIN', '10Hz', 900),('GYNECOLOGIC PAIN', '7710', 900),('POTENCY', '60Hz', 900),('HEAD', '60Hz', 300);");

    return oasisDB.commit();
}


user* db::getUser(int id) {

    oasisDB.transaction();

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE pid=:pid");
    query.bindValue(":pid", id);
    query.exec();

    if (!oasisDB.commit()) {
        throw "Error: Query failed to execute";
    }

   // user does not exist
    if (!query.next()) {
        addUser(id, 100.0, 1);
        user* pro = new user(id, 100, 0);
        return pro;
    }

    // user exists
    user* pro = new user(query.value(0).toInt(), query.value(1).toDouble(), query.value(2).toInt());
    return pro;
}


QVector<record*> db::getRecordings() {

    QSqlQuery query;
    QVector<record*> qvr;
    oasisDB.transaction();

    query.prepare("SELECT name as treatment,date,power_level,duration FROM ( SELECT name as name,tid as rid FROM therapy_records UNION SELECT name as name,fid as rid FROM frequency_records ) NATURAL JOIN records ORDER BY rid;");
    query.exec();

    while (query.next()) {
        QString name = query.value(0).toString();
        QDateTime start = QDateTime::fromString(query.value(1).toString(), DATE_FORMAT);
        int power = query.value(2).toString().toInt();
        int duration = query.value(3).toString().toInt();
        record* r = new record(name, start, power, duration);
        qvr.push_back(r);
    }
    return qvr;
}


bool db::addUser(int id, double batteryLvl, int powerLvl) {

    oasisDB.transaction();

    QSqlQuery query;
    //query.prepare("INSERT OR REPLACE INTO users (pid, battery_level, power_level) VALUES (:pid, :battery_level, :power_level);");
    query.prepare("REPLACE INTO users (pid, battery_level, power_level) VALUES (:pid, :battery_level, :power_level);");
    query.bindValue(":pid", id);
    query.bindValue(":battery_level", batteryLvl);
    query.bindValue(":power_level", powerLvl);
    query.exec();

    return oasisDB.commit();
}


/*
 * Type: Public
 * Adds a therapy record to the database, if the arguments are valid.
 *
 * Parameters:
 *  therapy - the name of the therapy to add to the records, must be capitalized and in the database already
 *  time - the time the therapy started in QDateTime format
 *  powerLevel - the maximum power level observed during a therapy
 *  duration - the amount of time in seconds that the therapy was in use
 *
 * Returns:
 *  True - If the record was successfully added to the database
 *  False - If the arguments were invalid, or if the record couldn't be added to the database
 */
bool db::addTherapyRecord(const QString& therapy, const QDateTime& time, int powerLevel, int duration) {

    if (!isValidRecord("therapy", time, powerLevel, duration)) {
        return false;
    }
    return addRecord("therapy", therapy, time, powerLevel, duration);
}


/*
 * Type: Public
 * Adds a frequency record to the database, if the arguments are valid.
 *
 * Parameters:
 *  frequency - the name of the frequency to add to the records, must be in the database already
 *  time - the time the frequency treatment started in QDateTime format
 *  powerLevel - the maximum power level observed during a frequency treatment
 *  duration - the amount of time in seconds that the frequency treatment was in use
 *
 * Returns:
 *  True - If the record was successfully added to the database
 *  False - If the arguments were invalid, or if the record couldn't be added to the database
 */
bool db::addFrequencyRecord(const QString& frequency, const QDateTime& time, int powerLevel, int duration) {
    if (!isValidRecord("frequency", time, powerLevel, duration)) {
        return false;
    }
    return addRecord("frequency", frequency, time, powerLevel, duration);
}


/*
 * Type: Public
 * Deletes all records from the database.
 *
 * Returns:
 *  True - If the records were successfully removed from the database
 *  False - If the records couldn't be deleted from the database
 */
bool db::deleteRecords() {

    QSqlQuery query;
    query.prepare("DELETE FROM records");
    query.exec();
    query.prepare("DELETE FROM therapy_records");
    query.exec();
    query.prepare("DELETE FROM frequency_records");
    return query.exec();
}


QList<QString>* db::frequencies() {

    QList<QString>* frequencies = new QList<QString>;

    QSqlQuery query;
    query.exec("SELECT * FROM FREQUENCIES");
    while (query.next()) {
        frequencies->append(query.value(0).toString());
    }
    return frequencies;
}


QList<therapy*>* db::therapies() {
/*
    QList<therapy*>* therapies = new QList<therapy*>;

    QSqlQuery query;
    query.exec("SELECT * FROM therapies");
    while (query.next()) {
        therapy* t = new therapy(query.value(0).toString(), query.value(2).toInt(), query.value(1).toString());
        therapies->append(t);
    }
    return therapies;*/
}


/*
 * Type: Private
 * Validates the given parameters.
 *
 * Parameters:
 *  recordType - The type of record, used only for debugging
 *  time - the time the treatment started in QDateTime format
 *  powerLevel - the maximum power level observed during a treatment
 *  duration - the amount of time in milliseconds that the treatment was in use
 *
 * Returns:
 *  True - If the parameters are acceptable
 *  False - Otherwise
 *
 * See Also:
 *  db::addTherapyrecord
 *  db::addFrequencyrecord
 */
bool db::isValidRecord(const QString& recordType, const QDateTime& time, int powerLevel, int duration) {

    bool valid = true;
    if (!time.isValid()) {
        qDebug() << "Error: Cannot add " << recordType << " record, time is not valid";
        valid = false;
    }
    else if (powerLevel < 0 || powerLevel > 100) {
        qDebug() << "Error: Cannot add " << recordType << " record, power level is not valid";
        valid = false;
    }
    else if (duration < 0) {
        qDebug() << "Error: Cannot add " << recordType << " record, duration is not valid";
        valid = false;
    }
    return valid;
}


/*
 * Type: Private
 * Adds a treatment record to the database.
 *
 * Parameters:
 *  tableName - The database table to insert this record into
 *  name - The name of the frequency or therapy
 *  time - the time the treatment started in QDateTime format
 *  powerLevel - the maximum power level observed during a treatment
 *  duration - the amount of time in milliseconds that the treatment was in use
 *
 * Returns:
 *  True - If the record was added successfully
 *  False - Otherwise
 *
 * See Also:
 *  db::addTherapyrecord
 *  db::addFrequencyrecord
 */
bool db::addRecord(const QString& tableName, const QString& name, const QDateTime& time, int powerLevel, int duration) {

    oasisDB.transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO records (date, power_level, duration) VALUES (:date, :power_level, :duration);");
    query.bindValue(":date", time.toString(DATE_FORMAT));
    query.bindValue(":power_level", powerLevel);
    query.bindValue(":duration", duration);
    query.exec();

    int rowid = query.lastInsertId().toInt();
    query.prepare("INSERT INTO " + tableName + "_records VALUES (:name, :id);");
    query.bindValue(":name", name);
    query.bindValue(":id", rowid);
    query.exec();

    return oasisDB.commit();
}
