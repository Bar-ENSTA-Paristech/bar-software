#ifndef QUERY_H
#define QUERY_H

#include <string>

class Query
{
public:
    Query();
    const char* getQuery();
    int getStatus();
    bool getVerbose();
    void setQuery(std::string _query);
    void setQueryStatus(int _status);
    void setVerbose(bool _verbose);

private:
    const char* query;
    int status;
    bool verbose;// 0=discret/1=verbose
};

#endif // QUERY_H
