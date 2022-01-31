#include "activity.h"

Activity::Activity(int ID, QString productName, QString actionName, QTime startTime, QTime endTime) : ID(ID),
    productName(productName),
    actionName(actionName),
    startTime(startTime),
    endTime(endTime)
{

}


QString Activity::getProduct()
{
    return productName;
}
QString Activity::getAction()
{
    return actionName;
}
QString Activity::getStartTime()
{
    return startTime.toString(QLocale::system().timeFormat());
}
QString Activity::getEndTime()
{
    return endTime.toString();
}
