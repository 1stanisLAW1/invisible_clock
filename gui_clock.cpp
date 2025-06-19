#include "gui_clock.h"

#include "QVBoxLayout"
#include "qapplication.h"
#include "qdialog.h"
#include "setting_window.h"
#include "update_time.h"
#include "write_config.h"

#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QPushButton>
#include <QThread>
#include <QFontDatabase>

gui_clock::gui_clock(QObject *parent)
    : QObject{parent}
{
    lbl = new QLabel();
    lbl_2 = new QLabel();
    thread = new QThread();
    btn_setting = new QPushButton();
    btn = new QPushButton("-");

    sw = new setting_window();
    wc = new write_config();

   update_time* upd = new update_time();
   upd->moveToThread(thread);
   thread->start();

   connect(upd,&update_time::updtime,this,&gui_clock::upd_t);
   connect(upd,&update_time::updata,this,&gui_clock::upd_d);
    connect(sw,&setting_window::set_setting,this,&gui_clock::setSettings);

   connect(this,&gui_clock::signal_setting,sw,&setting_window::default_setting_comboBox);

    dialog = new QDialog();
    dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    dialog->setAttribute(Qt::WA_TranslucentBackground);
    dialog->setStyleSheet("QDialog { background: transparent; }");

    setSettings(wc->Read_Config_style());

    QRegularExpression colorRegex("color:\\s*(\\w+);");
    QRegularExpression fontSizeRegex("font-size:\\s*(\\d+)px;");
    QRegularExpression fontFamilyRegex("font-family:\\s*'([^']+)'");

    QRegularExpressionMatch colorMatch = colorRegex.match(lbl->styleSheet());
    QRegularExpressionMatch fontSizeMatch = fontSizeRegex.match(lbl->styleSheet());
    QRegularExpressionMatch fontFamilyMatch = fontFamilyRegex.match(lbl->styleSheet());


    list_global+=colorMatch.captured(1);
    list_global+=fontSizeMatch.captured(1);
    list_global+=fontFamilyMatch.captured(1);

    QString executablePath = QCoreApplication::applicationDirPath();
    QString filePath = executablePath + "/image/setting.png";
    if(check_btn==false){
        btn_setting->setIcon(QIcon(filePath));
        btn_setting->setIconSize(QSize(40, 40));
    }

    connect(btn_setting,&QPushButton::clicked,this,[=](){
        sw->show_setting();
        emit signal_setting(list_global);
    });

    connect(btn, &QPushButton::clicked, this, [=](){
        check_btn = !check_btn;
        if(check_btn) {
            dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
            btn_setting->setIcon(QIcon());
        } else {
            dialog->setWindowFlags(Qt::Dialog);
            btn_setting->setIcon(QIcon(filePath));
            btn_setting->setIconSize(QSize(40, 40));
        }
        dialog->show();
    });

    setTime();

    QHBoxLayout*hLayout = new QHBoxLayout();
    hLayout->addWidget(btn, 0, Qt::AlignRight);
    hLayout->addWidget(btn_setting, 1, Qt::AlignRight);


    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(lbl_2);
    layout->addWidget(lbl);
    layout->addLayout(hLayout);

    dialog->resize(400, 200);
    dialog->setAttribute(Qt::WA_NoSystemBackground);
    dialog->show();
}

void gui_clock::setTime()
{
    QString d = QDate::currentDate().toString("dd MMM");
    QString t  = QTime::currentTime().toString("HH:mm:ss");

    QString dayName = QDate::currentDate().toString("dddd");


    lbl->setText(t);
    lbl_2->setText(dayName+", "+d);
}

gui_clock::~gui_clock()
{
    thread->quit();
    thread->wait();

    delete lbl;
    delete lbl_2;
    delete dialog;
    delete thread;
    delete btn;
    delete btn_setting;
    delete sw;
    delete wc;

}

void gui_clock::upd_t(QString time)
{
   lbl->setText(time);
}

void gui_clock::upd_d(QString data)
{
    lbl_2->setText(data);
}

void gui_clock::setSettings(QStringList list)
{
    QString style_lbl = QString("QLabel {"
                                "color: %1; font-size: %2px; font-family: '%3'; font-weight: 600;"
                                "background: transparent;}")
                            .arg(list.at(0))
                            .arg(list.at(1))
                            .arg(list.at(2));
    QString style_btn = QString("QPushButton { color: %1; font-size: %2px; background: transparent; }").arg(list.at(0)).arg(list.at(1));
    lbl->setAlignment(Qt::AlignCenter);
    lbl_2->setAlignment(Qt::AlignCenter);
    lbl->setStyleSheet(style_lbl);
    lbl_2->setStyleSheet(style_lbl);
    btn->setStyleSheet(style_btn);
    btn_setting->setStyleSheet("QPushButton { color: white; font-size: 48px; background: transparent; }");
    btn_setting->setMaximumSize(40, 40);
    list_global = list;
}
