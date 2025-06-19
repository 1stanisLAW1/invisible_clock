#include "setting_window.h"
#include "qfontdatabase.h"
#include "qgridlayout.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include "write_config.h"

#include <QComboBox>
#include <QLineEdit>

setting_window::setting_window(QObject *parent)
    : QObject{parent}
{
    write_config* wc = new write_config();

    connect(this,&setting_window::write_settings,wc,&write_config::writeconfig);
}

void setting_window::show_setting()
{
    QWidget* widget = new QWidget();
    widget->setMinimumSize(250,250);
    QPushButton* save_btn = new QPushButton("Save");
    QPushButton* back_btn = new QPushButton("back");

    QLabel* lbl_color = new QLabel("Color");
    QLabel* lbl_size = new QLabel("Size");
    QLabel* lbl_family = new QLabel("Family");

    line_color = new QComboBox();
    line_size = new QComboBox();
    line_family = new QComboBox();

    setComboBox();

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(lbl_color,0,0);
    layout->addWidget(line_color,0,1);
    layout->addWidget(lbl_size,1,0);
    layout->addWidget(line_size,1,1);
    layout->addWidget(lbl_family,2,0);
    layout->addWidget(line_family,2,1);
    layout->addWidget(save_btn,3,1);
    layout->addWidget(back_btn,3,0);

    connect(save_btn,&QPushButton::clicked,this,[=](){
        QStringList list;
        list.append(line_color->currentText());
        list.append(line_size->currentText());
        list.append(line_family->currentText());
        emit write_settings(list);
        emit set_setting(list);
        widget->close();
        delete widget;
    });
    connect(back_btn,&QPushButton::clicked,this,[=](){
        widget->close();
        delete widget;
    });

    widget->setLayout(layout);
    widget->show();
}

void setting_window::setComboBox()
{
    QFontDatabase fontDatabase;
    QStringList font_families = fontDatabase.families();
    QList<int> standard_sizes = {8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72,84,96,108,120};
    QList<QString>standart_colors = {"Red","Green","Blue","Black","White","Yellow","Cyan","Magenta","Gray"};
    line_family->addItems(font_families);
    for (int size : standard_sizes) {
        line_size->addItem(QString::number(size));
    }
    for (QString color : standart_colors) {
        line_color->addItem(color);
    }
}

void setting_window::default_setting_comboBox(QStringList list)
{
    if(list.empty()){
        return;
    }
    qDebug()<<list;
    line_color->setCurrentText(list.at(0));
    line_size->setCurrentText(list.at(1));
    line_family->setCurrentText(list.at(2));
}
