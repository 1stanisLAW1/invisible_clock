#ifndef SETTING_WINDOW_H
#define SETTING_WINDOW_H

#include "qcombobox.h"
#include "write_config.h"
#include <QObject>

class setting_window : public QObject
{
    Q_OBJECT
public:
    explicit setting_window(QObject *parent = nullptr);
    void show_setting();
    void setComboBox();
    ~setting_window(){
        delete line_color;
        delete line_size;
        delete line_family;
        deleteLater();
        delete this;
    }

signals:
    void set_setting(QStringList);
    void write_settings(QStringList);
public slots:
    void default_setting_comboBox(QStringList);
private:
    QComboBox* line_color;
    QComboBox* line_size;
    QComboBox* line_family;
    QWidget* widget = nullptr;
    write_config* wc = nullptr;
};

#endif // SETTING_WINDOW_H
