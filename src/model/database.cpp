#include "database.h"



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
    queryResult = new std::queue<std::string> ;
}

int Database::openDatabase()
{
    //Modification de la configuration de sqlite pour accepter les URI (gestion des repertoires)
    sqlite3_config(SQLITE_CONFIG_URI,1);

    std::cout<<"Tentative d'ouverture de db"<<std::endl;
    int i=0;
    QString Path;
    Path=GLOBAL_PATH+"resources/BDD/bar.db";
    char DBfilename[100];
    for (i=0;i<Path.size();i++)
    {
        DBfilename[i]=Path.at(i).toLatin1();
    }
    DBfilename[i]='\0';
    std::cout<<DBfilename<<std::endl;
    int coderesult=sqlite3_open_v2(DBfilename //Database filename
                                   ,&handle //adresse mémoire de la BDD
                                   , SQLITE_OPEN_READWRITE
                                   , NULL); // Default VFS


    if (coderesult!=SQLITE_OK)
        std::cout<<sqlite3_errmsg(handle)<<std::endl;
    else{
        //handle=DB;
        std::cout<<"OK"<<std::endl;
    }

    return coderesult;

}

int Database::closeDatabase()
{
    std::cout<<"Tentative de fermeture de db"<<std::endl;
    int coderesult=sqlite3_close_v2(handle);

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
    const char* query_string=_query.getQuery();
    bool verbose=_query.getVerbose();

    int coderesult;
    char*zErrMsg;

    coderesult = sqlite3_exec(handle, query_string, callback, 0, &zErrMsg);

    if(verbose==true)
    {
        if( coderesult!=SQLITE_OK )
        {
            std::cout<<"SQL error: "<<zErrMsg<<"\n"<<std::endl;
            sqlite3_free(zErrMsg);
        }
        else
        {
            std::cout<<"The following query has been correctly executed: "<<query_string<<std::endl;
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

    test_q.setQuery("CREATE TABLE IF NOT EXISTS `acces` (`password` varchar(15) INTEGER PRIMARY KEY,`id` unsigned int(10) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `categories` (`cat_id`INTEGER PRIMARY KEY,`categorie` varchar(20) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `consos` (`conso_id` INTEGER PRIMARY KEY,`nom` varchar(25) NOT NULL DEFAULT 'NULL',`type` int(11) DEFAULT NULL,`prix` float DEFAULT NULL,`stock` int(11) DEFAULT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `historique` (`his_id` INTEGER PRIMARY KEY,`client_id` int(11) NOT NULL,`conso_id` int(11) NOT NULL,`conso_price` float DEFAULT NULL,`date_conso` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `historique_save` (`his_id` INTEGER PRIMARY KEY,`client_id` int(11) NOT NULL,`conso_id` int(11) NOT NULL,`conso_price` float DEFAULT NULL,`date_conso` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `historique_deleted_account` (`his_id` INTEGER PRIMARY KEY,`client_id` int(11) NOT NULL,`conso_id` int(11) NOT NULL,`conso_price` float DEFAULT NULL,`date_conso` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `notes` (`client_id` INTEGER PRIMARY KEY,`nom` varchar(25) NOT NULL,`prenom` varchar(25) NOT NULL,`login` varchar(25) NOT NULL,`type` int(11) NOT NULL,`compte` float NOT NULL,`vip` tinyint(1)) ;");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `prix_consos` (`id_conso` INTEGER PRIMARY KEY,`prix_precedent` float DEFAULT NULL,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `types_conso` (`type_conso_id` INTEGER PRIMARY KEY,`nom_type` varchar(25) NOT NULL);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `vidage_caisse` (`type_vidage` tinyint(1) NOT NULL,`valeur` float NOT NULL,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `commande` (`commande_id` INTEGER PRIMARY KEY,`valeur` float NOT NULL,`libelle` varchar(100) ,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
    coderesult+=executeQuery(test_q);
    test_q.setQuery("CREATE TABLE IF NOT EXISTS `achats` (`commande_id` INTEGER PRIMARY KEY,`conso_id` int(11) NOT NULL,`quantite` int(11),`prix_unitaire` float(11) ,`date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP);");
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

db_customerQueue Database::searchCustomer(std::string &string,int cat)
{
    std::string catstring=std::to_string(cat);
    std::string searchString=string;
    std::string queryString="";   //Initialisation du string qui contiendra la requête SQL

    Query query; //Initialisation de la requête

    std::queue<std::string> *queryResultFunction(0);  //
    queryResultFunction = new std::queue<std::string> ;
    delete queryResult;
    queryResult = new std::queue<std::string> ;   //queryResult n'est alloué que dans les fonctions l'utilisant

    /*
     * Remarque sur queryResultFunction et queryResult
     *    queryResult est définie en dehors de toute méthode. Cela est du a la syntaxe "fermée" de sqlite3_exec et de son argument callback.
     *    Par la suite queryResultFunction est définie comme pointant vers la même adresse que queryResult. Cela revient à un passage par adresse
     *    un peu dégeu mais cette solution fonctionne.
    */
    unsigned i;
    unsigned j=0;
    db_customerQueue result; //On initialise la queue de tuple qui sera retournée à la fin au controlleur

    //On initialise aussi le tuple correspondant
    db_customerTuple customer;

    //Formation du string de query adapté

    if (cat==0)
    {
        queryString+=" SELECT * FROM notes WHERE nom LIKE '";
        queryString+=searchString;
        queryString+="%";
        queryString+="' OR prenom LIKE '";
        queryString+=searchString;
        queryString+="%";
        queryString+="' ORDER BY nom ASC;";
    }
    else
    {
        queryString+=" SELECT * FROM notes WHERE type='";
        queryString+=catstring;
        queryString+="' AND (nom LIKE '";
        queryString+=searchString;
        queryString+="%' OR prenom LIKE '";
        queryString+=searchString;
        queryString+="%') ORDER BY nom ASC;";
    }

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
                unsigned recuperatedCategory;

                std::istringstream(vectorFromQueue[4]) >> recuperatedCategory;
                std::istringstream(vectorFromQueue[5]) >> recuperatedBalance;
                std::istringstream(vectorFromQueue[0]) >> recuperatedId;

                //*customer = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[4],recuperatedBalance,recuperatedId,vectorFromQueue[3]);
                customer.setCustomerId(recuperatedId);
                customer.setCustomerName(vectorFromQueue[1]);
                customer.setCustomerFirstname(vectorFromQueue[2]);
                customer.setCustomerLogin(vectorFromQueue[3]);
                customer.setCustomerCategory(recuperatedCategory);
                customer.setCustomerBalance(recuperatedBalance);

                queryResultFunction->pop();      //On supprime le dernier element du résultat unique , le parser '\n'

                result.push(customer);
                j++; // L'int j correspond à l'index dans la queue , il est incrémenté a chaque boucle sur une personne
                vectorFromQueue.clear(); // Ne pas oublier de vider le vecteur à chaque individu
            }
        }
    }
    clear(queue); // queue étant défini en dehors de la fonction, par précaution on la vide à la fin de l'appel
    delete queryResultFunction;
    return result;

}

db_productQueue Database::getAllProducts()
{
    std::string queryString;
    Query query;

    db_productQueue result;

    db_productTuple *conso(0);
    conso=new db_productTuple;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    delete queryResult;
    queryResult = new std::queue<std::string> ;

    unsigned i;
    unsigned j=0;

    queryString+=" SELECT * FROM consos";
    queryString+=" ORDER BY conso_id ASC;";

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

            //conso = std::make_tuple (vectorFromQueue[1],recuperatedCategory,recuperatedPrice,recuperatedStock,recuperatedId);
            conso->setProductId(recuperatedId);
            conso->setProductName(vectorFromQueue[1]);
            conso->setProductPrice(recuperatedPrice);
            conso->setProductStock(recuperatedStock);
            conso->setProductCategory(recuperatedCategory);

            result.push(*conso);
            queryResultFunction->pop();
            j++;
            vectorFromQueue.clear();

        }
    }
    delete conso;
    delete queryResultFunction;
    clear(queue);
    return result;
}

db_categoryQueue Database::getProdCategories()
{
    Query query;

    db_categoryTuple *cat(0);
    cat=new db_categoryTuple;

    unsigned i;
    unsigned j=0;
    db_categoryQueue result;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    std::vector<std::string> vectorFromQueue;

    std::string queryString =" SELECT * FROM categ_consos";
    queryString+=" ORDER BY id ASC;";


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
            unsigned recuperatedId;

            std::istringstream(vectorFromQueue[0]) >> recuperatedId;

            //*cat = std::make_tuple (vectorFromQueue[1],recuperatedId);

            cat->setCategoryId(recuperatedId);
            cat->setCategoryName(vectorFromQueue[1]);

            queryResultFunction->pop();
            result.push(*cat);

            j++;
            vectorFromQueue.clear();
        }
    }
    clear(queue);
    delete cat;
    delete queryResultFunction;
    return result;
}

