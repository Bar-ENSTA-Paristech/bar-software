#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"
#include "query.h"
#include "queue"
#include "tuple"

//TUPLE du consommateur : Nom, Prénom , Catégorie , balance , id
typedef std::tuple< std::string, std::string, std::string, float, unsigned > type_dbTuple;
//TUPLE du produit : Produit, Catégorie , prix ,stock , id
typedef std::tuple< std::string, unsigned, float , unsigned, unsigned > type_consodbTuple;
//TUPLE d'un historique (une transaction) : Nom, Prénom, Produit, Date, valeur
typedef std::tuple< std::string,std::string,std::string,std::string , float> type_histdbTuple;


//On définit les structures de queue<> correspondant à chaque type de tuple
typedef std::queue<type_dbTuple> type_dbQueue;
typedef std::queue<type_consodbTuple> type_consodbQueue;
typedef std::queue<type_histdbTuple> type_histdbQueue;

class Database
{
public:
    Database();
    int openDatabase(); //Cette méthode ne prend pas d'argument car la BDD à ouvrir est unique et fixée
    int executeQuery (Query &query);
    int closeDatabase();
    int initializeDatabaseForm();
    type_dbQueue searchCustomer(std::string &string);//Méthode qui renvoie une queue de tuple correspondant aux infos des consommateurs dont le nom correspond à la recherche

    type_dbTuple getCustomerFromId(int id);//Méthode recevant l'id d'un client et renvoyant le tuple de ses infos

    type_consodbQueue getProductsFromCategory(unsigned);//Méthode recevant un unsigned correspondant à une catégorie de conso et renvoie toutes les consos correspondates

    type_consodbTuple getProductFromId(unsigned);//Méthode recevant l'id d'une conso et renvoyant le tuple de ses infos

    type_histdbQueue getLastOperations(); //Méthode qui récupère les 15 dernières opérations effectuées

    type_histdbQueue getCustomerHist(unsigned);//Renvoie l'historique d'un client en ayant recu son id

private:

    sqlite3* handle; //Pointeur vers la BDD
};

#endif // DATABASE_H
