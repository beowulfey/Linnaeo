#include "seqthread.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

SeqThread::SeqThread(SeqViewer *parent, QString *input, bool showColor)
    : QThread(parent)
{
    QStringList seqs;
    QString blank;
    QString formatted;
    QStringList splitSeq;
    QList<QList<QString>> seqBlocks;
    QRegularExpression re;
    QRegularExpressionMatchIterator matches;
    QRegularExpressionMatch match;

    formatted = QString("<pre style=\"font-family:%1;\">").arg(parent->font().family());
    width = parent->rect().width();
    charWidth = QFontMetricsF(parent->font()).averageCharWidth();
    qDebug() << "Av. CharW =" <<charWidth<<"and window is" <<width;
    numChars = trunc(width/charWidth)-1;
    seqs = parent->getSeqList();
    numBlocks = seqs.first().length()/numChars;

    blank = QString("");
    blank.resize(numChars);
    blank.fill(' ').append("\n");
    for(auto& tempSeq : seqs)
    {
        re.setPattern(QString("(.{%1})").arg(numChars));
        matches = re.globalMatch(tempSeq);
        int lastEnd = 0;
        while(matches.hasNext())
        {
            match = matches.next();
            splitSeq.append(match.capturedTexts().at(0));
            lastEnd = match.capturedEnd();
        }
        if (lastEnd > 0) splitSeq.append(tempSeq.mid(lastEnd));

        seqBlocks.append(splitSeq);
    }

    for(int i = 0; i<=numBlocks; i++)
        // for each text block...
    {
        for(int j=0; j<seqs.length();j++)
            // for each sequence in the list...
        {
            qDebug()<< "Block:"<< i <<"Seq"<<j<<"extracts"<<seqBlocks.at(j).at(i);
            formatted.append(QString(seqBlocks.at(j).at(i)).append("\n"));
        }
        formatted.append(blank);
    }
    formatted.append("</pre>");
}
