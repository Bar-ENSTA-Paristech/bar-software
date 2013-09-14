#ifndef HISTORY_H
#define HISTORY_H

#include <QFrame>

class History : public QFrame
{
    Q_OBJECT
public:
    explicit History(QWidget *parent = 0);
    void setHistory();
    
signals:
    
public slots:
    
};

#endif // HISTORY_H
