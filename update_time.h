#ifndef UPDATE_TIME_H
#define UPDATE_TIME_H

#include "qtimer.h"
#include <QObject>

class update_time : public QObject
{
    Q_OBJECT
public:
    explicit update_time(QObject *parent = nullptr);
    void upd_time();
    ~update_time(){
        delete timer;
    }

signals:
    void updtime(QString);
    void updata(QString);
private:
    QTimer* timer;
};

#endif // UPDATE_TIME_H
