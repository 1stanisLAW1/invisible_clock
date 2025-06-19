#include "mainwindow.h"
#include "qdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Обязательные настройки
    ui->centralwidget->setWindowFlag(Qt::FramelessWindowHint);  // Убираем рамку
    ui->centralwidget->setAttribute(Qt::WA_TranslucentBackground);  // Включаем прозрачность
    ui->centralwidget->setStyleSheet("background: transparent;");  // Убираем фон

    // Если виджет содержит другие элементы (кнопки, лейблы)
    ui->centralwidget->setAttribute(Qt::WA_NoSystemBackground);  // Отключаем системный фон

    ui->centralwidget->resize(400, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}
