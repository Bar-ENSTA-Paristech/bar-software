#include <iostream>
#include "database.h"
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
//cela signifie que toutes les informations n'ont pas encore été remises au controleur (sécurité à implémenter)
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
    char DBfilename[]="file:bar.db";
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
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        //queue.push(azColName[i]);

        queue.push(argv[i] ? argv[i] : "NULL");
    }
    //printf("\n");

    queue.push("\n");

    *queryResult=queue;
    return 0;
}

void clear( std::queue<std::string> &q )
{
    std::queue<std::string> empty;
    std::swap( q, empty );
}

int Database::executeQuery(Query &_query)
{
    std::string query_string=_query.getQuery();
    bool verbose=_query.getVerbose();

    char* query= new char[query_string.length()+1];    //Transformation de la requete en string sous forme explicite de char*
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

sqlite3* Database::getHandle()
{
    return handle;
}

void Database::setHandle(sqlite3* given_handle)
{
    handle=given_handle;
}

int Database::initializeDatabaseForm()
{
    Query test_q;
    int coderesult=0;
    //Structure des différentes tables

    test_q.setQuery("CREATE TABLE IF NOT EXISTS `acces` (`password` varchar(15) NOT NULL,`id` unsigned int(10) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `categories` (`cat_id` unsigned int(11) NOT NULL,`categorie` varchar(20) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `consos` (`conso_id` unsigned int(11) NOT NULL,`nom` varchar(25) NOT NULL DEFAULT 'NULL',`type` int(11) DEFAULT NULL,`prix` float DEFAULT NULL,`stock` int(11) DEFAULT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `historique` (`his_id` int(11) NOT NULL,`client_id` int(11) NOT NULL,`conso_id` int(11) NOT NULL,`conso_price` float DEFAULT NULL,`date_conso` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `historique_save` (`his_id` int(11) NOT NULL,`client_id` int(11) NOT NULL,`conso_id` int(11) NOT NULL,`conso_price` float DEFAULT NULL,`date_conso` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `historique_deleted_account` (`his_id` int(11) NOT NULL,`client_id` int(11) NOT NULL,`conso_id` int(11) NOT NULL,`conso_price` float DEFAULT NULL,`date_conso` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `notes` (`client_id` int(11) NOT NULL,`nom` varchar(25) NOT NULL,`prenom` varchar(25) NOT NULL,`login` varchar(25) NOT NULL,`type` int(11) NOT NULL,`compte` float NOT NULL,`vip` tinyint(1)) ;");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `prix_consos` (`id_conso` int(11) NOT NULL,`prix_precedent` float DEFAULT NULL,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `types_conso` (`type_conso_id` int(11) NOT NULL,`nom_type` varchar(25) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `vidage_caisse` (`type_vidage` tinyint(1) NOT NULL,`valeur` float NOT NULL,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `commande` (`commande_id` int(11) NOT NULL,`valeur` float NOT NULL,`libelle` varchar(100) ,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `achats` (`commande_id` int(11) NOT NULL,`conso_id` int(11) NOT NULL,`quantite` int(11),`prix_unitaire` float(11) ,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);


    //test_q.setVerbose(1);
    return coderesult;
}

/*---------------------------------------------------
Toutes les méthodes qui renvoient les résultats d'une
requête depuis la BDD jusqu'au controlleur sont
construites sous le même schema que la méthode suivante
Elles ne seront donc pas commentées aussi précisément
que la méthode qui suit.
---------------------------------------------------*/

type_customerdbQueue Database::searchCustomer(std::string &string)
{
    std::string searchString=string;
    std::string queryString="";   //Initialisation du string qui contiendra la requête SQL

    Query query; //Initialisation de la requête

    std::queue<std::string> *queryResultFunction(0);  //
    queryResultFunction = new std::queue<std::string> ;

    queryResult = new std::queue<std::string> ;   //queryResult n'est alloué que dans les fonctions l'utilisant

    /*
     * Remarque sur queryResultFunction et queryResult
     *    queryResult est définie en dehors de toute méthode. Cela est du a la syntaxe "fermée" de sqlite3_exec et de son argument callback.
     *    Par la suite queryResultFunction est définie comme pointant vers la même adresse que queryResult. Cela revient à un passage par adresse
     *    un peu dégeu mais cette solution fonctionne.
    */
    unsigned i;
    unsigned j=0;
    type_customerdbQueue *result(0); //On initialise la queue de tuple qui sera retournée à la fin au controlleur
    result=new type_customerdbQueue;

    type_customerdbTuple *customer(0); //On initialise aussi le tuple correspondant
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

    *queryResultFunction=*queryResult;    //Récupération des données renvoyées par la db que l'on met dans une queue<string>

    /*Il faut désormais caster le queue <string> dans un queue<tuple< // >> que l'on va return
    Pour cela on utilise un vector de string */

    std::vector<std::string> vectorFromQueue;

    if (queryResultFunction->size()!=0) //Boucle sur tout le resultat
    {
        for (i=0;i<=queryResultFunction->size();i++)
        {
            while(!queryResultFunction->empty())
            {
                //Remplissage de Result
                while (queryResultFunction->front()!= "\n"&& !queryResultFunction->empty())
                {
                    vectorFromQueue.push_back(queryResultFunction->front()); // Pour chaque individu, on récupère les informations dans le vector vectorFromQueue
                    queryResultFunction->pop();      //On supprime l'élément qui vient d'être extrait.
                }

                //On transforme les std::string en float et unsigned pour les champs Balance et Id
                float recuperatedBalance;
                int recuperatedId;

                std::istringstream(vectorFromQueue[5]) >> recuperatedBalance;
                std::istringstream(vectorFromQueue[0]) >> recuperatedId;

                *customer = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[4],recuperatedBalance,recuperatedId,vectorFromQueue[3]);

                queryResultFunction->pop();      //On supprime le dernier element du résultat unique , le parser '\n'

                result->push(*customer);
                j++; // L'int j correspond à l'index dans la queue , il est incrémenté a chaque boucle sur une personne
                vectorFromQueue.clear(); // Ne pas oublier de vider le vecteur à chaque individu
            }
        }
    }
    clear(queue); // queue étant défini en dehors de la fonction, par précaution on la vide à la fin de l'appel
    return *result;
}

type_consodbQueue Database::getProductsFromCategory(unsigned categorie)
{
    //On doit transformer l'int categorie en string pour effectuer la requête
    std::string idString = static_cast<std::ostringstream*>( &(std::ostringstream() << categorie) )->str();
    std::string queryString;
    Query query;

    type_consodbQueue *result(0);
    result=new type_consodbQueue;

    type_consodbTuple *conso(0);
    conso=new type_consodbTuple;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    queryResult = new std::queue<std::string> ;

    unsigned i;
    unsigned j=0;

    queryString+=" SELECT * FROM consos WHERE type=";
    queryString+=idString;
    queryString+=" ORDER BY nom ASC;";

    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);

    *queryResultFunction=*queryResult;

    std::vector<std::string> vectorFromQueue;

    for (i=0;i<=queryResultFunction->size();i++)
    {
        while(!queryResultFunction->empty())
        {
            while (queryResultFunction->front()!= "\n"&&!queryResultFunction->empty())
            {
                vectorFromQueue.push_back(queryResultFunction->front());
                queryResultFunction->pop();
            }

            float recuperatedPrice;
            unsigned recuperatedId;
            unsigned recuperatedStock;
            unsigned recuperatedCategory;

            std::istringstream(vectorFromQueue[3]) >> recuperatedPrice;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;
            std::istringstream(vectorFromQueue[4]) >> recuperatedStock;
            std::istringstream(vectorFromQueue[2]) >> recuperatedCategory;

            *conso = std::make_tuple (vectorFromQueue[1],recuperatedCategory,recuperatedPrice,recuperatedStock,recuperatedId);

            queryResultFunction->pop();
            result->push(*conso);
            j++;
            vectorFromQueue.clear();

        }
    }
    clear(queue);
    return *result;
}

type_consodbTuple Database::getProductFromId(unsigned id)
{
    //On doit transformer l'int id en string pour effectuer la requête
    std::string idString = static_cast<std::ostringstream*>( &(std::ostringstream() << id) )->str();
    std::string queryString;
    Query query;

    type_consodbTuple *conso(0);
    conso=new type_consodbTuple;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    queryResult = new std::queue<std::string> ;

    queryString+=" SELECT * FROM consos WHERE conso_id=";
    queryString+=idString;
    queryString+=" ORDER BY nom ASC;";
    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);


    *queryResultFunction=*queryResult;

    std::vector<std::string> vectorFromQueue;

    if (queryResultFunction->size()!=0)
    {
        while (queryResultFunction->front()!= "\n"&&queryResultFunction->size()>1)
        {
            vectorFromQueue.push_back(queryResultFunction->front());
            queryResultFunction->pop();
        }

        float recuperatedPrice;
        unsigned recuperatedId;
        unsigned recuperatedStock;
        unsigned recuperatedCategory;

        std::istringstream(vectorFromQueue[3]) >> recuperatedPrice;
        std::istringstream(vectorFromQueue[0]) >> recuperatedId;
        std::istringstream(vectorFromQueue[4]) >> recuperatedStock;
        std::istringstream(vectorFromQueue[2]) >> recuperatedCategory;

        *conso = std::make_tuple (vectorFromQueue[1],recuperatedCategory,recuperatedPrice,recuperatedStock,recuperatedId);
        queryResultFunction->pop();
    }
    else
    {
    }
    clear(queue);
    vectorFromQueue.clear();
    return *conso;

}

type_histdbQueue Database::getLastOperations()
{
    Query query;

    type_histdbTuple *hist(0);
    hist=new type_histdbTuple;

    unsigned i;
    unsigned j=0;
    type_histdbQueue *result(0);
    result=new type_histdbQueue;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    std::vector<std::string> vectorFromQueue;

    //Utiliser des jointures
    // From client_id -> nom + prénom
    // From conso_id -> conso + prix
    std::string queryString="SELECT historique.his_id, notes.nom, notes.prenom,consos.nom, historique.conso_price, historique.date_conso ";
    queryString+="FROM historique ";
    queryString+="LEFT JOIN consos ";
    queryString+="ON consos.conso_id = historique.conso_id ";
    queryString+="LEFT JOIN notes ";
    queryString+="ON notes.client_id=historique.client_id ";
    queryString+="ORDER BY historique.date_conso DESC LIMIT 15;";


    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);

    *queryResultFunction=*queryResult;

    for (i=0;i<=queryResultFunction->size();i++)
    {
        while(!queryResultFunction->empty())
        {
            while (queryResultFunction->front()!= "\n"&&!queryResultFunction->empty())
            {
                vectorFromQueue.push_back(queryResultFunction->front());
                queryResultFunction->pop();
            }

            float recuperatedPrice;
            unsigned recuperatedId;

            std::istringstream(vectorFromQueue[4]) >> recuperatedPrice;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;

            *hist = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[3],vectorFromQueue[5],recuperatedPrice,recuperatedId);

            queryResultFunction->pop();
            result->push(*hist);

            j++;
            vectorFromQueue.clear();
        }
    }
    clear(queue);
    return *result;

}

