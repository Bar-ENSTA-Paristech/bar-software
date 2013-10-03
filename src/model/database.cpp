#include <iostream>
#include "database.h"
#include "sqlite3.h"
#include <cstring>
#include "QDebug"
#include <tuple>
#include <sstream>
#include <vector>

//La déclaration du pointeur vers le résultat de la requête doit se faire dans l'espage global
//car la fonction callback ne peut être incorporée à une classe et l'on ne peut toucher à ses arguments.
std::queue<std::string> *queryResult(0);

//On définit de même queue dans l'espace global pour que celle-ci ne soit pas locale du callback.
//
// queue correspond à la file des résultats renvoyés par la BDD, si celle-ci n'est pas vide lors de l'execution d'une nouvelle requête,
//cela signifie que toutes les informations n'ont pas encore été remises au controleur
//
std::queue<std::string> queue;


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
        //queue.push(azColName[i]);
        queue.push(argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    queue.push("\n");
    *queryResult=queue;
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
    /* test_q.setQuery("INSERT INTO `notes` (`client_id`, `nom`, `prenom`, `type`, `compte`, `vip`) VALUES(152, 'Toof', 'Gui', 5, -4, 0),(3, 'Manchoule', 'Shimone', 1, 3.3, 0);");
    coderesult+=executeQuery(test_q);*/

    //test_q.setVerbose(1);

    return coderesult;
}

type_customerdbQueue Database::searchCustomer(std::string &string)
{
    std::string searchString=string;
    std::string queryString="";

    //std::string str;
    Query query;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;
    //queryResult n'est alloué que dans les fonctions l'utilisant
    queryResult = new std::queue<std::string> ;

    unsigned i;
    unsigned j=0;
    type_customerdbQueue *result(0);
    result=new type_customerdbQueue;

    type_customerdbTuple *customer(0);
    customer=new type_customerdbTuple;

    //Formation du string de query adapté
    queryString+=" SELECT * FROM notes WHERE nom LIKE '";
    queryString+=searchString;
    queryString+="%";
    queryString+="' OR prenom LIKE '";
    queryString+=searchString;
    queryString+="%";
    queryString+="' ORDER BY nom DESC;";

    //Implémentation de la query et execution de celle ci
    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);

    //Récupération des données renvoyées par la db que l'on met dans une queue<string>
    *queryResultFunction=*queryResult;

    //str=queryResultFunction->front();
    //std::cout<<str<<std::endl;
    //std::cout<<queryResultFunction->size()<<std::endl;

    //Il faut désormais caster le queue <string> dans un queue<tuple< // >> que l'on va return

    //Pour cela on utilise une list de string
    std::vector<std::string> vectorFromQueue;

    //Boucle sur tout le resultat (L'emploi de while n'est peut être pas le plus judicieux)
    for (i=0;i<=queryResultFunction->size();i++)
    {
        while(queryResultFunction->size()>1)
        {
            //Travail des données d'une personne unique

            //Remplissage de Result

            while (queryResultFunction->front()!= "\n"||queryResultFunction->size()>1)
            {
                //La ligne suivante pop les noms des colonnes dans le cas ou elles sont push initialement
                //queryResultFunction->pop();
                vectorFromQueue.push_back(queryResultFunction->front());
                //On supprime l'élément qui vient d'être extrait.
                queryResultFunction->pop();
            }

            //On parse les std::string en float et unsigned pour Balance et Id
            float recuperatedBalance;
            int recuperatedId;

            std::istringstream(vectorFromQueue[4]) >> recuperatedBalance;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;

            *customer = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[3],recuperatedBalance,recuperatedId);

            //On supprime le dernier element du résultat unique , le parser '\n'
            queryResultFunction->pop();
            result->push(*customer);
            // L'int j correspond à l'index dans la queue , il est incrémenté a chaque boucle sur une personne
            j++;
        }
    }

    return *result;
}

