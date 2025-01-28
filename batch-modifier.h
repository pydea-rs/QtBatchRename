#ifndef BATCHMODIFIER_H
#define BATCHMODIFIER_H

#include <QString>

class BatchModifier
{
private:
    const QString directoryPath;
public:
    BatchModifier(const QString &directoryPath): directoryPath(directoryPath) {}
    QStringList fetchFilenames() const;

    QMap<QString, QString> batchExtend(const QString &text, bool prepend) const;
    QString getAppendedFilename(const QString &filename, const QString &suffix) const;

    QString getPrependedFilename(const QString &prefix, const QString &filename) const;

    QString BatchModifier::getReplacedFilename(QString filename, const QString &oldPhrase, const QString &newPhrase) const;
    QMap<QString, QString> BatchModifier::batchReplace(const QString &oldPhrase, const QString &newPhrase) const;
};

#endif // BATCHMODIFIER_H
