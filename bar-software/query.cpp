#include "query.h"
#include <iostream>
#include <cstring>

#include <QDebug>

Query::Query()
{
}

char* Query::getQuery()
{
        return query;
}

void Query::setQuery(std::string _query)
{
    char* query_array = new char[_query.length()+1];
    strcpy (query_array,_query.c_str());
    //Copie de _query dans query_array

    query=query_array;

    qDebug()<<query_array;

    delete query_array;
    return ;
}
