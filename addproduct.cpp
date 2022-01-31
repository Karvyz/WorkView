#include "addproduct.h"
#include "ui_addproduct.h"

AddProduct::AddProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProduct)
{
    ui->setupUi(this);
}

AddProduct::~AddProduct()
{
    delete ui;
}

void AddProduct::on_buttonBox_accepted()
{
    if (dbService == nullptr)
        qDebug() << "nullptred";
    dbService->addProduct(ui->nameEdit->text());
}

