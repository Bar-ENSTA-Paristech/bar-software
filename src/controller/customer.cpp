#include "customer.h"
#include <iostream>

using namespace std;

Customer::Customer()
{
    login ="";
    name="";
    firstname="";
    login="";
    customerid=0;
    balance=0;
}

string Customer::getFirstName() const
{
    return firstname;
}

string Customer::getName() const
{
    return name;
}

string Customer::getLogin() const
{
    return login;
}

float Customer::getBalance() const
{
    return balance;
}

unsigned Customer::getCustomerId()
{
    return customerid;
}

int Customer::getCategory()
{
    return category;
}

/*
void Customer::setName(const string &firstName, const string &familyName)
{
    name = make_pair(firstName,familyName);
}

void Customer::setName(pair<string,string> _name)
{
    name = _name;
}
*/
void Customer::setFirstName(const std::string &_firstName)
{
    firstname = _firstName;
}

void Customer::setName(const std::string &_familyName)
{
    name = _familyName;
}

void Customer::setLogin(const std::string &_login)
{
    login = _login;
}

void Customer::setCustomerId(unsigned _id)
{
    customerid = _id;
}

void Customer::setCategory(int _cat)
{
    category=_cat;
}

void Customer::setBalance(float _balance)
{
    if (_balance > balance)
        cout << "Balance of customer " << name << " " << firstname << "has been raised above its own." << endl;
    else if (_balance < 0)
        cout << "A negative balance has been given to customer " << name << " " << firstname << "." << endl;
    //checkBalance();
    balance = _balance;
}
/*
void Customer::addToBalance(float addedBalance)
{
   balance += addedBalance;
}

void Customer::removeToBalance(float removedBalance)
{
    balance += (-removedBalance);
}

bool Customer::checkBalance() const
{
    if (balance >= 0)
        return true;
    cout << "Customer " << name.first << " " << name.second << " now has a negative balance." << endl;
    return false;
}

Customer &Customer::operator +=(int addedBalance)
{
    if (addedBalance > 50.0)
        cout << "More than 50 euros were added to " << name.first << " " << name.second << "'s account." << endl;
    balance += addedBalance;
    checkBalance();
    return *this;
}

Customer &Customer::operator -=(int removedBalance)
{
    return (*this)+=(-removedBalance);
}
*/
