#include <iostream>
#include "database.h"
#include "sqlite3.h"

database::database()
{

}

int database::openDatabase()
{

    //Modification de la configuration de sqlite pour accepter les URI (gestion des repertoires)
    sqlite3_config(SQLITE_CONFIG_URI,1);

std::cout<<"Tentative d'ouverture de db"<<std::endl;
    sqlite3* DB;
    char* DBfilename="file:bar.db";
    int coderesult=sqlite3_open(DBfilename //Database filename
                                ,&DB);//adresse mémoire de la BDD



    if (coderesult!=SQLITE_OK)
        std::cout<<sqlite3_errmsg(DB)<<std::endl;
    else
        handle=DB;
    std::cout<<"OK"<<std::endl;

    return coderesult;

}

int database::closeDatabase()
{
std::cout<<"Tentative de fermeture de db"<<std::endl;
    sqlite3* DB=handle;
    int coderesult=sqlite3_close(DB);

    if (coderesult!=SQLITE_OK)
        std::cout<<"The database could not close properly."<<std::endl;
    else
        std::cout<<"The database has been properly closed."<<std::endl;

    return coderesult;

}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++)
  {
     printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
 }


int database::executeQuery(Query &_query)
{
    char* query=_query.getQuery();
    int coderesult;
    char*zErrMsg;

    coderesult = sqlite3_exec(handle, query, callback, 0, &zErrMsg);
    if( coderesult!=SQLITE_OK )
    {
        std::cerr<<"SQL error: "<<zErrMsg<<"\n"<<std::endl;
        sqlite3_free(zErrMsg);
    }
    else
    {
        std::cout<<"The following query has been correctly executed: "<<query<<std::endl;
    }
    return coderesult;
}