type_histdbQueue Database::getCustomerHist(unsigned id)
{
    Query query;
    std::string id_String = static_cast<std::ostringstream*>( &(std::ostringstream() << id) )->str();

    type_histdbTuple *hist(0);
    hist=new type_histdbTuple;

    unsigned i;
    unsigned j=0;
    type_histdbQueue *result(0);
    result=new type_histdbQueue;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    //Utiliser des jointures
    // From client_id -> nom + prénom
    // From conso_id -> conso + prix
    std::string queryString="SELECT historique.his_id, notes.nom, notes.prenom,consos.nom, historique.conso_price, historique.date_conso ";
    queryString+="FROM historique ";
    queryString+="LEFT JOIN consos ";
    queryString+="ON consos.conso_id = historique.conso_id ";
    queryString+="LEFT JOIN notes ";
    queryString+="ON notes.client_id=historique.client_id ";
    queryString+="WHERE notes.client_id=";
    queryString+=id_String;
    queryString+=" ORDER BY historique.date_conso DESC LIMIT 30;";

    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);


    *queryResultFunction=*queryResult;
    std::vector<std::string> vectorFromQueue;

    for (i=0;i<=queryResultFunction->size();i++)
    {
        while(!queryResultFunction->empty())
        {

            while (queryResultFunction->front()!= "\n"&&!queryResultFunction->empty())
            {
                vectorFromQueue.push_back(queryResultFunction->front());
                queryResultFunction->pop();
            }
            float recuperatedPrice;
            unsigned recuperatedId;

            std::istringstream(vectorFromQueue[4]) >> recuperatedPrice;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;

            *hist = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[3],vectorFromQueue[5],recuperatedPrice,recuperatedId);

            queryResultFunction->pop();
            result->push(*hist);
            j++;
            vectorFromQueue.clear();
        }
    }
    clear(queue);

    return *result;

}

