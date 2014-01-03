#include "plotting.h"
#include <QDateTime>
#include <tuple>
#include "structures.h"

Plotting::Plotting()
{
}

/* Dans toutes les méthodes de recherche, l'arg "scale" correspond à l'échelle du graphe:
 *scale=0 ->Quotidien
 *scale=1 ->Hebdomadaire
 *scale=2 ->Mensuel
 */

db_dataarray Plotting::customerConsumption(int id,int scale,int type)
{
    db_histQueue customer_hist = db.getCustomerHist(id);
    db_histTuple customer_operation;
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

    for (unsigned j=0; j<customer_hist.size();j++)
    {
        customer_operation=customer_hist.front();
        customer_hist.pop();
        std::string operation_time=customer_operation.getHistDate();
        QString qoperation_time=QString::fromStdString(operation_time);

        if (scale==0)
        {
            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24);
            for (int i=0;i<100;i++)
            {
                Values.first[i]=now_int-(24*3600)*i;
            }
            if (k<100 && k>=0)
            {
                Values.second[k]++;
            }
        }
        else
        {
            if (scale==1)
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(3600*24*7);
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(3600*24*7)*i;
                }
            }
            else
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(2628000);
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(2628000)*i;
                }
            }

        }

        if (k<100 && k>0)
        {
            Values.second[k]++;
        }
    }
    return (Values);
}

db_dataarray Plotting::customerBalance(int id, int scale)
{
    db_histQueue customer_hist = db.getCustomerHist(id);
    db_customerTuple customer_data =db.getCustomerFromId(id);
    db_histTuple customer_operation;
    QString format="yyyy-MM-dd hh:mm:ss";
    QDateTime qtime=QDateTime::currentDateTime();
    QDateTime now=QDateTime::currentDateTime();
    float balance= customer_data.getCustomerBalance();
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
        Values.second[i]=balance;
    }

    for (unsigned j=0; j<customer_hist.size();j++)
    {
        customer_operation=customer_hist.front();
        customer_hist.pop();
        std::string operation_time=customer_operation.getHistDate();
        QString qoperation_time=QString::fromStdString(operation_time);

        if (scale==0)
        {
            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24);
            for (int i=0;i<100;i++)
            {
                Values.first[i]=now_int-(24*3600)*i;
            }
        }
        else
        {
            if (scale==1)
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(3600*24*7);
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(3600*24*7)*i;
                }
            }
            else
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(2628000);
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(2628000)*i;
                }
            }

        }
        if (k<100 && k>=0)
        {
            balance+=customer_operation.getHistPrice();
            Values.second[k]=balance;
        }
for (int l=0;l<100;l++)
{
    if (k<l)
    {
        Values.second[l]=balance;
    }
}

    }
    return (Values);
}

db_dataarray Plotting::productConsumption(int id, int scale)
{
db_histQueue product_hist = db.getProductHist(id);
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

for (unsigned j=0; j<product_hist.size();j++)
{
    product_operation=product_hist.front();
    product_hist.pop();
    std::string operation_time=product_operation.getHistDate();
    QString qoperation_time=QString::fromStdString(operation_time);

    if (scale==0)
    {
        qtime=QDateTime::fromString(qoperation_time,format);
        k=-now.secsTo(qtime)/(3600*24);
        for (int i=0;i<100;i++)
        {
            Values.first[i]=now_int-(24*3600)*i;
        }
    }
    else
    {
        if (scale==1)
        {
            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24*7);
            for (int i=0;i<100;i++)
            {
                Values.first[i]=now_int-(3600*24*7)*i;
            }
        }
        else
        {
            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(2628000);
            for (int i=0;i<100;i++)
            {
                Values.first[i]=now_int-(2628000)*i;
            }
        }

    }

    if (k<100 && k>0)
    {
        Values.second[k]++;
    }
}
return (Values);
}

db_dataarray Plotting::productStock(int id, int scale)
{
    db_histQueue product_hist = db.getProductHist(id);
    db_productTuple product_data =db.getProductFromId(id);
    db_histTuple product_operation;
    QString format="yyyy-MM-dd hh:mm:ss";
    QDateTime qtime=QDateTime::currentDateTime();
    QDateTime now=QDateTime::currentDateTime();
    int stock= product_data.getProductStock();
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
        Values.second[i]=stock;
    }

    for (unsigned j=0; j<product_hist.size();j++)
    {
        product_operation=product_hist.front();
        product_hist.pop();
        std::string operation_time=product_operation.getHistDate();
        QString qoperation_time=QString::fromStdString(operation_time);

        if (scale==0)
        {
            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24);
            for (int i=0;i<100;i++)
            {
                Values.first[i]=now_int-(24*3600)*i;
            }
        }
        else
        {
            if (scale==1)
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(3600*24*7);
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(3600*24*7)*i;
                }
            }
            else
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(2628000);
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(2628000)*i;
                }
            }

        }
        if (k<100 && k>=0)
        {
            stock++;
            Values.second[k]=stock;
        }
for (int l=0;l<100;l++)
{
    if (k<l)
    {
        Values.second[l]=stock;
    }
}

    }
    return (Values);
}


db_dataarray Plotting::totalConsumption(int scale,int type)
{
    db_histQueue hist = db.getFullHist();
    db_histTuple operation;
    QString format="yyyy-MM-dd hh:mm:ss";

    QDateTime qtime=QDateTime::currentDateTime();
    QDateTime now=QDateTime::currentDateTime();
    int k;
    //recupérer les anciennes données quand getCustomer_Old_Hist sera implémenté
    std::vector<double> x(100), y(100);
    db_dataarray Values=make_pair(x,y);
    int now_int = QDateTime::currentDateTime().toTime_t();

    for (int i=0;i<100;i++)
    {
        Values.first[i]=0;
        Values.second[i]=0;
    }

    for (unsigned j=0; j<hist.size();j++)
    {
        operation=hist.front();
        hist.pop();
        std::string operation_time=operation.getHistDate();
        QString qoperation_time=QString::fromStdString(operation_time);

        if (scale==0)
        {
            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24);

            for (int i=0;i<100;i++)
            {
                Values.first[i]=now_int-(24*3600)*i;
            }
        }
        else
        {
            if (scale==1)
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(3600*24*7);
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(3600*24*7)*i;
                }
            }
            else
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(2628000);
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(2628000)*i;
                }
            }
        }
        if (k<100 && k>=0)
        {
            Values.second[k]++;
        }

    }
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

