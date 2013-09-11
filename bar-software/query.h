#ifndef QUERY_H
#define QUERY_H

#include <string>

class Query
{
public:
    Query();
    char* getQuery();
    int getQueryStatus();
    void setQuery(const std::string _query);
    void setQueryStatus(int _status);

private:
    char* query;
    int status;
};

#endif // QUERY_H
