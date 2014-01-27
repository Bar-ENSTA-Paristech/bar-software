#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"
#include "query.h"
#include "queue"
#include "tuple"
#include "structures.h"
#include <QString>

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

    db_customerQueue searchCustomer(std::string &string,int cat=0);//Méthode qui renvoie une queue de tuple correspondant aux infos des consommateurs dont le nom correspond à la recherche
    //OK (Fonctionne - a tester plus en profondeur)

    db_customerTuple getCustomerFromId(unsigned id);//Méthode recevant l'id d'un client et renvoyant le tuple de ses infos
    //OK (Fonctionne - a tester plus en profondeur)

    db_productQueue getProductsFromCategory(unsigned cat);//Méthode recevant un unsigned correspondant à une catégorie de conso et renvoie toutes les consos correspondates
    //OK (Fonctionne - a tester plus en profondeur

    db_productQueue getAllProducts ();//

    db_productTuple getProductFromId(unsigned id);//Méthode recevant l'id d'une conso et renvoyant le tuple de ses infos
    //OK (Fonctionne - a tester plus en profondeur)

    db_histQueue getLastOperations(int x); //Méthode qui récupère les x dernières opérations effectuées
    //OK (Fonctionne - a tester plus en profondeur)

    db_categoryQueue getProdCategories(); //Implémentée / Non testée

    db_categoryQueue getCustCategories();

    db_histQueue getFullHist();

    db_histQueue getProductHist (unsigned id);

    db_histQueue getCustomerHist(unsigned);//Renvoie l'historique d'un client en ayant recu son id
    //OK (Fonctionne - a tester plus en profondeur)

    std::string getPassword (std::string &login);//Retourne le password correspondant au login recherché

    int editCustomerAccount (db_customerTuple); //Méthode générique qui met à jour TOUTES les informations du client
    //Implémentée / Non testée

    int createCustomerAccount (db_customerTuple);// Méthode créant un nouveau champ dans la Table 'notes' de la BDD/ Par défaut l'id envoyé vaut -1
    //Implémentée / Non testée

    int deleteCustomerAccount (int id);// Supprime le compte d'un client ainsi que toutes ses opérations , [les infos seront transférées dans une BDD séparée (si possible), l'opération est protégée = effectué par le controleur]
    //Implémentée / Non testée

    int createProduct (db_productTuple);//Méthode créant un nouveau champ dans consos /Par défaut le nouvel id envoyé par le controlleur vaut -1

    int deleteProduct (int id);

    int editProduct (db_productTuple);//Méthode générique qui met à jour TOUTES les informations de la conso
    //Rq : penser à Maj prix_consos

    int createCategory (db_categoryTuple);//Méthode créant un nouveau champ dans categories /Par défaut le nouvel id vaut -1

    int editCategory (db_categoryTuple);

    int deleteCategory (int id);

    int addHist (db_histTuple,bool to_old=false);

    int addToBar (std::pair<std::string,std::string>);

    int autoDumpHist();

private:
    sqlite3* handle; //Pointeur vers la BDD
};

#endif // DATABASE_H
