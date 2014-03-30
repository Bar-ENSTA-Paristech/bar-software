#include "plotting.h"
#include <QDateTime>
#include <tuple>
#include "structures.h"

Plotting::Plotting()
{
}

/* Dans toutes les méthodes de recherche, l'arg "scale" correspond à l'échelle du graphe en jours:
 */

db_dataarray Plotting::customerConsumption(int id, int scale, int numberOfPoints, int type)
{
    db.openDatabase();
    db_histQueue customer_hist = db.getCustomerHist(id,false);
    db.closeDatabase();
    db.openDatabase();
    db_histQueue customer_hist_old = db.getCustomerHist(id,true);
    db.closeDatabase();
    db_histTuple customer_operation;
    QString format="yyyy-MM-dd hh:mm:ss";
    QDateTime qtime=QDateTime::currentDateTime();
    QDateTime now=QDateTime::currentDateTime();
    int k;
    //recupérer les anciennes données quand getCustomer_Old_Hist sera implémenté
    std::vector<double> x(numberOfPoints), y(numberOfPoints);
    db_dataarray Values=make_pair(x,y);
    int now_int = QDateTime::currentDateTime().toTime_t();
    //On remplit le tableau, qui contient les dates et les valeurs:
    // Values.first contient les dates,
    // Values.second les valeurs.

    for (int i=0;i<numberOfPoints;i++)
    {
        Values.first[i]=0;
        Values.second[i]=0;
    }
    if (!customer_hist.empty())
    {
        for (unsigned j=0; j<customer_hist.size();j++)
        {
            customer_operation=customer_hist.front();
            customer_hist.pop();
            std::string operation_time=customer_operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<numberOfPoints;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }
            if (k<numberOfPoints && k>=0)
            {
                Values.second[k]++;
            }

        }
    }
    else{}

    if (!customer_hist_old.empty())
    {
        for (unsigned j=0; j<customer_hist_old.size();j++)
        {
            customer_operation=customer_hist_old.front();
            customer_hist_old.pop();
            std::string operation_time=customer_operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<numberOfPoints;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }
            if (k<numberOfPoints && k>=0)
            {
                Values.second[k]++;
            }
        }
    }
    else{}
    return (Values);
}

db_dataarray Plotting::customerBalance(int id, int scale, int numberOfPoints)
{
    db.openDatabase();
    db_histQueue customer_hist_old = db.getCustomerHist(id,true);
    db.closeDatabase();
    db.openDatabase();
    db_histQueue customer_hist = db.getCustomerHist(id,false);
    db.closeDatabase();
    db.openDatabase();
    db_customerTuple customer_data =db.getCustomerFromId(id);
    db.closeDatabase();
    db_histTuple customer_operation;
    QString format="yyyy-MM-dd hh:mm:ss";
    QDateTime qtime=QDateTime::currentDateTime();
    QDateTime now=QDateTime::currentDateTime();
    float balance= customer_data.getCustomerBalance();
    int k;
    //recupérer les anciennes données quand getCustomer_Old_Hist sera implémenté
    std::vector<double> x(numberOfPoints), y(numberOfPoints);
    db_dataarray Values=make_pair(x,y);
    int now_int = QDateTime::currentDateTime().toTime_t();
    //On remplit le tableau, qui contient les dates et les valeurs:
    // Values.first contient les dates,
    // Values.second les valeurs.

    for (int i=0;i<numberOfPoints;i++)
    {
        Values.first[i]=0;
        Values.second[i]=balance;
    }
    if (!customer_hist.empty())
    {
        for (unsigned j=0; j<customer_hist.size();j++)
        {
            customer_operation=customer_hist.front();
            customer_hist.pop();
            std::string operation_time=customer_operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<numberOfPoints;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }

            if (k<numberOfPoints && k>=0)
            {
                balance+=customer_operation.getHistPrice();
                Values.second[k]=balance;
            }
            for (int l=0;l<numberOfPoints;l++)
            {
                if (k<l)
                {
                    Values.second[l]=balance;
                }
            }

        }
    }
    else{}
    if (!customer_hist_old.empty())
    {
        for (unsigned j=0; j<customer_hist_old.size();j++)
        {
            customer_operation=customer_hist_old.front();
            customer_hist_old.pop();
            std::string operation_time=customer_operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<numberOfPoints;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }

            if (k<numberOfPoints && k>=0)
            {
                balance+=customer_operation.getHistPrice();
                Values.second[k]=balance;
            }
            for (int l=0;l<numberOfPoints;l++)
            {
                if (k<l)
                {
                    Values.second[l]=balance;
                }
            }

        }
    }
    else{}
    return (Values);
}

