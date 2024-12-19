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
    if(!dir.exists())
        throw new std::invalid_argument("No such directory!");
    return dir.entryList(QDir::Files);
}

QString appendFilename(const QString& filename, const QString& newName) {
    unsigned short int dotIndex = 0;
    unsigned short oldNameLength = filename.length();
    for(unsigned short int i = filename.length() - 1; i > 0; i++) {
        if(!dotIndex && filename[i] == '.')
            dotIndex = i;
        if(filename[i] == '/' || filename == '\\') {

        }
    }

}
void renameByAppend(QStringList filenames) {
    for (const auto& filename: filenames) {
        QFile file(filename);
        file.file
    }
}
