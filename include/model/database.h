#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <cstring>
#include <QDebug>
#include <tuple>
#include <sstream>
#include <QString>
#include <vector>
#include <QDateTime>
#include <ctime>
#include <cstdio>
#include "sqlite3.h"
#include "query.h"
#include "queue"
#include "tuple"
#include "structures.h"

extern QString GLOBAL_PATH;

class Plotting;
class db_categoryTuple;
class db_customerTuple;
class db_histTuple;
class db_productTuple;

class view_customerTuple;
class view_productTuple;

class Database
{
public:
    Database();
    int openDatabase(); //Cette méthode ne prend pas d'argument car la BDD à ouvrir est unique et fixée
    int executeQuery (Query &query);
    int closeDatabase();
    int initializeDatabaseForm();

    sqlite3* getHandle();
    void setHandle(sqlite3*);

    db_customerQueue searchCustomer(std::string &string,int cat=-1);//Méthode qui renvoie une queue de tuple correspondant aux infos des consommateurs dont le nom correspond à la recherche
    //OK (Fonctionne - a tester plus en profondeur)

    db_customerTuple getCustomerFromId(unsigned id);//Méthode recevant l'id d'un client et renvoyant le tuple de ses infos
    //OK (Fonctionne - a tester plus en profondeur)

    db_customerQueue getCustomerFromCategory(int id); // Méthode renvoyant les clients d'une certaine catégorie


    db_productQueue getProductsFromCategory(int cat);//Méthode recevant un unsigned correspondant à une catégorie de conso et renvoie toutes les consos correspondates

    db_customerQueue getOldCustomers(){db_customerQueue a; return a;} // Methode renvoyant les clients ayant été supprimés
    // ########## A IMPLEMENTER ########

 //OK (Fonctionne - a tester plus en profondeur

    db_productQueue getAllProducts ();//

    db_productTuple getProductFromId(unsigned id);//Méthode recevant l'id d'une conso et renvoyant le tuple de ses infos
    //OK (Fonctionne - a tester plus en profondeur)

    db_histQueue getLastOperations(int x); //Méthode qui récupère les x dernières opérations effectuées
    //OK (Fonctionne - a tester plus en profondeur)

    db_categoryQueue getProdCategories(); //Implémentée / Non testée

    db_categoryQueue getCustCategories();

    void editProdCategory(db_categoryTuple tuple); // Fonctionne

    void editCustCategory(db_categoryTuple tuple); // Fonctionne

    db_histQueue getFullHist();

    db_histQueue getProductHist (unsigned id,bool old);

    db_histQueue getCustomerHist(unsigned id,bool old);//Renvoie l'historique d'un client en ayant recu son id
    //OK (Fonctionne - a tester plus en profondeur)

    std::string getPassword (std::string &login);//Retourne le password correspondant au login recherché

    void dumpCustomerToDelete(db_customerTuple tuple);//

    void dumpProductToDelete(db_productTuple tuple); //Cas d'un stock non nul a gérer dans le controlleur

    void addHistCashier(db_finop_tuple tuple); //Paiement par Cash/Chèque

    void transferToBDE(db_finop_tuple tuple); // Paiement par CB ou Vidage de caisse//Paiement des factures

    db_finop_queue getBDEHist(int year=0); // 0 for current year / -1 for all

    db_finop_queue getCashierHist();

    float getAccountValue(Account cpt);

    void updateAccountValue(float addedValue,Account cpt);
    // ############# A IMPLEMENTER #############
    void dumpHistOfDeletedCust (unsigned id);

    void setPassword(std::string login, std::string password); // edit le mdp ou le crée si le login est inconnu

    // ######
    int editCustomerAccount (db_customerTuple); //Méthode générique qui met à jour TOUTES les informations du client
    //Implémentée / fonctionne

    int createCustomerAccount (db_customerTuple);// Méthode créant un nouveau champ dans la Table 'notes' de la BDD/ Par défaut l'id envoyé vaut -1
    //Implémentée / Non testée

    int deleteCustomerAccount (int id);// Supprime le compte d'un client ainsi que toutes ses opérations , [les infos seront transférées dans une BDD séparée (si possible), l'opération est protégée = effectué par le controleur]
    //Implémentée / Non testée

    int createProduct (db_productTuple);//Méthode créant un nouveau champ dans consos /Par défaut le nouvel id envoyé par le controlleur vaut -1

    int deleteProduct (int id);

    int editProduct (db_productTuple);//Méthode générique qui met à jour TOUTES les informations de la conso
    //Rq : penser à Maj prix_consos

    int createProdCategory (db_categoryTuple);//Méthode créant un nouveau champ dans categories /Par défaut le nouvel id vaut -1

    //int editCategory (db_categoryTuple); cf versions spécialisées product & customer

    int deleteCategory (int id);

    int addHist (db_histTuple,bool to_old=false);

    int addToBar (std::pair<std::string,std::string>);

    db_TVAcategoryQueue getTvaRates();

    int autoDumpHist();

    int addStockedit (db_commandQueue _com);

    int addCommand (db_comTuple);

    db_commandQueue getCommandFromProdId (int id);

    void editTvaRate(db_TVAcategoryTuple tuple);

    db_comQueue getCommandsOfYear (int _year);

    db_saleQueue getSalesOfYear (int _year);

    void convertToPointDecimal(std::string &str); // Remplace les éventuelles virgules d'un décimal par des points, compréhensible par SQLite

private:
    sqlite3* handle; //Pointeur vers la BDD
};

#endif // DATABASE_H
