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
    qDebug() << "dbPath" << dbPath;

    db.setDatabaseName(dbPath);
    if (!db.open())
    {
        qCritical() << "unable to open db" << db.lastError().text() << dbPath;
    }

    tablesCreation();
}

QSqlQuery DbService::runQuery(QString queryString)
{
    QSqlQuery query;
    query.exec(queryString);

    if (query.lastError().isValid()){
        qWarning() << "CREATE TABLE" << query.lastError().text();
    }
    return query;
}

void DbService::tablesCreation()
{
    QString tableUsers = "CREATE TABLE IF NOT EXISTS Users("
                         "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                         "name STRING NOT NULL UNIQUE)";
    runQuery(tableUsers);

    QString createTableProducts = "CREATE TABLE IF NOT EXISTS Products("
                                  "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                  "name STRING NOT NULL UNIQUE)";
    runQuery(createTableProducts);

    QString createTableActions = "CREATE TABLE IF NOT EXISTS Actions("
                                 "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                 "name STRING NOT NULL UNIQUE)";
    runQuery(createTableActions);

    QString createTableActivities = "CREATE TABLE IF NOT EXISTS Activities("
                                    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                    "userID INT NOT NULL REFERENCES Users(ID),"
                                    "productID INT NOT NULL REFERENCES Products(ID),"
                                    "actionID INT NOT NULL REFERENCES Actions(ID),"
                                    "date DATE DEFAULT CURRENT_DATE,"
                                    "startTime TIME NOT NULL,"
                                    "endTime TIME NOT NULL)";
    runQuery(createTableActivities);
}


std::vector<Activity> DbService::getActivities(QString user, QDate date)
{
    qDebug() << user;
    QSqlQuery query;
    query.prepare("select Activities.ID,startTime,endTime,Products.name,Actions.name from Activities"
                  " join Users on userID=Users.ID"
                  " join Products on productID=Products.ID"
                  " join Actions on actionID=Actions.ID"
                  " where Users.name = :name"
                  " and Activities.date = :date");
    query.bindValue(":name", user);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.exec();
    std::vector<Activity> data;
    while (query.next())
    {

        Activity temp(query.value("Activities.ID").toUInt(),
                      query.value("Products.name").toString(),
                      query.value("Actions.name").toString(),
                      QTime::fromString(query.value("startTime").toString(), "hh:mm:ss"),
                      QTime::fromString(query.value("endTime").toString(), "hh:mm:ss"));
        data.push_back(temp);
    }

    return data;
}

std::vector<QString> DbService::getProducts(){
    QString activitiesQuery = "select name from Products";
    QSqlQuery query = runQuery(activitiesQuery);
    std::vector<QString> data;
    while (query.next())
    {
        data.push_back(query.value("name").toString());
    }
    return data;
}

std::vector<QString> DbService::getActions()
{
    QString activitiesQuery = "select name from Actions";
    QSqlQuery query = runQuery(activitiesQuery);
    std::vector<QString> data;
    while (query.next())
    {
        data.push_back(query.value("name").toString());
    }
    return data;
}

std::vector<QString> DbService::getUsers()
{
    QString activitiesQuery = "select name from Users";
    QSqlQuery query = runQuery(activitiesQuery);
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
void DbService::addEvent(QString userName, QString productName, QString actionName, QTime startTime, QTime endTime)
{
    qDebug() << endTime;
    QSqlQuery query;
    query.prepare("INSERT INTO Activities(userID, productID, actionID, startTime, endTime)"
                  " VALUES((SELECT ID FROM Users WHERE name= :userName),"
                  "(SELECT ID FROM Products WHERE name= :productName),"
                  "(SELECT ID FROM Actions WHERE name= :actionName),"
                  ":startTime,"
                  ":endTime)");
    query.bindValue(":userName", userName);
    query.bindValue(":productName", productName);
    query.bindValue(":actionName", actionName);
    query.bindValue(":startTime", startTime.toString("hh:mm:ss"));
    query.bindValue(":endTime", endTime.toString("hh:mm:ss"));
    query.exec();
    if (query.lastError().isValid()){
        qWarning() << "add event" << query.lastError().text();
    }
}
