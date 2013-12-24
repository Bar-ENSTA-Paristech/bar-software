#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>


//TUPLE model du consommateur : Nom, Prénom ,Login, Catégorie , balance , id
//typedef std::tuple<  std::string, std::string, std::string , std::string, float, unsigned > db_customerTuple;
//TUPLE view du consommateur : Nom, Prénom , Catégorie , balance , id
typedef std::tuple< QString, QString, QString, float, unsigned/*,QString*/ > view_customerTuple;
//TUPLE model du produit : Produit, Catégorie , prix ,stock , id
typedef std::tuple< std::string, unsigned, float , unsigned, unsigned > db_consoTuple;
//TUPLE view du produit : Produit, prix, quantity
typedef std::tuple<QString, float, unsigned int> view_productTuple;
//TUPLE model d'un historique (une transaction) : Nom, Prénom, Produit, Date, valeur
typedef std::tuple< std::string,std::string,std::string,std::string , float> db_histTuple;

//On définit les structures de queue<> correspondant à chaque type de tuple
//typedef std::queue<db_customerTuple> db_customerQueue;
typedef std::queue<db_consoTuple> db_consoQueue;
typedef std::queue<db_histTuple> db_histQueue;
typedef std::queue<view_customerTuple> view_customerQueue;
typedef std::queue<view_productTuple> view_productQueue;


typedef std::pair< std::vector< double > , std::vector< double > > db_dataarray;


#endif // STRUCTURES_H
