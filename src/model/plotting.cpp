#include "plotting.h"
#include <QDateTime>
#include <tuple>

Plotting::Plotting()
{
}


db_dataarray Plotting::customerConsumption(int id,int scale,int type)
{
    type_histdbQueue customer_hist = db.getCustomerHist(id);

    type_histdbTuple customer_operation;

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
        std::string operation_time=std::get<3>(customer_operation);
        QString qoperation_time=QString::fromStdString(operation_time);

        if (scale==0)
        {
            qtime=QDateTime::fromString(qoperation_time,format);
            k=-now.secsTo(qtime)/(3600*24);

            if (k<100 && k>=0)
            {
                Values.second[k]++;
            }

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

                if (k<100 && k>0)
                {
                    Values.second[k]++;
                }
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(2628000)*i;
                }
            }
            else
            {
                qtime=QDateTime::fromString(qoperation_time,format);
                k=-now.secsTo(qtime)/(3600*24*7);

                if (k<100 && k>0)
                {
                    Values.second[k]++;
                }
                for (int i=0;i<100;i++)
                {
                    Values.first[i]=now_int-(2628000)*i;
                }
            }
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

