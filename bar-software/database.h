#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"
#include "query.h"

class database
{
public:
    database();
    int openDatabase(); //Cette méthode ne prend pas d'argument car la BDD à ouvrir est unique et fixée
    int executeQuery (Query &query);
    int closeDatabase();
    int initializeDatabase();

private:
    sqlite3* handle; //Pointeur vers la BDD
};

#endif // DATABASE_H
