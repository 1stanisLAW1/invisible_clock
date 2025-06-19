#ifndef SETTING_WINDOW_H
#define SETTING_WINDOW_H

#include "qcombobox.h"
#include <QObject>

class setting_window : public QObject
{
    Q_OBJECT
public:
    explicit setting_window(QObject *parent = nullptr);
    void show_setting();
    void setComboBox();

signals:
    void set_setting(QStringList);
    void write_settings(QStringList);
public slots:
    void default_setting_comboBox(QStringList);
private:
    QComboBox* line_color;
    QComboBox* line_size;
    QComboBox* line_family;
};

#endif // SETTING_WINDOW_H
