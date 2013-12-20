#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"
#include "query.h"
#include "queue"
#include "tuple"

//TUPLE du consommateur : Nom, Prénom , Catégorie , balance , id, login
typedef std::tuple< std::string, std::string, std::string, float, unsigned, std::string> type_customerdbTuple;
//TUPLE du produit : Produit, Catégorie , prix ,stock , id
typedef std::tuple< std::string, unsigned, float , unsigned, unsigned > type_consodbTuple;
//TUPLE d'un historique (une transaction) : Nom, Prénom, Produit, Date, valeur,id
typedef std::tuple< std::string,std::string,std::string,std::string , float , unsigned> type_histdbTuple;
//TUPLE des catégories : nom,id
typedef std::tuple< std::string, unsigned> type_categorydbTuple;

//On définit les structures de queue<> correspondant à chaque type de tuple
typedef std::queue<type_customerdbTuple> type_customerdbQueue;
typedef std::queue<type_consodbTuple> type_consodbQueue;
typedef std::queue<type_histdbTuple> type_histdbQueue;
typedef std::queue<type_categorydbTuple> type_categorydbQueue;

class Plotting;

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

    type_customerdbQueue searchCustomer(std::string &string);//Méthode qui renvoie une queue de tuple correspondant aux infos des consommateurs dont le nom correspond à la recherche
    //OK (Fonctionne - a tester plus en profondeur)

    type_customerdbTuple getCustomerFromId(unsigned id);//Méthode recevant l'id d'un client et renvoyant le tuple de ses infos
    //OK (Fonctionne - a tester plus en profondeur)

    type_consodbQueue getProductsFromCategory(unsigned cat);//Méthode recevant un unsigned correspondant à une catégorie de conso et renvoie toutes les consos correspondates
    //OK (Fonctionne - a tester plus en profondeur)

    type_consodbQueue getAllProducts ();//

    type_consodbTuple getProductFromId(unsigned id);//Méthode recevant l'id d'une conso et renvoyant le tuple de ses infos
    //OK (Fonctionne - a tester plus en profondeur)

    type_histdbQueue getLastOperations(); //Méthode qui récupère les 15 dernières opérations effectuées
    //OK (Fonctionne - a tester plus en profondeur)

    type_categorydbQueue getCategories(); //Implémentée / Non testée

    type_histdbQueue getFullHist();

    type_histdbQueue getCustomerHist(unsigned);//Renvoie l'historique d'un client en ayant recu son id
    //OK (Fonctionne - a tester plus en profondeur)

    /* (tuple a définir) getCategories();  */

    int editCustomerAccount (type_customerdbTuple); //Méthode générique qui met à jour TOUTES les informations du client
    //Implémentée / Non testée

    int createCustomerAccount (type_customerdbTuple);// Méthode créant un nouveau champ dans la Table 'notes' de la BDD/ Par défaut l'id envoyé vaut -1
    //Implémentée / Non testée

    int deleteCustomerAccount (int id);// Supprime le compte d'un client ainsi que toutes ses opérations , [les infos seront transférées dans une BDD séparée (si possible), l'opération est protégée = effectué par le controleur]
    //Implémentée / Non testée

    int createProduct (type_consodbTuple);//Méthode créant un nouveau champ dans consos /Par défaut le nouvel id envoyé par le controlleur vaut -1

    int deleteProduct (int id);

    int editProduct (type_consodbTuple);//Méthode générique qui met à jour TOUTES les informations de la conso
    //Rq : penser à Maj prix_consos

    int createCategory (type_categorydbTuple);//Méthode créant un nouveau champ dans categories /Par défaut le nouvel id vaut -1

    int editCategory (type_categorydbTuple);

    int deleteCategory (int id);

    int addHist (type_histdbTuple);

private:
    sqlite3* handle; //Pointeur vers la BDD
};

#endif // DATABASE_H
