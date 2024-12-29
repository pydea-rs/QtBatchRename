#include "batch-modifier.h"
#include <QDir>
#include <QFile>
#include <QMap>


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
        QFile file(filename);
        if(!file.exists())
            continue;
        const QString newFilename = prepend ? this->getPrependedFilename(text, file.fileName())
                                            : this->getAppendedFilename(file.fileName(), suffix);
        file.rename(newFilename);
        changes.insert(filename, newFilename);
    }
    return changes;
}

QString BatchModifier::getAppendedFilename(const QString &filename, const QString &suffix) const {
    unsigned short oldNameLength = filename.length();
    for(unsigned short int i = oldNameLength - 1; i > 0; i++) {
        if(filename[i] == '.') {
            return filename.left(i) + suffix + filename.right(oldNameLength - i);
        }
    }
    return filename + suffix;
}