db_dataarray Plotting::productConsumption(int id, int scale, int numberOfPoints)
{
    db_histQueue product_hist_old = db.getProductHist(id,true);
    db.closeDatabase();
    db.openDatabase();
    db_histQueue product_hist = db.getProductHist(id,false);
    db.closeDatabase();

    db_histTuple product_operation;
    QString format="yyyy-MM-dd hh:mm:ss";
    QDateTime qtime=QDateTime::currentDateTime();
    QDateTime now=QDateTime::currentDateTime();
    int k;
    //recupérer les anciennes données quand getCustomer_Old_Hist sera implémenté
    std::vector<double> x(100), y(100);
    db_dataarray Values=make_pair(x,y);
    int now_int = QDateTime::currentDateTime().toTime_t();
    //On remplit le tableau, qui contient les dates et les valeurs:
    // Values.first contient les dates,
    // Values.second les valeurs.

    for (int i=0;i<100;i++)
    {
        Values.first[i]=0;
        Values.second[i]=0;
    }
    if (!product_hist.empty())
    {
        for (unsigned j=0; j<product_hist.size();j++)
        {
            product_operation=product_hist.front();
            product_hist.pop();
            std::string operation_time=product_operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<100;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }
            if (k<numberOfPoints && k>0)
            {
                Values.second[k]++;
            }
        }
    }
    else{}
    if (!product_hist_old.empty())
    {
        for (unsigned j=0; j<product_hist_old.size();j++)
        {
            product_operation=product_hist_old.front();
            product_hist_old.pop();
            std::string operation_time=product_operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<100;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }
            if (k<numberOfPoints && k>0)
            {
                Values.second[k]++;
            }
        }
    }
    else{}
    return (Values);
}