db_categoryQueue Database::getCustCategories()
{
    Query query;

    db_categoryTuple *cat(0);
    cat=new db_categoryTuple;

    unsigned i;
    unsigned j=0;
    db_categoryQueue result;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    std::vector<std::string> vectorFromQueue;

    std::string queryString =" SELECT * FROM categ_cust";
    queryString+=" ORDER BY id ASC;";


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
            int recuperatedId;

            std::istringstream(vectorFromQueue[0]) >> recuperatedId;

            cat->setCategoryId(recuperatedId);
            cat->setCategoryName(vectorFromQueue[1]);

            queryResultFunction->pop();
            result.push(*cat);

            j++;
            vectorFromQueue.clear();
        }
    }
    clear(queue);
    delete cat;
    delete queryResultFunction;
    return result;
}


db_customerQueue Database::getCustomerFromCategory(int id)
{
    std::string idstring=std::to_string(id);

    std::string queryString="";
    Query query; //Initialisation de la requête

    std::queue<std::string> *queryResultFunction(0);  //
    queryResultFunction = new std::queue<std::string> ;

    delete queryResult;
    queryResult = new std::queue<std::string> ;

    unsigned i;
    unsigned j=0;
    db_customerQueue result; //On initialise la queue de tuple qui sera retournée à la fin au controlleur

    //On initialise aussi le tuple correspondant
    db_customerTuple customer;

    //Formation du string de query adapté

    queryString+=" SELECT * FROM notes WHERE type='";
    queryString+=idstring;
    queryString+="' ORDER BY nom ASC;";

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
                int recuperatedCategory;

                std::istringstream(vectorFromQueue[4]) >> recuperatedCategory;
                std::istringstream(vectorFromQueue[5]) >> recuperatedBalance;
                std::istringstream(vectorFromQueue[0]) >> recuperatedId;

                //*customer = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[4],recuperatedBalance,recuperatedId,vectorFromQueue[3]);
                customer.setCustomerId(recuperatedId);
                customer.setCustomerName(vectorFromQueue[1]);
                customer.setCustomerFirstname(vectorFromQueue[2]);
                customer.setCustomerLogin(vectorFromQueue[3]);
                customer.setCustomerCategory(recuperatedCategory);
                customer.setCustomerBalance(recuperatedBalance);

                queryResultFunction->pop();      //On supprime le dernier element du résultat unique , le parser '\n'

                result.push(customer);
                j++; // L'int j correspond à l'index dans la queue , il est incrémenté a chaque boucle sur une personne
                vectorFromQueue.clear(); // Ne pas oublier de vider le vecteur à chaque individu
            }
        }
    }
    clear(queue); // queue étant défini en dehors de la fonction, par précaution on la vide à la fin de l'appel
    delete queryResultFunction;
    return result;


}

