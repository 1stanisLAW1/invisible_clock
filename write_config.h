#ifndef WRITE_CONFIG_H
#define WRITE_CONFIG_H

#include <QObject>

class write_config : public QObject
{
    Q_OBJECT
public:
    explicit write_config(QObject *parent = nullptr);
public slots:
    void writeconfig(QStringList);
    QStringList Read_Config_style();

signals:
};

#endif // WRITE_CONFIG_H
