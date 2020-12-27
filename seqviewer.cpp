#include "seqviewer.h"
#include <math.h>
#include <QRegularExpression>
#include <QFontDatabase>
#include <QFontDialog>

SeqViewer::SeqViewer(QWidget *parent): QTextEdit(parent)
{
    QFontDatabase::addApplicationFont(":/fonts/Noto-Custom.ttf");
    //seqFont = QFont("Noto Custom", 10, 1);
    this->setFont(QFont("Noto Custom", 10, 1));
}


void SeqViewer::clearViewer()
{
    displayedSeqs.clear();
    this->setText("");
}

QStringList SeqViewer::getSeqList()
{
    return displayedSeqs;
}

void SeqViewer::resizeEvent(QResizeEvent *event)
{
    QTextEdit::resizeEvent(event);
    drawSequenceOrAlignment();
}

void SeqViewer::displaySequence(QString seq, QString name)
/// Called upon double-clicking; initializes the viewer with the sequence of choice.
/// Calls the sequence redraw function.
{
    this->displayedSeqs.clear();
    this->displayedSeqs.append(seq);
    this->displayedNames.clear();
    this->displayedNames.append(name);
    drawSequenceOrAlignment();
}




void SeqViewer::drawSequenceOrAlignment()
/// Gets the current width of the window and
{
    int width;
    float charWidth;
    int numChars;
    int numBlocks;
    //QTextCursor cursor;
    QString blank;
    QString formatted;
    QStringList splitSeq;
    QList<QList<QString>> seqBlocks;
    QRegularExpression re;
    QRegularExpressionMatchIterator matches;
    QRegularExpressionMatch match;


    if(!displayedSeqs.isEmpty())
    {
        this->setText("");

        formatted = QString("<pre style=\"font-family:%1;\">").arg(font().family());
        width = this->rect().width();
        charWidth = QFontMetricsF(this->seqFont).averageCharWidth();
        qDebug() << "Av. CharW =" <<charWidth<<"and window is" <<width;

        numChars = trunc(width/charWidth)-1;
        numBlocks = this->displayedSeqs.first().length()/numChars;
        blank = QString("");
        blank.resize(numChars);
        blank.fill(' ').append("\n");
        for(auto& tempSeq : displayedSeqs)
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
            for(int j=0; j<this->displayedSeqs.length();j++)
                // for each sequence in the list...
            {
                qDebug()<< "Block:"<< i <<"Seq"<<j<<"extracts"<<seqBlocks.at(j).at(i);
                //cursor.movePosition(QTextCursor::End);

                //this->insertHtml(QString(seqBlocks.at(j).at(i)).append("\n"));
                formatted.append(QString(seqBlocks.at(j).at(i)).append("\n"));
                //this->setText(seqBlocks.at(j).at(i));
            }
            formatted.append(blank);
            //this->insertHtml(blank);
        }
        formatted.append("</pre>");
        this->textCursor().insertHtml(formatted);
        //this->insertHtml("</span></pre>");

    }


}

