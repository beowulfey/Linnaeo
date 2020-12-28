#include "seqviewer.h"
#include <math.h>
#include <QRegularExpression>
#include <QFontDatabase>
#include <QElapsedTimer>

SeqViewer::SeqViewer(QWidget *parent): QTextEdit(parent)
{
    QFontDatabase::addApplicationFont(":/fonts/Noto-Custom.ttf");
    this->setFont(QFont("Noto Custom", 10, 1));
    colorOn = false;
}


void SeqViewer::clearViewer()
{
    displayedSeqs.clear();
    this->document()->setHtml("");
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
    calculateColor();
    drawSequenceOrAlignment();
}


void SeqViewer::calculateColor()
{
    for(auto&& seq: displayedSeqs)
    {

    }
}

void SeqViewer::drawSequenceOrAlignment()
/// Gets the current width of the window and
{

    float charWidth;
    int numChars;
    int numBlocks;
    QString formatted;


    if(!displayedSeqs.isEmpty())
    {
        QElapsedTimer timer;
        timer.start();
        formatted = QString("<pre style=\"font-family:%1;\">").arg(font().family());
        charWidth = QFontMetricsF(font()).averageCharWidth();
        numChars = trunc((QRectF(rect()).width()-3)/charWidth)-1;
        numBlocks = displayedSeqs.first().length()/numChars;

        for(int i = 0; i<=numBlocks; i++) // for each text block...
        {
            for(int j=0; j<displayedSeqs.length();j++) // for each sequence in the list...
            {
                QString seg;
                if(!colorOn) // Black and white only uses the displayedSeqs parameter
                {
                    if(!(i==numBlocks))seg = QString(displayedSeqs.at(j).sliced(i*numChars, numChars)).append("\n");
                    else seg = QString(displayedSeqs.at(j).last(displayedSeqs.at(j).length()-i*numChars)).append("\n");
                } else // Color uses the displayedSeqsColor List<List<String>> of the sequence expanded with color data
                {}
                //qDebug()<< "Block:"<< i <<"Seq"<<j<<"extracts"<<seg;
                formatted.append(seg);
            }
            formatted.append("\n");
        }
        formatted.append("</pre>");
        this->document()->clear();
        this->document()->setHtml(QString(formatted));
        qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";

    }


}

