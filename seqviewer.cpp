#include "seqviewer.h"
#include "themes.h"
#include <math.h>
#include <QRegularExpression>
#include <QFontDatabase>
#include <QElapsedTimer>

SeqViewer::SeqViewer(QWidget *parent): QTextEdit(parent)
{
    QFontDatabase::addApplicationFont(":/fonts/Noto-Custom.ttf");
    this->setFont(QFont("Noto Custom", 10, 1));
    setTheme(0);
}

void SeqViewer::setTheme(int index)
{
    switch(index) {
    case 0: lookup = Themes::defaultTheme();
    default: lookup = Themes::defaultTheme();
    }
    if(!displayedSeqs.isEmpty()) drawSequenceOrAlignment();
}

void SeqViewer::setColors(bool colors)
{
    colorOn = colors;
    if(!displayedSeqs.isEmpty()) drawSequenceOrAlignment();

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

void SeqViewer::setDisplaySequence(QString seq, QString name)
/// Called upon double-clicking; initializes the viewer with the sequence of choice.
/// Calls the sequence redraw function.
{
    this->displayedSeqs.clear();
    this->displayedSeqsColor.clear();
    this->displayedSeqs.append(seq);
    this->displayedNames.clear();
    this->displayedNames.append(name);
    calculateColor();
    drawSequenceOrAlignment();
}


void SeqViewer::calculateColor()
{
    //QElapsedTimer timer;

    //timer.start();
    // Define themes:

    QList<QString> colorSeq;

    for(auto&& seq: displayedSeqs)
    {
        colorSeq.clear();
        for(auto&& resi: seq)
        {
            QString colorRes = "<span style=\"background-color:";
            colorRes.append(lookup[resi]);
            colorSeq.append(colorRes);
            //qDebug() << "appended" <<colorRes;
        }
        displayedSeqsColor.append(colorSeq);


    }
    //qDebug()  << displayedSeqsColor.at(0).length() << "vs" << displayedSeqs.at(0).length();
    //qDebug() << "Creating color version took" << timer.elapsed() << "milliseconds";
}

void SeqViewer::drawSequenceOrAlignment()
/// Gets the current width of the window and calculates the sequence split.
/// If there is color, uses the color version of the sequences lists.
/// In release mode, this is FAST ENOUGH (about 8ms) but in debug it is VERY SLOW
/// Black and white mode is fast in both!
/// Keep an eye on this...
{

    float charWidth;
    int numChars;
    int numBlocks;
    QString formatted;


    if(!displayedSeqs.isEmpty())
    {
        //QElapsedTimer timer;
        //timer.start();
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
                    if(!(i==numBlocks))seg = displayedSeqs.at(j).sliced(i*numChars, numChars).append("\n");
                    else seg = displayedSeqs.at(j).last(displayedSeqs.at(j).length()-i*numChars).append("\n");
                    //qDebug()<< "Block:"<< i <<"Seq"<<j<<"extracts"<<seg;
                } else // Color uses the displayedSeqsColor List<List<String>> of the sequence expanded with color data
                {
                    if(!(i==numBlocks))seg = QList<QString>(displayedSeqsColor.at(j).sliced(i*numChars, numChars)).join("").append("\n");
                    else seg = QList<QString>(displayedSeqsColor.at(j).last(displayedSeqsColor.at(j).length()-i*numChars)).join("").append("\n");
                    //qDebug() << seg;
                }
                //
                formatted.append(seg);
            }
            formatted.append("\n");
        }
        formatted.append("</pre>");
        this->document()->clear();
        this->document()->setHtml(formatted);
        //qDebug() << "The drawing operation took" << timer.elapsed() << "milliseconds";

    }


}

