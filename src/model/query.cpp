#include "query.h"
#include <iostream>

Query::Query(): query(""),status(1),verbose(false)
{
}

 const char* Query::getQuery()
{
        return query;
}

bool Query::getVerbose()
{
    return verbose;
}

void Query::setQuery(std::string _query)
{

    query=_query.data();
    return;
}

void Query::setVerbose(bool _verbose)
{
    verbose=_verbose;
    return;
}
