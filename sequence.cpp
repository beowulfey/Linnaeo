#include "sequence.h"

//#include <QDebug>

namespace Sequence
{
    QList<QStringList> parseFastaString(QString input)
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

}
