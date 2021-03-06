#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QTime>
#include <QDebug>

class Activity
{
public:
    Activity(uint ID, QString productName, QString actionName, double quantity, QTime startTime, QTime endTime);

    uint getID();
    QString getProduct();
    QString getAction();
    double getQuantity();
    QString getStartTime();
    QString getEndTime();
private:
    uint ID;
    QString productName;
    QString actionName;
    double quantity;
    QTime startTime;
    QTime endTime;
};

#endif // ACTIVITY_H
