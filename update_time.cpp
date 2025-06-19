#include "update_time.h"

#include <QTime>

update_time::update_time(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&update_time::upd_time);
    timer->start(1000);
}

void update_time::upd_time()
{
    QString time  = QTime::currentTime().toString("HH:mm:ss");
    emit updtime(time);
    if(time=="00:00:00"){
        QString d = QDate::currentDate().toString("dd MMM");
        QString dayName = QDate::currentDate().toString("dddd");
        QString data = dayName+", "+d;
        emit updata(data);
    }
}