type_customerdbTuple Database::getCustomerFromId(unsigned customerId)
{
    std::string queryString="";

    //On doit transformer l'int customerId en string pour effectuer la requête
    std::string idString = static_cast<std::ostringstream*>( &(std::ostringstream() << customerId) )->str();
    Query query;
    std::queue<std::string> *queryResultFunction(0);

    queryResultFunction = new std::queue<std::string> ;
    queryResult = new std::queue<std::string> ;

    unsigned j=0;

    type_customerdbTuple *customer(0);
    customer=new type_customerdbTuple;

    queryString+=" SELECT * FROM notes WHERE client_id=";
    queryString+=idString;
    queryString+=" ORDER BY nom DESC;";

    //Implémentation de la query et execution de celle ci
    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);

    *queryResultFunction=*queryResult;

    std::vector<std::string> vectorFromQueue;

    if (queryResultFunction->size()!=0)
    {
        while(queryResultFunction->front()!="\n" && !queryResultFunction->empty())
        {

            while (queryResultFunction->front()!= "\n"&& !queryResultFunction->empty())
            {
                vectorFromQueue.push_back(queryResultFunction->front());
                queryResultFunction->pop();
            }

            float recuperatedBalance;
            int recuperatedId;

            std::istringstream(vectorFromQueue[5]) >> recuperatedBalance;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;

            *customer = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[4],recuperatedBalance,recuperatedId,vectorFromQueue[3]);

            queryResultFunction->pop();
            j++;
            vectorFromQueue.clear();
        }
    }

    else
    {

    }

    clear(queue);
    return *customer;
}

