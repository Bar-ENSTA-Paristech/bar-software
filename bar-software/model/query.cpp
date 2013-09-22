#include "query.h"
#include <iostream>

Query::Query(): query(""),status(1),verbose(false)
{
}

std::string Query::getQuery()
{
        return query;
}

bool Query::getVerbose()
{
    return verbose;
}

void Query::setQuery(std::string _query)
{

    query=_query;
    return;
}

void Query::setVerbose(bool _verbose)
{
    verbose=_verbose;
    return;
}
