#include "customer.h"
#include <iostream>

using namespace std;

Customer::Customer(string _login, pair<string,string> _name, string _group, float _balance) : login(_login), name(_name), group(_group), balance(_balance)
{
}

Customer::Customer(string _login, string _firstName, string _familyName, string _group, float _balance) : login(_login), balance(_balance), group(_group)
{
    name = make_pair(_firstName, _familyName);
}

string Customer::getFirstName() const
{
    return name.first;
}

string Customer::getFamilyName() const
{
    return name.second;
}

string Customer::getLogin() const
{
    return login;
}

float Customer::getBalance() const
{
    return balance;
}

void Customer::setName(const string &firstName, const string &familyName)
{
    name = make_pair(firstName,familyName);
}

void Customer::setName(pair<string,string> _name)
{
    name = _name;
}

void Customer::setFirstName(const string &_firstName)
{
    name.first = _firstName;
}

void Customer::setFamilyName(const string &_familyName)
{
    name.second = _familyName;
}

void Customer::setLogin(const string &_login)
{
    login = _login;
}

void Customer::setBalance(float _balance)
{
    if (_balance > balance)
        cout << "Balance of customer " << name.first << " " << name.second << "has been raised above its own." << endl;
    else if (_balance < 0)
        cout << "A negative balance has been given to customer " << name.first << " " << name.second << "." << endl;
    checkBalance();
    balance = _balance;
}

void Customer::addToBalance(float addedBalance)
{
    if (addedBalance > 50.0)
        cout << "More than 50 euros were added to " << name.first << " " << name.second << "'s account." << endl;
    balance += addedBalance;
    checkBalance();
}

void Customer::removeToBalance(float removedBalance)
{
    addToBalance(-removedBalance);
}

bool Customer::checkBalance() const
{
    if (balance >= 0)
        return true;
    cout << "Customer " << name.first << " " << name.second << " now has a negative balance." << endl;
    return false;
}
