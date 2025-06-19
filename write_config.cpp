#include "write_config.h"

#include <QCoreApplication>
#include <QFile>

write_config::write_config(QObject *parent)
    : QObject{parent}
{}

void write_config::writeconfig(QStringList list)
{
    QString executablePath = QCoreApplication::applicationDirPath();
    QString filePath = executablePath + "/configs/config_style.txt";
    QFile file(filePath);

    if(list.empty()){
        qDebug()<<"Список пуст";
        return;
    }

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream<<"[main]"<<"\n";

        stream<<"Color = "<<list.at(0)<<"\n";
        stream<<"Size = "<<list.at(1)<<"\n";
        stream<<"Family = "<<list.at(2)<<"\n";

        if(stream.status() != QTextStream::Ok) {
            qDebug() << "Ошибка записи данных: " << filePath << stream.status();
        }

        file.close();

        if(file.error() != QFile::NoError) {
            qDebug() << "Ошибка закрытия файла";
        }
    }
    else {
        qDebug() << "Не удалось открыть файл для записи";
    }

}

QStringList write_config::Read_Config_style()
{
    QString executablePath = QCoreApplication::applicationDirPath();
    QString filePath = executablePath + "/configs/config_style.txt";
    QFile file(filePath);

    if (!file.exists() || file.size() == 0) {
        qDebug() << "Файл не существует или пуст, создаем конфиг по умолчанию";
        file.close();
        return QStringList();
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QStringList result;

        while (!stream.atEnd()) {
            QString line = stream.readLine().trimmed();

            if (line.startsWith("[main]")) {
                while (!stream.atEnd()) {
                    line = stream.readLine().trimmed();
                    if (line.isEmpty()) continue;

                    if (line.startsWith("Color = ")) {
                        QString value = line.mid(8).trimmed();
                        if (!value.isEmpty()) {
                            result.append(value);
                        }
                    }
                    else if (line.startsWith("Size = ")) {
                        QString value = line.mid(7).trimmed();
                        if (!value.isEmpty()) {
                            result.append(value);
                        }
                    }
                    else if (line.startsWith("Family = ")) {
                        QString value = line.mid(9).trimmed();
                        if (!value.isEmpty()) {
                            result.append(value);
                        }
                    }
                }
            }
        }
        return result;
        file.close();
    }
    else {
        qDebug() << "Error: Не удалось открыть файл для чтения";
        return QStringList();
    }
}
