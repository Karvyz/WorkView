#include "workview.h"


WorkView::WorkView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WorkView)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    updateUsers();
    updateActivites();
}

WorkView::~WorkView()
{
    delete ui;
}

void WorkView::updateActivites()
{
    if (ui->treeWidget->topLevelItemCount() != 0)
        ui->treeWidget->clear();
    std::vector<Activity> activities = dbService->getActivities(ui->nameComboBox->currentText(), ui->dateEdit->date());
    for (auto activity : activities)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, activity.getProduct());
        item->setText(1, activity.getAction());
        if (activity.getQuantity() != 0)
            item->setText(2, QString::number(activity.getQuantity()));
        item->setText(3, activity.getStartTime());
        item->setText(4, activity.getEndTime());
    }
}

void WorkView::updateUsers()
{
    std::vector<QString> users = dbService->getUsers();
    ui->nameComboBox->clear();
    for (auto user : users)
        ui->nameComboBox->addItem(user);
}


void WorkView::on_actionAjouter_un_produit_triggered()
{
    AddProduct ap;
    ap.exec();
}


void WorkView::on_actionAjouter_une_action_triggered()
{
    AddAction aa;
    aa.exec();
}


void WorkView::on_actionAjouter_un_utilisateur_triggered()
{
    AddUser au;
    au.exec();
    updateUsers();
}


void WorkView::on_nameComboBox_currentTextChanged(const QString &arg1)
{
    updateActivites();
}


void WorkView::on_dateEdit_userDateChanged(const QDate &date)
{
    updateActivites();
}

void WorkView::on_addEventButton_clicked()
{
    AddEvent ae;
    ae.setCurrentUser(ui->nameComboBox->currentText());
    ae.setDate(ui->dateEdit->date());
    ae.exec();
    updateActivites();
}


void WorkView::on_removeEventButton_clicked()
{
    if (ui->treeWidget->currentItem() == nullptr)
        return;
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    std::vector<Activity> activities = dbService->getActivities(ui->nameComboBox->currentText(), ui->dateEdit->date());
    for (auto activity : activities)
    {
        if (activity.getProduct() == item->text(0)
                && activity.getAction() == item->text(1)
                && (QString::number(activity.getQuantity()) == item->text(2) || (activity.getQuantity() == 0 && item->text(2) == ""))
                && activity.getStartTime() == item->text(3)
                && activity.getEndTime() == item->text(4))
        {
            dbService->removeEvent(activity.getID());
        }

    }
    updateActivites();
}