db_productQueue Database::getProductsFromCategory(int categorie)
{
    //On doit transformer l'int categorie en string pour effectuer la requête
    std::string idString = std::to_string(categorie);
    std::string queryString;
    Query query;

    db_productQueue result;

    db_productTuple *conso(0);
    conso=new db_productTuple;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    delete queryResult;
    queryResult = new std::queue<std::string> ;

    int i;
    int j=0;

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
            int recuperatedId;
            int recuperatedStock;
            int recuperatedCategory;

            std::istringstream(vectorFromQueue[3]) >> recuperatedPrice;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;
            std::istringstream(vectorFromQueue[4]) >> recuperatedStock;
            std::istringstream(vectorFromQueue[2]) >> recuperatedCategory;

            //*conso = std::make_tuple (vectorFromQueue[1],recuperatedCategory,recuperatedPrice,recuperatedStock,recuperatedId);
            conso->setProductId(recuperatedId);
            conso->setProductName(vectorFromQueue[1]);
            conso->setProductPrice(recuperatedPrice);
            conso->setProductStock(recuperatedStock);
            conso->setProductCategory(recuperatedCategory);

            queryResultFunction->pop();
            result.push(*conso);
            j++;
            vectorFromQueue.clear();

        }
    }
    clear(queue);
    delete conso;
    delete queryResultFunction;
    return result;
}

