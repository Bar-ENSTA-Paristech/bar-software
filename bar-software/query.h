#ifndef QUERY_H
#define QUERY_H

#include <string>

class Query
{
public:
    Query();
    std::string getQuery();
    int getStatus();
    bool getVerbose();
    void setQuery(const std::string _query);
    void setQueryStatus(int _status);
    void setVerbose(bool _verbose);

private:
    std::string query;
    int status;
    bool verbose;// 0=discret/1=verbose
};

#endif // QUERY_H
