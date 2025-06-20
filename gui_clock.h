#ifndef GUI_CLOCK_H
#define GUI_CLOCK_H

#include "qlabel.h"
#include "qpushbutton.h"
#include "setting_window.h"
#include "write_config.h"
#include <QObject>

class gui_clock : public QObject
{
    Q_OBJECT
public:
    explicit gui_clock(QObject *parent = nullptr);
    void setTime();
    ~gui_clock();

public slots:
    void upd_t(QString time);
    void upd_d(QString data);
    void setSettings(QStringList list);
signals:
    void signal_setting(QStringList);
private:
    QLabel* lbl;
    QLabel* lbl_2;
    bool check_btn = true;
    QDialog* dialog;
    QThread* thread;
    QPushButton* btn;
    QStringList list_global;
    QPushButton* btn_setting;
    setting_window* sw = nullptr;
    write_config* wc = nullptr;
};

#endif // GUI_CLOCK_H