db_productTuple Database::getProductFromId(unsigned id)
{
    //On doit transformer l'int id en string pour effectuer la requête
    std::string idString = std::to_string(id);
    std::string queryString;
    Query query;

    db_productTuple conso;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    delete queryResult;
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
        int recuperatedCategory;

        std::istringstream(vectorFromQueue[3]) >> recuperatedPrice;
        std::istringstream(vectorFromQueue[0]) >> recuperatedId;
        std::istringstream(vectorFromQueue[4]) >> recuperatedStock;
        std::istringstream(vectorFromQueue[2]) >> recuperatedCategory;

        //*conso = std::make_tuple (vectorFromQueue[1],recuperatedCategory,recuperatedPrice,recuperatedStock,recuperatedId);
        conso.setProductId(recuperatedId);
        conso.setProductName(vectorFromQueue[1]);
        conso.setProductPrice(recuperatedPrice);
        conso.setProductStock(recuperatedStock);
        conso.setProductCategory(recuperatedCategory);

        queryResultFunction->pop();
    }
    else
    {
    }
    clear(queue);
    delete queryResultFunction;
    vectorFromQueue.clear();
    return conso;

}

db_histQueue Database::getFullHist()
{
    Query query;

    db_histTuple *hist(0);
    hist=new db_histTuple;

    unsigned i;
    unsigned j=0;
    db_histQueue result;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    std::vector<std::string> vectorFromQueue;

    //Utiliser des jointures
    // From client_id -> nom + prénom
    // From conso_id -> conso + prix
    std::string queryString="SELECT historique.his_id, notes.nom, notes.prenom,consos.nom, historique.conso_price, historique.date_conso, historique.client_id,historique.conso_id ";
    queryString+="FROM historique ";
    queryString+="LEFT JOIN consos ";
    queryString+="ON consos.conso_id = historique.conso_id ";
    queryString+="LEFT JOIN notes ";
    queryString+="ON notes.client_id=historique.client_id ";
    queryString+="ORDER BY historique.date_conso DESC;";


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
            unsigned recuperatedClientId;
            unsigned recuperatedProductId;

            std::istringstream(vectorFromQueue[4]) >> recuperatedPrice;
            std::istringstream(vectorFromQueue[0]) >> recuperatedId;
            std::istringstream(vectorFromQueue[6]) >> recuperatedClientId;
            std::istringstream(vectorFromQueue[7]) >> recuperatedProductId;

            //*hist = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[3],vectorFromQueue[5],recuperatedPrice,recuperatedId);
            hist->setHistId(recuperatedId);
            hist->setHistName(vectorFromQueue[1]);
            hist->setHistFirstName(vectorFromQueue[2]);
            hist->setHistDate(vectorFromQueue[5]);
            hist->setHistPrice(recuperatedPrice);
            hist->setHistOperation(vectorFromQueue[3]);
            hist->setHistCustomerId(recuperatedClientId);
            hist->setHistProductId(recuperatedProductId);

            result.push(*hist);
            queryResultFunction->pop();
            j++;
            vectorFromQueue.clear();
        }
    }
    clear(queue);
    delete hist;
    delete queryResultFunction;
    return result;
}

