#include "addaction.h"
#include "ui_addaction.h"

AddAction::AddAction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAction)
{
    ui->setupUi(this);
}

AddAction::~AddAction()
{
    delete ui;
}

void AddAction::on_buttonBox_accepted()
{
    dbService->addAction(ui->nameEdit->text());
}

