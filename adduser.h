#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>

#include "dbservice.h"

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddUser *ui;
    DbService* dbService;
};

#endif // ADDUSER_H
