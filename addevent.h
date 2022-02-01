#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>

#include "dbservice.h"

namespace Ui {
class AddEvent;
}

class AddEvent : public QDialog
{
    Q_OBJECT

public:
    explicit AddEvent(QWidget *parent = nullptr);
    ~AddEvent();

    void setCurrentUser(QString user);
    void setDate(QDate date);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddEvent *ui;
    DbService* dbService;

    QString currentUser;
    QDate date;

    void setUpProducts();
    void setUpActions();
};

#endif // ADDEVENT_H
