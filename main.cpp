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

QString appendFilename(const QString& filename, const QString& suffix) {
    unsigned short oldNameLength = filename.length();
    for(unsigned short int i = oldNameLength - 1; i > 0; i++) {
        if(filename[i] == '.') {
            return filename.left(i) + suffix + filename.right(oldNameLength - i);
        }
    }
    return filename + suffix;
}