type_consodbQueue Database::getProductsFromCategory(unsigned categorie)
{
    std::string queryString;
    //std::string str;
    Query query;

    type_consodbQueue *result(0);
    result=new type_consodbQueue;

    type_consodbTuple *conso(0);
    conso=new type_consodbTuple;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    //queryResult n'est alloué que dans les fonctions l'utilisant
    queryResult = new std::queue<std::string> ;

    unsigned i;
    unsigned j=0;

    //Formation du string de query adapté
    queryString+=" SELECT * FROM consos WHERE type=";
    queryString+=categorie;
    queryString+=" ORDER BY nom ASC;";

    //Implémentation de la query et execution de celle ci
    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);

    //Récupération des données renvoyées par la db que l'on met dans une queue<string>
    *queryResultFunction=*queryResult;

    //str=queryResultFunction->front();
    //std::cout<<str<<std::endl;
    //std::cout<<queryResultFunction->size()<<std::endl;

    //Il faut désormais caster le queue <string> dans un queue<tuple< // >> que l'on va return

    //Pour cela on utilise une list de string
    std::vector<std::string> vectorFromQueue;

    //Boucle sur tout le resultat (L'emploi de while n'est peut être pas le plus judicieux)
    for (i=0;i<=queryResultFunction->size();i++)
    {
        while(queryResultFunction->size()>1)
        {
            //Travail des données d'une personne unique

            //Remplissage de Result

            while (queryResultFunction->front()!= "\n"||queryResultFunction->size()>1)
            {
                //La ligne suivante pop les noms des colonnes dans le cas ou elles sont push initialement
                //queryResultFunction->pop();
                vectorFromQueue.push_back(queryResultFunction->front());
                //On supprime l'élément qui vient d'être extrait.
                queryResultFunction->pop();
            }

            //On parse les std::string en float et unsigned pour Balance et Id
            float recuperatedPrice;
            unsigned recuperatedId;
            unsigned recuperatedStock;
            unsigned recuperatedCategory;

            std::istringstream(vectorFromQueue[3]) >> recuperatedPrice;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;
            std::istringstream(vectorFromQueue[4]) >> recuperatedStock;
            std::istringstream(vectorFromQueue[2]) >> recuperatedCategory;

            *conso = std::make_tuple (vectorFromQueue[1],recuperatedCategory,recuperatedPrice,recuperatedStock,recuperatedId);

            //On supprime le dernier element du résultat unique , le parser '\n'
            queryResultFunction->pop();
            result->push(*conso);
            // L'int j correspond à l'index dans la queue , il est incrémenté a chaque boucle sur une personne
            j++;
        }
    }

    return *result;
}

type_histdbQueue Database::getLastOperations()
{

}

type_customerdbTuple Database::getCustomerFromId(int customerId)
{
    std::string queryString="";

    //On doit transformer l'int customerId en string pour effectuer la requête
    std::string idString = static_cast<std::ostringstream*>( &(std::ostringstream() << customerId) )->str();

    //std::string str;
    Query query;
    std::queue<std::string> *queryResultFunction(0);

    queryResultFunction = new std::queue<std::string> ;
    //queryResult n'est alloué que dans les fonctions l'utilisant
    queryResult = new std::queue<std::string> ;

    unsigned i;
    unsigned j=0;

    type_customerdbTuple *customer(0);
    customer=new type_customerdbTuple;

    //Formation du string de query adapté
    queryString+=" SELECT * FROM notes WHERE client_id=";
    queryString+=idString;
    queryString+=" ORDER BY nom DESC;";

    //Implémentation de la query et execution de celle ci
    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);

    //Récupération des données renvoyées par la db que l'on met dans une queue<string>
    *queryResultFunction=*queryResult;

    //str=queryResultFunction->front();
    //std::cout<<str<<std::endl;
    //std::cout<<queryResultFunction->size()<<std::endl;

    //Il faut désormais caster le queue <string> dans un queue<tuple< // >> que l'on va return
    //Pour cela on utilise une list de string
    std::vector<std::string> vectorFromQueue;

    //Boucle sur tout le resultat (L'emploi de while n'est peut être pas le plus judicieux)
    for (i=0;i<=queryResultFunction->size();i++)
    {
        while(queryResultFunction->size()>1)
        {
            //Travail des données d'une personne unique

            //Remplissage de Result

            while (queryResultFunction->front()!= "\n"||queryResultFunction->size()>1)
            {
                //La ligne suivante pop les noms des colonnes dans le cas ou elles sont push initialement
                //queryResultFunction->pop();
                vectorFromQueue.push_back(queryResultFunction->front());
                //On supprime l'élément qui vient d'être extrait.
                queryResultFunction->pop();
            }

            //On parse les std::string en float et unsigned pour Balance et Id
            float recuperatedBalance;
            int recuperatedId;

            std::istringstream(vectorFromQueue[4]) >> recuperatedBalance;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;

            *customer = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[3],recuperatedBalance,recuperatedId);

            //On supprime le dernier element du résultat unique , le parser '\n'
            queryResultFunction->pop();
            // L'int j correspond à l'index dans la queue , il est incrémenté a chaque boucle sur une personne
            j++;
        }
    }

    return *customer;
}