db_histQueue Database::getLastOperations(int limit)
{
    Query query;
    std::string LimitString = std::to_string(limit);
    db_histTuple *hist(0);
    hist=new db_histTuple;

    unsigned i;
    unsigned j=0;
    db_histQueue result;

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
    queryString+="ORDER BY historique.date_conso DESC LIMIT ";
    queryString+=LimitString;
    queryString+=";";

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

            //*hist = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[3],vectorFromQueue[5],recuperatedPrice,recuperatedId);
            hist->setHistId(recuperatedId);
            hist->setHistName(vectorFromQueue[1]);
            hist->setHistFirstName(vectorFromQueue[2]);
            hist->setHistDate(vectorFromQueue[5]);
            hist->setHistPrice(recuperatedPrice);
            hist->setHistOperation(vectorFromQueue[3]);

            result.push(*hist);
            queryResultFunction->pop();
            j++;
            vectorFromQueue.clear();
        }
    }
    clear(queue);
    delete hist;
    delete queryResultFunction;
    return result;

}
// hist.conso_price n'est pas dans la db actuellement, il faudra faire avec conso.price
//en réalité, on utilisera conso.price pour hist_older=avant la maj
db_histQueue Database::getCustomerHist(unsigned id, bool old)
{
    Query query;
    std::string id_String = std::to_string(id);

    db_histTuple *hist(0);
    hist=new db_histTuple;

    unsigned i;
    unsigned j=0;
    db_histQueue result;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    if (old!=true)
    {
    //Utiliser des jointures
    // From client_id -> nom + prénom
    // From conso_id -> conso + prix
    std::string queryString="SELECT notes.nom, notes.prenom,consos.nom, consos.prix, hist.date_conso ";
    queryString+="FROM hist ";
    queryString+="LEFT JOIN consos ";
    queryString+="ON consos.conso_id = hist.conso_id ";
    queryString+="LEFT JOIN notes ";
    queryString+="ON notes.client_id=hist.client_id ";
    queryString+="WHERE notes.client_id=";
    queryString+=id_String;
    queryString+=" ORDER BY hist.date_conso DESC ;";

    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);
}
    else
    {
        std::string queryString="SELECT notes.nom, notes.prenom,consos.nom, consos.prix, historique_save.date_conso ";
        queryString+="FROM historique_save ";
        queryString+="LEFT JOIN consos ";
        queryString+="ON consos.conso_id = historique_save.conso_id ";
        queryString+="LEFT JOIN notes ";
        queryString+="ON notes.client_id=historique_save.client_id ";
        queryString+="WHERE notes.client_id=";
        queryString+=id_String;
        queryString+=" ORDER BY historique.date_conso DESC ;";

        query.setQuery(queryString);
        query.setVerbose(1);
        executeQuery(query);

    }


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

            //*hist = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[3],vectorFromQueue[5],recuperatedPrice,recuperatedId);
            hist->setHistId(recuperatedId);
            hist->setHistName(vectorFromQueue[1]);
            hist->setHistFirstName(vectorFromQueue[2]);
            hist->setHistDate(vectorFromQueue[5]);
            hist->setHistPrice(recuperatedPrice);
            hist->setHistOperation(vectorFromQueue[3]);

            queryResultFunction->pop();
            result.push(*hist);
            j++;
            vectorFromQueue.clear();
        }
    }
    clear(queue);
    delete hist;
    delete queryResultFunction;
    return result;

}

