#include "sequence.h"

#include <QDebug>

namespace Sequence
{
    QHash<QString, QString> parseFastaString(QString input)
    {
        qDebug()<<input.trimmed();
        QHash <QString, QString> result;
        QString curName;
        QString curSeq;
        QListIterator<QString> seg(input.trimmed().split("\n"));
        while(seg.hasNext())
        {

            if(seg.peekNext()[0] == '>' && seg.hasPrevious())
            {
                qDebug() << "Looking at"<<seg.peekNext() << "Found new seq! Saved previous.";
                result[curSeq]=curName;
                curSeq.clear();
                curName = QString(seg.next()).remove(0,1);
            }
            else if (seg.peekNext()[0] == '>' && !seg.hasPrevious())
            {
                qDebug() << "Looking at"<<seg.peekNext() << "Found first name!";
                curName = seg.next();
            }
            else
            {
                qDebug() << "Looking at"<<seg.peekNext() << "appending to seq!";
                curSeq.append(seg.next());
            }
        }
        qDebug() << "Saved final seq!";
        result[curSeq]=curName;
        qDebug() << result;

        return result;




    }

}