db_dataarray Plotting::productStock(int id, int scale, int numberOfPoints)
{

    db.openDatabase();
    std::cout<<"Teststock";
    db_histQueue product_hist = db.getProductHist(id,false);
    db.closeDatabase();
    db.openDatabase();
    db_histQueue product_hist_old = db.getProductHist(id,true);
    db.closeDatabase();
    db.openDatabase();
    //TODO : la méthode qui renvoie les modifs de stock sous la forme d'un db_commandQueue
    db_commandQueue product_hist_stocks = db.getCommandFromProdId(id);
    db.closeDatabase();
    db.openDatabase();
    db_productTuple product_data =db.getProductFromId(id);
    db.closeDatabase();
    db_histTuple product_operation;
    db_commandTuple command_operation;
    QString format="yyyy-MM-dd hh:mm:ss";
    QDateTime qtime=QDateTime::currentDateTime();
    QDateTime now=QDateTime::currentDateTime();
    int stock= product_data.getProductStock();
    int stockedit=0;
    int k;
    //recupérer les anciennes données quand getCustomer_Old_Hist sera implémenté
    std::vector<double> x(numberOfPoints), y(numberOfPoints);
    db_dataarray Values=make_pair(x,y);
    db_dataarray ValuesStockEdit=make_pair(x,y);
    int now_int = QDateTime::currentDateTime().toTime_t();
    //On remplit le tableau, qui contient les dates et les valeurs:
    // Values.first contient les dates,
    // Values.second les valeurs.

    for (int i=0;i<numberOfPoints;i++)
    {
        Values.first[i]=0;
        Values.second[i]=stock;
    }
    // La boucle qui suit récupère les data de l'HIST récent
    if (!product_hist.empty())
    {
        for (unsigned j=0; j<product_hist.size();j++)
        {
            product_operation=product_hist.front();
            product_hist.pop();
            std::string operation_time=product_operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<numberOfPoints;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }

            if (k<numberOfPoints && k>=0)
            {
                stock++;
                Values.second[k]=stock;
            }
            for (int l=0;l<numberOfPoints;l++)
            {
                if (k<l)
                {
                    Values.second[l]=stock;
                }
            }
        }

    }
    else{}
    // La boucle qui suit récupère les data de l'HIST ancien
    if (!product_hist_old.empty())
    {
        for (unsigned j=0; j<product_hist_old.size();j++)
        {
            product_operation=product_hist_old.front();
            product_hist_old.pop();
            std::string operation_time=product_operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<numberOfPoints;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }

            if (k<numberOfPoints && k>=0)
            {
                stock++;
                Values.second[k]=stock;
            }
            for (int l=0;l<numberOfPoints;l++)
            {
                if (k<l)
                {
                    Values.second[l]=stock;
                }
            }
        }
    }
    else{}
    // La boucle qui suit récupère les modifs de stock
    if (!product_hist_stocks.empty())
    {
        for (unsigned j=0; j<product_hist_stocks.size();j++)
        {
            command_operation=product_hist_stocks.front();
            product_hist_stocks.pop();
            std::string operation_time=command_operation.getDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);
            for (int i=0;i<numberOfPoints;i++)
            {
                ValuesStockEdit.first[i]=now_int-(24*3600*scale)*i;
            }

            if (k<numberOfPoints && k>=0)
            {
                stockedit-=command_operation.getProd_qty();
                ValuesStockEdit.second[k]-=stockedit;
            }
            for (int l=0;l<numberOfPoints;l++)
            {
                if (k<l)
                {
                    ValuesStockEdit.second[l]=stockedit;
                }
            }
        }
    }
    else{}
    for (int j=0;j<numberOfPoints;j++)
    {
        Values.second[j]+=ValuesStockEdit.second[j];
    }

    return (Values);
}


db_dataarray Plotting::totalConsumption(int scale,int numberOfPoints, int type)
{
    db.openDatabase();
    db_histQueue hist = db.getFullHist();
    db.closeDatabase();
    db_histTuple operation;
    QString format="yyyy-MM-dd hh:mm:ss";

    QDateTime qtime=QDateTime::currentDateTime();
    QDateTime now=QDateTime::currentDateTime();
    int k;
    //recupérer les anciennes données quand getCustomer_Old_Hist sera implémenté
    std::vector<double> x(numberOfPoints), y(numberOfPoints);
    db_dataarray Values=make_pair(x,y);
    int now_int = QDateTime::currentDateTime().toTime_t();

    for (int i=0;i<numberOfPoints;i++)
    {
        Values.first[i]=0;
        Values.second[i]=0;
    }
    if (!hist.empty())
    {
        for (unsigned j=0; j<hist.size();j++)
        {
            operation=hist.front();
            hist.pop();
            std::string operation_time=operation.getHistDate();
            QString qoperation_time=QString::fromStdString(operation_time);

            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*scale);

            for (int i=0;i<numberOfPoints;i++)
            {
                Values.first[i]=now_int-(24*3600*scale)*i;
            }

            if (k<numberOfPoints && k>=0)
            {
                Values.second[k]++;
            }

        }
    }
    else{}
    return (Values);
}



void Plotting::setDb(sqlite3* handle)
{
    db.setHandle(handle);
}

sqlite3* Plotting::getDb()
{
    return db.getHandle();
}

//methode de test : ne dois PAS se situer dans le vue !!
void Plotting::plot(db_dataarray datas)
{
}

