#ifndef PLOTTING_H
#define PLOTTING_H

#include <vector>
#include <utility>
#include "database.h"
#include "controller.h"
#include "qcustomplot.h"
#include "structures.h"


class Database;

class Plotting
{
public:
    Plotting();

    db_dataarray customerConsumption (int id,int scale,int type);
    db_dataarray customerBalance (int id,int scale);

    db_dataarray productConsumption (int id,int scale);
    db_dataarray productStock (int id,int scale);

    db_dataarray totalConsumption (int scale,int type);

    db_dataarray stockValue(int scale);
    db_dataarray accountValue(int scale);
    db_dataarray cashValue (int scale);

    void plot(db_dataarray);

    void setDb(sqlite3*);
    sqlite3* getDb();

private:
Database db;
};

#endif // PLOTTING_H