int Database::createCustomerAccount(type_customerdbTuple tuple)
{
    std::string nom,prenom;
    int code;
    float balance;
    std::string categorie;
    std::string queryString="";
    Query query;

    nom=std::get<0>(tuple);
    prenom=std::get<1>(tuple);
    categorie=std::get<2>(tuple);
    balance=std::get<3>(tuple);

    //Il faut transfomer les int et float en std::string
    //std::string categorieString = static_cast<std::ostringstream*>( &(std::ostringstream() << categorie) )->str();
    std::string balanceString = static_cast<std::ostringstream*>( &(std::ostringstream() << balance) )->str();

    queryString+="INSERT INTO notes (nom,prenom,type,compte) VALUES (";
    queryString+=nom;
    queryString+=", ";
    queryString+=prenom;
    queryString+=", ";
    queryString+=categorie;
    queryString+=", ";
    queryString+=balanceString;
    queryString+=");";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::editCustomerAccount(type_customerdbTuple tuple)
{
    int code;

    std::string categorie,nom,prenom;
    unsigned id;
    float balance;
    std::string queryString="";
    Query query;

    nom=std::get<0>(tuple);
    prenom=std::get<1>(tuple);
    categorie=std::get<2>(tuple);
    balance=std::get<3>(tuple);
    id=std::get<4>(tuple);

    //std::string categorieString = static_cast<std::ostringstream*>( &(std::ostringstream() << categorie) )->str();
    std::string balanceString = static_cast<std::ostringstream*>( &(std::ostringstream() << balance) )->str();
    std::string idString = static_cast<std::ostringstream*>( &(std::ostringstream() << id) )->str();

    queryString+="UPDATE notes";
    queryString+="SET nom=";
    queryString+=nom;
    queryString+=", prenom=";
    queryString+=prenom;
    queryString+=", type=";
    queryString+=categorie;
    queryString+=", balance=";
    queryString+=balanceString;
    queryString+="WHERE client_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::deleteCustomerAccount(int id)
{
    int code;
    Query query;
    std::string queryString="";
    std::string idString = static_cast<std::ostringstream*>( &(std::ostringstream() << id) )->str();

    queryString+="DELETE FROM notes WHERE client_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::createProduct(type_consodbTuple tuple)
{
    std::string nom;
    int code;
    float prix;
    int stock=0;
    int categorie;
    std::string queryString="";
    Query query;

    nom=std::get<0>(tuple);
    categorie=std::get<1>(tuple);
    prix=std::get<2>(tuple);


    //Il faut transfomer les int et float en std::string
    std::string stockString = static_cast<std::ostringstream*>( &(std::ostringstream() << stock) )->str();
    std::string categorieString = static_cast<std::ostringstream*>( &(std::ostringstream() << categorie) )->str();
    std::string priceString = static_cast<std::ostringstream*>( &(std::ostringstream() << prix) )->str();

    queryString+="INSERT INTO notes (nom,type,prix,stock) VALUES (";
    queryString+=nom;
    queryString+=", ";
    queryString+=categorieString;
    queryString+=", ";

    queryString+=priceString;
    queryString+=", ";
    queryString+=stockString;
    queryString+=");";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::editProduct(type_consodbTuple tuple)
{
    std::string nom;
    int code;
    unsigned id;
    int stock;
    int categorie;
    float price;
    std::string queryString="";
    Query query;

    nom=std::get<0>(tuple);
    categorie=std::get<1>(tuple);
    price=std::get<2>(tuple);
    stock=std::get<3>(tuple);
    id=std::get<4>(tuple);

    std::string categorieString = static_cast<std::ostringstream*>( &(std::ostringstream() << categorie) )->str();
    std::string stockString = static_cast<std::ostringstream*>( &(std::ostringstream() << stock) )->str();
    std::string priceString = static_cast<std::ostringstream*>( &(std::ostringstream() << price) )->str();
    std::string idString = static_cast<std::ostringstream*>( &(std::ostringstream() << id) )->str();

    queryString+="UPDATE consos";
    queryString+="SET nom=";
    queryString+=nom;
    queryString+=", type=";
    queryString+=categorieString;
    queryString+=", prix=";
    queryString+=priceString;
    queryString+=", stock=";
    queryString+=stockString;
    queryString+="WHERE conso_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::deleteProduct(int id)
{
    int code;
    Query query;
    std::string queryString="";
    std::string idString = static_cast<std::ostringstream*>( &(std::ostringstream() << id) )->str();

    queryString+="DELETE FROM consos WHERE conso_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}
