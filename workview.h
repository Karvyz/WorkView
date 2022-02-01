#ifndef WORKVIEW_H
#define WORKVIEW_H

#include <QMainWindow>

#include "dbservice.h"
#include "addevent.h"
#include "adduser.h"
#include "addproduct.h"
#include "addaction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WorkView; }
QT_END_NAMESPACE

class WorkView : public QMainWindow
{
    Q_OBJECT

public:
    WorkView(QWidget *parent = nullptr);
    ~WorkView();

    void setDbService(DbService* dbService) {this->dbService = dbService;};

    void updateActivites();

private slots:
    void on_pushButton_clicked();

    void on_actionAjouter_un_produit_triggered();

    void on_actionAjouter_une_action_triggered();

    void on_actionAjouter_un_utilisateur_triggered();

    void on_nameComboBox_currentTextChanged(const QString &arg1);

    void on_dateEdit_userDateChanged(const QDate &date);

private:
    Ui::WorkView *ui;
    DbService* dbService;

    uint currentUser = 1;

    void updateUsers();
};
#endif // WORKVIEW_H
