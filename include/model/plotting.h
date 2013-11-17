#ifndef PLOTTING_H
#define PLOTTING_H

#include <vector>
#include <utility>
#include "database.h"
#include "../../include/controller/controller.h"
#include "../../resources/lib/qcustomplot.h"

typedef std::pair< std::vector< double > , std::vector< double > > db_dataarray;

class Database;

class Plotting
{
public:
    Plotting();

    db_dataarray customerConsumption (int id,int scale,int type);
    db_dataarray customerAccount (int id,int scale);

    db_dataarray productConsumption (int id,int scale);
    db_dataarray productStock (int id,int scale);

    db_dataarray totalConsumption (int scale,int type);

    db_dataarray stockValue(int scale);
    db_dataarray cashValue (int scale);

    void plot(db_dataarray);

    void setDb(sqlite3*);
    sqlite3* getDb();

private:
Database db;
};

#endif // PLOTTING_H
