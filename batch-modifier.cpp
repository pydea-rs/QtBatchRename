#include "batch-modifier.h"
#include <QDir>
#include <QFile>
#include <QMap>
#include <QDebug>

QStringList BatchModifier::fetchFilenames() const {
    QDir dir(this->directoryPath);
    if(!dir.exists())
        throw new std::invalid_argument("No such directory!");
    return dir.entryList(QDir::Files);
}

QMap<QString, QString> BatchModifier::batchExtend(const QString &text, bool prepend) const {
    const QStringList filenames = this->fetchFilenames();
    QMap<QString, QString> changes;

    for (const auto& filename: filenames) {
        QFile file(this->directoryPath + "/" + filename);
        if(!file.exists())
            continue;
        const QString newFilename = prepend ? this->getPrependedFilename(text, file.fileName())
                                            : this->getAppendedFilename(file.fileName(), text);
        file.rename(newFilename);
        changes.insert(filename, newFilename);
    }
    return changes;
}

QMap<QString, QString> BatchModifier::batchReplace(const QString &oldPhrase, const QString &newPhrase) const {
    const QStringList filenames = this->fetchFilenames();
    QMap<QString, QString> changes;

    for (const auto& filename: filenames) {
        QFile file(this->directoryPath + "/" + filename);
        if(!file.exists())
            continue;
        const QString newFilename = this->getReplacedFilename(file.fileName(), oldPhrase, newPhrase);
        file.rename(newFilename);
        changes.insert(filename, newFilename);
    }
    return changes;
}

QString BatchModifier::getAppendedFilename(const QString &filename, const QString &suffix) const {
    unsigned short oldNameLength = filename.length();
    for(unsigned short int i = oldNameLength - 1; i >= 0; i--) {
        if(filename[i] == '.') {
            return filename.left(i) + suffix + filename.right(oldNameLength - i);
        }
    }
    return filename + suffix;
}

QString BatchModifier::getPrependedFilename(const QString &prefix, const QString &filename) const {
    unsigned short oldNameLength = filename.length();
    for(unsigned short int i = oldNameLength - 1; i >= 0; i--) {
        if(filename[i] == '/') {
            return filename.left(i + 1) + prefix + filename.right(oldNameLength - i - 1);
        }
    }
    return prefix + filename;
}

QString BatchModifier::getReplacedFilename(QString filename, const QString &oldPhrase, const QString &newPhrase) const {
    unsigned short oldNameLength = filename.length();
    for(unsigned short int i = oldNameLength - 1; i >= 0; i--) {
        if(filename[i] == '/') {
            return filename.left(i) + filename.right(oldNameLength - i).replace(oldPhrase, newPhrase, Qt::CaseInsensitive);
        }
    }
    return filename.replace(oldPhrase, newPhrase, Qt::CaseInsensitive);
}
