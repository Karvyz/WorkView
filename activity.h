#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QTime>
#include <QDebug>

class Activity
{
public:
    Activity(int ID, QString productName, QString actionName, QTime startTime, QTime endTime);

    QString getProduct();
    QString getAction();
    QString getStartTime();
    QString getEndTime();
private:
    int ID;
    QString productName;
    QString actionName;
    QTime startTime;
    QTime endTime;
};

#endif // ACTIVITY_H