db_histQueue Database::getProductHist(unsigned id,bool old)
{
    Query query;
    std::string id_String = std::to_string(id);

    db_histTuple *hist(0);
    hist=new db_histTuple;

    unsigned i;
    unsigned j=0;
    db_histQueue result;

    std::queue<std::string> *queryResultFunction(0);
    queryResultFunction = new std::queue<std::string> ;

    if (old!=true)
    {
        //Utiliser des jointures
        // From client_id -> nom + prénom
        // From conso_id -> conso + prix
        std::string queryString="SELECT historique.his_id, notes.nom, notes.prenom,consos.nom, consos.prix, historique.date_conso ";
        queryString+="FROM historique ";
        queryString+="LEFT JOIN notes ";
        queryString+="ON notes.client_id=historique.client_id ";
        queryString+="LEFT JOIN consos ";
        queryString+="ON consos.conso_id = historique.conso_id ";
        queryString+="WHERE consos.conso_id=";
        queryString+=id_String;
        queryString+=" ORDER BY historique.date_conso DESC;";

        query.setQuery(queryString);
        query.setVerbose(1);
        executeQuery(query);
    }

    else
    {
        std::string queryString="SELECT historique_save.his_id, notes.nom, notes.prenom,consos.nom, consos.prix, historique_save.date_conso ";
        queryString+="FROM historique_save ";
        queryString+="LEFT JOIN notes ";
        queryString+="ON notes.client_id=historique_save.client_id ";
        queryString+="LEFT JOIN consos ";
        queryString+="ON consos.conso_id = historique_save.conso_id ";
        queryString+="WHERE consos.conso_id=";
        queryString+=id_String;
        queryString+=" ORDER BY historique_save.date_conso DESC;";

        query.setQuery(queryString);
        query.setVerbose(1);
        executeQuery(query);
    }


    *queryResultFunction=*queryResult;
    std::vector<std::string> vectorFromQueue;

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

            //*hist = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[3],vectorFromQueue[5],recuperatedPrice,recuperatedId);
            hist->setHistId(recuperatedId);
            hist->setHistName(vectorFromQueue[1]);
            hist->setHistFirstName(vectorFromQueue[2]);
            hist->setHistDate(vectorFromQueue[5]);
            hist->setHistPrice(recuperatedPrice);
            hist->setHistOperation(vectorFromQueue[3]);

            queryResultFunction->pop();
            result.push(*hist);
            j++;
            vectorFromQueue.clear();
        }
    clear(queue);
    delete hist;
    delete queryResultFunction;
    return result;
}

db_customerTuple Database::getCustomerFromId(unsigned customerId)
{
    std::string queryString="";

    //On doit transformer l'int customerId en string pour effectuer la requête
    std::string idString = std::to_string(customerId);
    Query query;
    std::queue<std::string> *queryResultFunction(0);

    queryResultFunction = new std::queue<std::string> ;
    delete queryResult;
    queryResult = new std::queue<std::string> ;


    db_customerTuple customer;

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

        while (queryResultFunction->front()!= "\n"&& !queryResultFunction->empty())
        {
            vectorFromQueue.push_back(queryResultFunction->front());
            queryResultFunction->pop();
        }

        float recuperatedBalance;
        int recuperatedId, recuperatedCategory;

        std::istringstream(vectorFromQueue[5]) >> recuperatedBalance;
        std::istringstream(vectorFromQueue[0]) >> recuperatedId;
        std::istringstream(vectorFromQueue[4]) >> recuperatedCategory;

        //*customer = std::make_tuple (vectorFromQueue[1],vectorFromQueue[2],vectorFromQueue[4],recuperatedBalance,recuperatedId,vectorFromQueue[3]);
        customer.setCustomerId(recuperatedId);
        customer.setCustomerName(vectorFromQueue[1]);
        customer.setCustomerFirstname(vectorFromQueue[2]);
        customer.setCustomerLogin(vectorFromQueue[3]);
        customer.setCustomerCategory(recuperatedCategory);
        customer.setCustomerBalance(recuperatedBalance);


        queryResultFunction->pop();
    }
    vectorFromQueue.clear();
    delete queryResultFunction;
    clear(queue);
    return customer;
}


std::string Database::getPassword (std::string &login)
{
    std::string queryString,result;
    Query query;
    std::queue<std::string> *queryResultFunction(0);  //
    queryResultFunction = new std::queue<std::string> ;

    queryString+=" SELECT password FROM passwords WHERE login LIKE '";
    queryString+=login;
    queryString+="'";

    query.setQuery(queryString);
    query.setVerbose(1);
    executeQuery(query);

    *queryResultFunction=*queryResult;
    result=queryResultFunction->front();
    queryResultFunction->pop();
    delete queryResultFunction;
    clear(queue);
    return result;
}




