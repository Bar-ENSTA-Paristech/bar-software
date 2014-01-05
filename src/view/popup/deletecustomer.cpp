#include "deletecustomer.h"

DeleteCustomer::DeleteCustomer(QWidget *parent) :
    QWidget(parent)
{
    VIEW.deleteCustomer = this;
    this->setWindowFlags(Qt::Tool);
    this->setFixedSize(400, 100);
    QGridLayout* layout = new QGridLayout(this);
    text = new QLabel(this);
    layout->addWidget(text, 0,0,1,1, Qt::AlignCenter);
    this->setLayout(layout);
}


void DeleteCustomer::printDelete(view_customerTuple& customer)
{
    text->setText(customer.getCustomerFirstName() + " " + customer.getCustomerName() + " n'est plus de ce monde !");
    this->show();
}
