#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QString>
#include <QHash>

namespace Sequence
/// Sequence Namespace
/// Sequences are stored in Linnaeo (as data in my Item Models) as QStrings for simplicity.
/// These utilities are provided for validation purposes.
{
    QList<QStringList> splitFastaAlignmentString(QString input);
    QString prettyPrintFastaSequence(QString name, QString seq, int lineLength=60);
}

#endif // SEQUENCE_H
