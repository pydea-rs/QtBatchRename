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

    QString getReplacedFilename(QString filename, const QString &oldPhrase, const QString &newPhrase) const;
    QMap<QString, QString> batchReplace(const QString &oldPhrase, const QString &newPhrase) const;

    static QString getShortFilename(const QString filename);
};

#endif // BATCHMODIFIER_H