int Database::createCustomerAccount(db_customerTuple tuple)
{
    std::string nom,prenom,login;
    int code,categorie;
    float balance;


    std::string queryString="";
    Query query;

    nom=tuple.getCustomerName();
    prenom=tuple.getCustomerFirstname();
    login=tuple.getCustomerLogin();
    categorie=tuple.getCustomerCategory();
    balance=tuple.getCustomerBalance();

    //Il faut transfomer les int et float en std::string
    //std::string categorieString = static_cast<std::ostringstream*>( &(std::ostringstream() << categorie) )->str();
    std::string balanceString = std::to_string(balance);
    std::string categorieString = std::to_string(categorie);
    convertToPointDecimal(balanceString); // peut contenir une virgule (notemment sous linux)

    queryString+="INSERT INTO notes (nom,prenom,login,type,compte) VALUES ('";
    queryString+=nom;
    queryString+="', '";
    queryString+=prenom;
    queryString+="', '";
    queryString+=login;
    queryString+="', ";
    queryString+=categorieString;
    queryString+=", ";
    queryString+=balanceString;
    queryString+=");";

    query.setQuery(queryString);
    std::cout << queryString << std::endl;
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::editCustomerAccount(db_customerTuple tuple)
{
    int code;

    std::string nom,prenom,login;
    unsigned id, categorie;
    float balance;
    std::string queryString="";
    Query query;

    nom=tuple.getCustomerName();
    prenom=tuple.getCustomerFirstname();
    login=tuple.getCustomerLogin();
    categorie=tuple.getCustomerCategory();
    balance=tuple.getCustomerBalance();
    id=tuple.getCustomerId();

    //std::string categorieString = static_cast<std::ostringstream*>( &(std::ostringstream() << categorie) )->str();
    std::string balanceString = std::to_string(balance);
    convertToPointDecimal(balanceString); // peut contenir une virgule (notemment sous linux)
    std::string idString = std::to_string(id);
    std::string categorieString = std::to_string(categorie);

    queryString+="UPDATE notes ";
    queryString+="SET nom=";
    queryString+="'";
    queryString+=nom;
    queryString+="'";
    queryString+=", prenom=";
    queryString+="'";
    queryString+=prenom;
    queryString+="'";
    queryString+=", login=";
    queryString+="'";
    queryString+=login;
    queryString+="'";
    queryString+=", type=";
    queryString+="'";
    queryString+=categorieString;
    queryString+="'";
    queryString+=", compte=";
    queryString+=balanceString;
    queryString+=" WHERE client_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    std::cout<<queryString<<std::endl;
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::deleteCustomerAccount(int id)
{
    int code;
    Query query;
    std::string queryString="";
    std::string idString = std::to_string(id);

    queryString+="DELETE FROM notes WHERE client_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::createProduct(db_productTuple tuple)
{
    std::string nom;
    int code;
    float prix;
    int stock=0;
    int categorie;
    std::string queryString="";
    Query query;

    nom=tuple.getProductName();
    categorie=tuple.getProductCategory();
    prix=tuple.getProductPrice();
    stock=tuple.getProductStock();

    //Il faut transfomer les int et float en std::string
    std::string stockString = std::to_string(stock);
    std::string categorieString = std::to_string(categorie);
    std::string priceString = std::to_string(prix);
    convertToPointDecimal(priceString); // peut contenir une virgule (notemment sous linux)

    queryString+="INSERT INTO consos (nom,type,prix,stock) VALUES (";
    queryString+="'";
    queryString+=nom;
    queryString+="'";
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

int Database::editProduct(db_productTuple tuple)
{
    std::string nom;
    int code;
    unsigned id;
    int stock;
    int categorie;
    float price;
    std::string queryString="";
    Query query;

    nom=tuple.getProductName();
    categorie=tuple.getProductCategory();
    price=tuple.getProductPrice();
    stock=tuple.getProductStock();
    id=tuple.getProductId();

    std::string categorieString = std::to_string(categorie);
    std::string stockString = std::to_string(stock);
    std::string priceString = std::to_string(price);
    convertToPointDecimal(priceString); // peut contenir une virgule (notemment sous linux)
    std::string idString = std::to_string(id);

    queryString+="UPDATE consos ";
    queryString+="SET nom=";
    queryString+="'";
    queryString+=nom;
    queryString+="'";
    queryString+=", type=";
    queryString+=categorieString;
    queryString+=", prix=";
    queryString+=priceString;
    queryString+=", stock=";
    queryString+=stockString;
    queryString+=" WHERE conso_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    std::cout<<queryString<<std::endl;
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::deleteProduct(int id)
{
    int code;
    Query query;
    std::string queryString="";
    std::string idString = std::to_string(id);

    queryString+="DELETE FROM consos WHERE conso_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::createCategory(db_categoryTuple tuple)
{
    std::string nom;
    int code;

    std::string queryString="";
    Query query;

    nom=tuple.getCategoryName();

    //Il faut transfomer les int et float en std::string


    queryString+="INSERT INTO types_conso (nom_type) VALUES (";
    queryString+=nom;
    queryString+=");";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::deleteCategory(int id)
{
    int code;
    Query query;
    std::string queryString="";
    std::string idString = std::to_string(id);

    queryString+="DELETE FROM type_consos WHERE conso_id=";
    queryString+=idString;
    queryString+=";";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::addHist(db_histTuple tuple,bool to_old)
{

    std::string timestamp;
    float price;
    int product_id;
    int client_id;

    int code;

    std::string queryString="";
    Query query;

    QString const format="yyyy-MM-dd hh:mm:ss\0";


    price=tuple.getHistPrice();
    client_id = tuple.getHistCustomerId();
    product_id = tuple.getHistProduct_Id();

    //Il faut transfomer les int et float en std::string
    std::string productIdString = std::to_string(product_id);
    std::string priceString = std::to_string(price);
    convertToPointDecimal(priceString); // peut contenir une virgule (notemment sous linux)
    std::string clientIdString = std::to_string(client_id);

    //
    if (to_old ==false)
    {
        queryString+="INSERT INTO historique (client_id,conso_id,conso_price,date_conso) VALUES (";
        queryString+=clientIdString;
        queryString+=", ";
        queryString+=productIdString;
        queryString+=", ";
        queryString+=priceString;
        queryString+=", ";
        queryString+="CURRENT_TIMESTAMP";
        queryString+=");";
    }
    else
    {
        QDateTime DateTime=QDateTime::fromString(QString::fromStdString(tuple.getHistDate()),format);

        timestamp = QString::number(DateTime.toTime_t()).toStdString();

        queryString+="INSERT INTO historique_save (client_id,conso_id,conso_price,date_conso) VALUES (";
        queryString+=clientIdString;
        queryString+=", ";
        queryString+=productIdString;
        queryString+=", ";
        queryString+=priceString;
        queryString+=", datetime(";
        queryString+=timestamp;
        queryString+=", 'unixepoch', 'localtime'));";
    }

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::addToBar(std::pair<std::string,std::string> datas)
{
    std::string queryString="";
    int code;
    Query query;

    queryString+="INSERT INTO passwords (login,password) VALUES (";
    queryString+=datas.first;
    queryString+=", ";
    queryString+=datas.second;
    queryString+=");";

    query.setQuery(queryString);
    query.setVerbose(1);
    code=executeQuery(query);

    return (code);
}

int Database::autoDumpHist()
{
    int code;

    db_histQueue hist=this->getFullHist();
    db_histTuple tuple;
    db_histQueue toDump;

    int size=hist.size();
    int cur_hist_id;
    std::string idstring;

    if (size>=1000)
    {
        for(int i=0;i<size;i++)
        {
            if(i<1000)
            {
                hist.pop();
            }
            else
            {
                if(i==1000)
                {
                    hist.pop();
                    tuple=hist.front();
                    cur_hist_id=tuple.getHistId();
                    idstring=std::to_string(cur_hist_id);
                    toDump.push(tuple);
                }
                else
                {
                    tuple=hist.front();
                    this->addHist(tuple,true);
                    hist.pop();
                }
            }
        }

        //Do the SQL statement

        //1: Add the tuples

        //Delete old rows
        Query query;
        std::string queryString="";
        queryString+="DELETE FROM historique WHERE his_id<";
        queryString+=idstring;
        queryString+=";";

        query.setQuery(queryString);
        query.setVerbose(1);
        code=executeQuery(query);
    }

    return code;
}

void Database::convertToPointDecimal(std::string& str)
{
    unsigned n = str.size();
    for(unsigned i = 0 ; i < n ; i++)
    {
        if(str[i]==',')
            str[i]='.';
    }
}
