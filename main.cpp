#include "gui_clock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui_clock gc;
    return a.exec();
}
