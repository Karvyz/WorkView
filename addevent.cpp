#include "addevent.h"
#include "ui_addevent.h"

AddEvent::AddEvent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEvent)
{
    ui->setupUi(this);
    setUpProducts();
    setUpActions();
}

AddEvent::~AddEvent()
{
    delete ui;
}

void AddEvent::setCurrentUser(QString user)
{
    currentUser = user;
}

void AddEvent::setDate(QDate date)
{
    this->date = date;
}

void AddEvent::setUpProducts()
{
    std::vector<QString> products = dbService->getProducts();
    for (auto product : products)
        ui->productComboBox->addItem(product);
}


void AddEvent::setUpActions()
{
    std::vector<QString> actions = dbService->getActions();
    for (auto action : actions)
        ui->actionComboBox->addItem(action);
}

void AddEvent::on_buttonBox_accepted()
{
   dbService->addEvent(currentUser,
                       date,
                       ui->productComboBox->currentText(),
                       ui->actionComboBox->currentText(),
                       ui->startTimeEdit->time(),
                       ui->endTimeEdit->time());
}

