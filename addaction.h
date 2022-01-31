#ifndef ADDACTION_H
#define ADDACTION_H

#include <QDialog>

#include "dbservice.h"

namespace Ui {
class AddAction;
}

class AddAction : public QDialog
{
    Q_OBJECT

public:
    explicit AddAction(QWidget *parent = nullptr);
    ~AddAction();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddAction *ui;
    DbService* dbService;
};

#endif // ADDACTION_H
