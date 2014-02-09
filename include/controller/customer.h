#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <utility>
#include "structures.h"

class Customer
{
public:
  Customer();

    std::string getFirstName() const;
    std::string getName() const;
    std::string getLogin() const;
    float getBalance() const;
    unsigned getCustomerId() ;
    int getCategory();

    void setFirstName(const std::string &firstName);
    void setName(const std::string &familyName);
    void setLogin(const std::string &login);
    void setBalance(float balance);
    void setCustomerId (unsigned _id);
    void setCategory (int _cat);

    void saveCustomer();
    db_customerTuple getDbCustomer();
    view_customerTuple getViewCustomer();

    /*
    void addToBalance(float addedBalance);
    void removeToBalance(float removedBalance);
    bool checkBalance() const;
    Customer& operator+=(int addedBalance);
    Customer& operator-=(int removedBalance);
*/
private:
    std::string name;
    std::string firstname;
    std::string login;
    int category;
    float balance;
    int customerid;
 };

#endif // CUSTOMER_H
