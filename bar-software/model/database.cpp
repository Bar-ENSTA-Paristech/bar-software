#include <iostream>
#include "database.h"
#include "sqlite3.h"
#include <cstring>

Database::Database()
{

}

int Database::openDatabase()
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

int Database::closeDatabase()
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

int Database::executeQuery(Query &_query)
{
    std::string query_string=_query.getQuery();
    bool verbose=_query.getVerbose();

    //Transformation de la requete en string sous forme explicite de char*
    char* query= new char[query_string.length()+1];
    strcpy (query,query_string.c_str());

    int coderesult;
    char*zErrMsg;

    coderesult = sqlite3_exec(handle, query, callback, 0, &zErrMsg);

    if(verbose==true)
    {
        if( coderesult!=SQLITE_OK )
        {
            std::cout<<"SQL error: "<<zErrMsg<<"\n"<<std::endl;
            sqlite3_free(zErrMsg);
        }
        else
        {
            std::cout<<"The following query has been correctly executed: "<<query<<std::endl;
        }
    }
    else
    {
        if( coderesult!=SQLITE_OK )
        {
            sqlite3_free(zErrMsg);
        }

    }
    return coderesult;
}

int Database::initializeDatabaseForm()
{
    Query test_q;
    int coderesult=0;
    //Structure de la table `acces`
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `acces` (`password` varchar(15) NOT NULL,`id` unsigned int(10) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `categories` (`cat_id` unsigned int(11) NOT NULL,`categorie` varchar(20) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `consos` (`conso_id` unsigned int(11) NOT NULL,`nom` varchar(25) NOT NULL DEFAULT 'NULL',`type` int(11) DEFAULT NULL,`prix` float DEFAULT NULL,`stock` int(11) DEFAULT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `historique` (`his_id` int(11) NOT NULL,`client_id` int(11) NOT NULL,`conso_id` int(11) NOT NULL,`date_conso` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `notes` (`client_id` int(11) NOT NULL,`nom` varchar(25) NOT NULL,`prenom` varchar(25) NOT NULL,`type` int(11) NOT NULL,`compte` float NOT NULL,`vip` tinyint(1) NOT NULL) ;");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `prix_consos` (`id_conso` int(11) NOT NULL,`prix_precedent` float DEFAULT NULL,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `types_conso` (`type_conso_id` int(11) NOT NULL,`nom_type` varchar(25) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS Bar(test VARCHAR(40))");
    coderesult+=executeQuery(test_q);
    return coderesult;
}
