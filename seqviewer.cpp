#include "seqviewer.h"
#include "themes.h"
#include <math.h>
#include <QRegularExpression>
#include <QFontDatabase>
#include <QElapsedTimer>


SeqViewer::SeqViewer(QWidget *parent): QTextEdit(parent)
{

    resizeTimer = new QTimer(this);
    resizeTimer->setSingleShot(true);
    connect(resizeTimer, &QTimer::timeout, this, &SeqViewer::resizeTimeout);
}

void SeqViewer::setTheme(int index)
{
    qDebug() << "Chosen index:"<< index;
    switch(index) {
    case 0:
        lookup = Themes::defaultTheme();
        qDebug() << "Chose default theme";
        break;
    case 1:
        lookup = Themes::neonTheme();
        qDebug() << "Chose neon theme";
        break;
    case 2:
        lookup = Themes::gradientTheme();
        qDebug() << "Chose neon theme";
        break;
    case 3:
        lookup = Themes::newTheme();
        qDebug() << "Chose neon theme";
        break;
    case 4:
        lookup = Themes::clustalXTheme();
        qDebug() << "Chose neon theme";
        break;
    }
    if(!displayedSeqs.isEmpty()){
        qDebug() << "Redrawing with new colors";
        calculateColor();
        drawSequenceOrAlignment();
    }
}

void SeqViewer::setColors(bool colors)
{
    colorOn = colors;
    if(!displayedSeqs.isEmpty()) drawSequenceOrAlignment();

}
void SeqViewer::setWrapSeqs(bool wrap)
{
    wrapSeqs = wrap;
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
    qDebug() <<" Begin resize";
    resizing = true;
    resizeTimer->start(100);

    drawSequenceOrAlignment();
}

void SeqViewer::resizeTimeout()
{
    resizing = false;
    qDebug() << "DONE RESIZING";
    drawSequenceOrAlignment();
}

void SeqViewer::setDisplaySequence(QString seq, QString name)
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

void SeqViewer::setDisplayAlignment(QList<QString> seqs, QList<QString> names)
{
    displayedSeqs.clear();
    displayedNames.clear();
    displayedSeqsColor.clear();
    displayedSeqs = seqs;
    displayedNames = names;
    calculateColor();
    drawSequenceOrAlignment();
}

void SeqViewer::calculateColor()
{
    displayedSeqsColor.clear();
    QElapsedTimer timer;

    timer.start();
    // Define themes:

    QList<QString> colorSeq;

    for(auto&& seq: displayedSeqs)
    {
        colorSeq.clear();
        for(auto&& resi: seq)
        {
            //QString colorRes = "<span style=\"background-color:";
            //colorRes.append(lookup[resi]);
            colorSeq.append(lookup[resi]);
            //qDebug() << "appended" <<colorRes;
        }
        displayedSeqsColor.append(colorSeq);


    }
    //qDebug()  << displayedSeqsColor.at(0).length() << "vs" << displayedSeqs.at(0).length();
    qDebug() << "Creating color version took" << timer.elapsed() << "milliseconds";
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
    QString formatted;
    QString namesFormatted;


    if(!displayedSeqs.isEmpty())
    {
        qDebug()<<"DRAWING";
        QElapsedTimer timer;
        timer.start();
        formatted = QString("<pre style=\"font-family:%1;\">").arg(font().family());
        namesFormatted = QString("<pre style=\"font-family:%1;text-align:right;\">").arg(font().family());
        if(wrapSeqs){
            qDebug() << "Setting wrap settings";
            charWidth = QFontMetricsF(font()).averageCharWidth();
            numChars = trunc((QRectF(rect()).width()-3)/charWidth)-1;
            numBlocks = displayedSeqs.first().length()/numChars;
        }
        else
        {
            qDebug() << "No wrap today.";
            numChars = displayedSeqs.first().length(); // all sequences should have same length at this point! may need to validate.
            numBlocks = 0;
        }

        for(int i = 0; i<=numBlocks; i++) // for each text block...
        {
            for(int j=0; j<displayedSeqs.length();j++) // for each sequence in the list...
            {
                // Name stuff
                namesFormatted.append(displayedNames.at(j)).append("\n");

                // Sequence stuff
                QString seg;
                if(colorOn && !resizing)  // Color uses the displayedSeqsColor List<List<String>> of the sequence expanded with color data
                {
                    if(!(i==numBlocks)) seg = QList<QString>(displayedSeqsColor.at(j).sliced(i*numChars, numChars)).join("").append("\n");
                    else seg = QList<QString>(displayedSeqsColor.at(j).last(displayedSeqsColor.at(j).length()-i*numChars)).join("").append("\n");
                } else // Black and white only uses the displayedSeqs parameter
                {
                    if(!(i==numBlocks)) seg = displayedSeqs.at(j).sliced(i*numChars, numChars).append("\n");
                    else seg = displayedSeqs.at(j).last(displayedSeqs.at(j).length()-i*numChars).append("\n");

                }
                formatted.append(seg);
            }
            formatted.append("\n");
            namesFormatted.append("\n");
        }
        formatted.remove(formatted.length()-2,2);
        formatted.append("</pre>");
        namesFormatted.remove(namesFormatted.length()-2,2);
        namesFormatted.append("</pre>");
        qDebug() << formatted << namesFormatted;
        this->document()->clear();
        this->document()->setHtml(formatted);
        emit updatedNamesAndRuler(namesFormatted); // Send it back to Linnaeo to add to names panel.
        qDebug() << "The drawing operation took" << timer.elapsed() << "milliseconds";


    }


}

