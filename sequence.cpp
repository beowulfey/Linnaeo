#include "sequence.h"

//#include <QDebug>
#include <QRegularExpression>

namespace Sequence
{
    QList<QStringList> splitFastaAlignmentString(QString input)
    /// Reads in an alignment string and returns a 2mer list of lists
    /// First list is a list of names of each sequence
    /// Second list is a list of the sequences themselves.
    {
        //qDebug()<<input.trimmed();
        QList<QStringList> result;
        QStringList names;
        QStringList seqs;
        QString curName;
        QString curSeq;
        QListIterator<QString> seg(input.trimmed().split("\n"));
        while(seg.hasNext())
        {

            if(seg.peekNext()[0] == '>' && seg.hasPrevious())
            {
                //qDebug() << "Looking at"<<seg.peekNext() << "Found new seq! Saved previous.";
                names.append(curName);
                seqs.append(curSeq);
                //[curSeq]=curName;
                curSeq.clear();
                curName = QString(seg.next()).remove(0,1);
            }
            else if (seg.peekNext()[0] == '>' && !seg.hasPrevious())
            {
                //qDebug() << "Looking at"<<seg.peekNext() << "Found first name!";
                curName = QString(seg.next()).remove(0,1);
            }
            else
            {
                //qDebug() << "Looking at"<<seg.peekNext() << "appending to seq!";
                curSeq.append(seg.next());
            }
        }
       // qDebug() << "Saved final seq!";
        names.append(curName);
        seqs.append(curSeq);
        //result[curSeq]=curName;
        //qDebug() << result;
        result.append(names);
        result.append(seqs);

        return result;




    }

    QString prettyPrintFastaSequence(QString name, QString seq, int lineLength)
    /// Returns a formatted Fasta sequence as a string. By default it splits the sequence into
    /// lines of length "lineLength".
    {
        QString result;
        QString seg;
        result.append(">").append(name).append("\n");
        while(seq.length()>lineLength)
        {
            seg = seq.first(lineLength); // This might be a little unsafe.
            seq.remove(seg);
            result.append(seg).append("\n");
        }
        result.append(seq).append("\n");
        return result;

    }

}
