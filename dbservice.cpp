#include "dbservice.h"

DbService::DbService()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if (db.lastError().isValid())
    {
        qCritical() << "addDatabase" << db.lastError().text();
        return;
    }

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataLocation);
    if (!dir.exists())
    {
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }

    QString dbPath = appDataLocation + "/data.db";

    db.setDatabaseName(dbPath);
    if (!db.open())
    {
        qCritical() << "unable to open db" << db.lastError().text() << dbPath;
    }

    tablesCreation();
}

void DbService::tablesCreation()
{
    QSqlQuery createTableUsers("CREATE TABLE IF NOT EXISTS Users("
                               "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                               "name STRING NOT NULL UNIQUE)");
    createTableUsers.exec();

    QSqlQuery createTableProducts("CREATE TABLE IF NOT EXISTS Products("
                                  "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                  "name STRING NOT NULL UNIQUE)");
    createTableProducts.exec();


    QSqlQuery createTableActions("CREATE TABLE IF NOT EXISTS Actions("
                                 "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                 "name STRING NOT NULL UNIQUE)");
    createTableActions.exec();

    QSqlQuery createTableActivities("CREATE TABLE IF NOT EXISTS Activities("
                                    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                    "userID INT NOT NULL REFERENCES Users(ID),"
                                    "productID INT NOT NULL REFERENCES Products(ID),"
                                    "actionID INT NOT NULL REFERENCES Actions(ID),"
                                    "date DATE DEFAULT CURRENT_DATE,"
                                    "startTime TIME NOT NULL,"
                                    "endTime TIME NOT NULL,"
                                    "quantity FLOAT)");
    createTableActivities.exec();

    QSqlQuery alterTableActivities("ALTER TABLE Activities ADD quantity FLOAT");
    alterTableActivities.exec();
}


std::vector<Activity> DbService::getActivities(QString user, QDate date)
{
    QSqlQuery query;
    query.prepare("SELECT Activities.ID,startTime,endTime,Products.name,Actions.name,quantity FROM Activities"
                  " JOIN Users ON userID=Users.ID"
                  " JOIN Products ON productID=Products.ID"
                  " JOIN Actions ON actionID=Actions.ID"
                  " WHERE Users.name = :name"
                  " AND Activities.date = :date");
    query.bindValue(":name", user);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.exec();
    std::vector<Activity> data;
    while (query.next())
    {
        Activity temp(query.value("Activities.ID").toUInt(),
                      query.value("Products.name").toString(),
                      query.value("Actions.name").toString(),
                      query.value("quantity").toDouble(),
                      QTime::fromString(query.value("startTime").toString(), "hh:mm:ss"),
                      QTime::fromString(query.value("endTime").toString(), "hh:mm:ss"));
        data.push_back(temp);
    }

    return data;
}

std::vector<QString> DbService::getProducts(){
    QSqlQuery query("SELECT name FROM Products");
    query.exec();
    std::vector<QString> data;
    while (query.next())
    {
        data.push_back(query.value("name").toString());
    }
    return data;
}

std::vector<QString> DbService::getActions()
{
    QSqlQuery query("SELECT name FROM Actions");
    query.exec();
    std::vector<QString> data;
    while (query.next())
    {
        data.push_back(query.value("name").toString());
    }
    return data;
}

std::vector<QString> DbService::getUsers()
{
    QSqlQuery query("SELECT name FROM Users");
    query.exec();
    std::vector<QString> data;
    while (query.next())
    {
        data.push_back(query.value("name").toString());
    }
    return data;
}



void DbService::addUser(QString name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Users(name) VALUES (:name)");
    query.bindValue(":name", name);
    query.exec();
}

void DbService::addProduct(QString name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Products(name) VALUES (:name)");
    query.bindValue(":name", name);
    query.exec();
}
void DbService::addAction(QString name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Actions(name) VALUES (:name)");
    query.bindValue(":name", name);
    query.exec();
}
void DbService::addEvent(QString userName, QDate date, QString productName, QString actionName, QTime startTime, QTime endTime)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Activities(userID, date, productID, actionID, startTime, endTime)"
                  " VALUES((SELECT ID FROM Users WHERE name= :userName),"
                  ":date,"
                  "(SELECT ID FROM Products WHERE name= :productName),"
                  "(SELECT ID FROM Actions WHERE name= :actionName),"
                  ":startTime,"
                  ":endTime)");
    query.bindValue(":userName", userName);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":productName", productName);
    query.bindValue(":actionName", actionName);
    query.bindValue(":startTime", startTime.toString("hh:mm:ss"));
    query.bindValue(":endTime", endTime.toString("hh:mm:ss"));
    query.exec();
    if (query.lastError().isValid()){
        qWarning() << "add event" << query.lastError().text();
    }
}
void DbService::addEvent(QString userName, QDate date, QString productName, QString actionName, QTime startTime, QTime endTime, double quantity)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Activities(userID, date, productID, actionID, startTime, endTime, quantity)"
                  " VALUES((SELECT ID FROM Users WHERE name= :userName),"
                  ":date,"
                  "(SELECT ID FROM Products WHERE name= :productName),"
                  "(SELECT ID FROM Actions WHERE name= :actionName),"
                  ":startTime,"
                  ":endTime,"
                  ":quantity)");
    query.bindValue(":userName", userName);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":productName", productName);
    query.bindValue(":actionName", actionName);
    query.bindValue(":startTime", startTime.toString("hh:mm:ss"));
    query.bindValue(":endTime", endTime.toString("hh:mm:ss"));
    query.bindValue(":quantity", quantity);
    query.exec();
    if (query.lastError().isValid()){
        qWarning() << "add event" << query.lastError().text();
    }
}

void DbService::removeEvent(uint ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ACTIVITIES WHERE ID= :ID");
    query.bindValue(":ID", ID);
    query.exec();
}
