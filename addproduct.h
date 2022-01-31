#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>

#include "dbservice.h"

namespace Ui {
class AddProduct;
}

class AddProduct : public QDialog
{
    Q_OBJECT

public:
    explicit AddProduct(QWidget *parent = nullptr);
    ~AddProduct();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddProduct *ui;
    DbService* dbService;
};

#endif // ADDPRODUCT_H
