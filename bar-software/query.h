#ifndef QUERY_H
#define QUERY_H

#include <string>

class Query
{
public:
    Query();
    char* getQuery();
    void setQuery(const std::string _query);

private:
    char* query;
};

#endif // QUERY_H
