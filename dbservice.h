#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <vector>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>

#include "activity.h"

class DbService
{
private:
    QSqlQuery runQuery(QString queryString);
    void tablesCreation();

public:
    DbService();
    std::vector<Activity> getActivities();
    std::vector<Activity> getActivities(QString user, QDate date);
    std::vector<QString> getProducts();
    std::vector<QString> getActions();
    std::vector<QString> getUsers();


    void addUser(QString name);
    void addProduct(QString name);
    void addAction(QString name);
    void addEvent(QString userName, QDate date, QString productName, QString actionName, QTime startTime, QTime endTime);
};

#endif // DBSERVICE_H
