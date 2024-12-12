#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

QStringList readFilenames(QString path) {
    QDir dir(path);
    return dir.entryList(QDir::Files);
}
