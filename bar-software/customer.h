#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <utility>


class Customer
{
public:
    Customer(std::string login, std::pair<std::string,std::string> name, std::string groupe = "", float balance = 0);
    Customer(std::string login, std::string firstName, std::string familyName, std::string groupe = "", float balance = 0);
    std::string getFirstName() const;
    std::string getFamilyName() const;
    std::string getLogin() const;
    float getBalance() const;
    void setName(const std::string &firstName, const std::string &familyName);
    void setName(std::pair<std::string,std::string> name);
    void setFirstName(const std::string &firstName);
    void setFamilyName(const std::string &familyName);
    void setLogin(const std::string &login);
    void setBalance(float balance);
    void addToBalance(float addedBalance);
    void removeToBalance(float removedBalance);
    bool checkBalance() const;
    Customer& operator+=(int addedBalance);
    Customer& operator-=(int removedBalance);

private:
    std::pair<std::string,std::string> name;
    std::string login;
    std::string group;
    float balance;
    static unsigned numberOfConsumers;
    // Est-il nécessaire de garder un historique plutôt que de faire une requête à la volée ?

};

#endif // CUSTOMER_H
