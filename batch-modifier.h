#ifndef BATCHMODIFIER_H
#define BATCHMODIFIER_H

#include <QString>

class BatchModifier
{
private:
    const QString directoryPath;
public:
    BatchModifier(const QString &directoryPath): directoryPath(directoryPath) {};
    QStringList fetchFilenames() const;

    QMap<QString, QString> batchAppend(const QString &suffix) const;
    QString getAppendedFilename(const QString &filename, const QString &suffix) const;

};

#endif // BATCHMODIFIER_H
