#include "logging.h"
#include "seqviewer.h"
#include "themes.h"
#include <math.h>
#include <QEvent>
#include <QRegularExpression>
#include <QFontDatabase>
#include <QElapsedTimer>
#include <QScrollBar>
#include <QPaintEvent>
#include <QPainter>


SeqViewer::SeqViewer(QWidget *parent): QTextEdit(parent)
{

    resizeTimer = new QTimer(this);
    resizeTimer->setSingleShot(true);
    connect(resizeTimer, &QTimer::timeout, this, &SeqViewer::resizeTimeout);
    this->horizontalScrollBar()->setTracking(true);
    connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(noWrapUpdateRuler(int)));
    //this->installEventFilter(this);
    //this->setMouseTracking(false);
}

void SeqViewer::resizeEvent(QResizeEvent *event)
{

    QTextEdit::resizeEvent(event);
    resizing = true;
    resizeTimer->start(100);

    wrapSeqs ? drawSequenceOrAlignment() : noWrapUpdateRuler();

}

void SeqViewer::resizeTimeout()
{
    resizing = false;
    //qDebug(lnoView) << "DONE RESIZING";
    wrapSeqs ? drawSequenceOrAlignment() : noWrapUpdateRuler();
}

void SeqViewer::paintEvent(QPaintEvent *event)
{
    QTextEdit::paintEvent(event);
    qDebug(lnoEvent)<<"Found paint event!";
    const QRect rect = event->rect();
    //const QFont font = currentCharFormat().font();
    int x30 = round(QFontMetricsF(font()).averageCharWidth() * 30.0)
            + document()->documentMargin();
    QPainter p(viewport());
    p.setPen(QPen("black"));
    p.drawLine(x30, rect.top(), x30, rect.bottom());
    qDebug(lnoEvent) << x30 << document()->documentMargin() << font();

}

bool SeqViewer::eventFilter(QObject *object, QEvent *ev)
{
    qDebug(lnoEvent) << object<<ev->type();
    return QTextEdit::eventFilter(object, ev);
}

void SeqViewer::setTheme(int index)
{
    switch(index) {
    case 0:
        lookup = Themes::defaultTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- default theme";
        break;
    case 1:
        lookup = Themes::neonTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- neon theme";
        break;
    case 2:
        lookup = Themes::gradientTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- gradient theme";
        break;
    case 3:
        lookup = Themes::newTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- new theme";
        break;
    case 4:
        lookup = Themes::clustalXTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- Clustal X theme";
        break;
    }
    if(!displayedSeqs.isEmpty()){
        qDebug(lnoView) << "Redrawing with new colors";
        calculateColor();
        drawSequenceOrAlignment();
    }
}

void SeqViewer::setInfoMode(bool infoMode)
{
    this->infoMode = infoMode;
    int height = QFontMetricsF(font()).height()*displayedSeqs.length()+2;



}



void SeqViewer::setColors(bool colors)
{
    qDebug(lnoView) << "Set show colors to" << colors;
    colorOn = colors;
    if(!displayedSeqs.isEmpty()) drawSequenceOrAlignment();

}
void SeqViewer::setWrapSeqs(bool wrap)
{
    qDebug(lnoView) << "Set wrap sequences to" << wrap;
    wrapSeqs = wrap;
    if(!displayedSeqs.isEmpty()) drawSequenceOrAlignment();

}

void SeqViewer::clearViewer()
{
    qDebug(lnoView) << "Viewer cleared of all sequences";
    displayedSeqs.clear();
    this->document()->setHtml("");
}

QStringList SeqViewer::getSeqList()
{
    return displayedSeqs;
}



void SeqViewer::setDisplaySequence(QString seq, QString name)
/// Called upon double-clicking; initializes the viewer with the sequence of choice.
/// Calls the sequence redraw function.
{
    qDebug(lnoView) << "Setting viewer to a single sequence:"<<name;
    this->displayedSeqs.clear();
    this->displayedSeqs.append(seq);
    this->displayedNames.clear();
    this->displayedNames.append(name);
    calculateColor();
    calculateRuler();
    drawSequenceOrAlignment();
}

void SeqViewer::setDisplayAlignment(QList<QString> seqs, QList<QString> names)
{
    qDebug(lnoView) << "Setting viewer to show an alignment";
    displayedSeqs.clear();
    displayedNames.clear();
    displayedSeqsColor.clear();
    displayedSeqs = seqs;
    displayedNames = names;
    calculateColor();
    calculateRuler();
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
        for(auto&& resi: seq) colorSeq.append(lookup[resi]);
        displayedSeqsColor.append(colorSeq);


    }
    qDebug(lnoView) << "Creating color version took" << timer.elapsed() << "milliseconds";
}

void SeqViewer::calculateRuler()
{
    displayedRuler.clear();
    int count;
    for(auto&& seq : displayedSeqs)
    {
        count = 0;
        QList<QString> counter; //is this big enough?
        for(auto && res : seq)
        {
            if(res != '-') count += 1;
            counter.append(QString::number(count));
        }
        displayedRuler.append(counter);
        //qDebug() << displayedRuler;
    }

}


void SeqViewer::drawSequenceOrAlignment()
/// Gets the current width of the window and calculates the sequence split.
/// If there is color, uses the color version of the sequences lists.
/// In release mode, this is FAST ENOUGH (about 8ms) but in debug it is VERY SLOW
/// Black and white mode is fast in both!
/// Keep an eye on this...
{

    float charWidth = 0;
    int numChars;
    int noWrapChars = 0;
    QString formatted;
    QString namesFormatted;
    QString rulerFormatted;


    if(!displayedSeqs.isEmpty())
    {

        qDebug(lnoView) << "Lengths:"<<displayedNames.length()<<displayedSeqs.length()<<displayedRuler.length()<<displayedSeqsColor.length();
        for(int i = 0; i<displayedNames.length();i++)
        {
            qDebug(lnoView)<< "Inner Lengths:"<<displayedNames.at(i).length()<<displayedSeqs.at(i).length()<<displayedRuler.at(i).length()<<displayedSeqsColor.at(i).length();
        }
        if(verticalScrollBar()->maximum() > verticalScrollBar()->minimum())
        {
            scrollPos = double(verticalScrollBar()->sliderPosition())/double(verticalScrollBar()->maximum()-verticalScrollBar()->minimum());
            //qDebug(lnoView)<<scrollPos;
            if(scrollPos < 0.05) scrollPos = 0;
        }
        if(horizontalScrollBar()->maximum()>horizontalScrollBar()->minimum())
        {
            hozScrollPos = double(horizontalScrollBar()->sliderPosition())/double(horizontalScrollBar()->maximum()-horizontalScrollBar()->minimum());
        }
        //QElapsedTimer timer;
        //timer.start();
        formatted = QString("<pre style=\"font-family:%1;\">").arg(font().family());
        //qInfo(lnoView) << formatted;
        namesFormatted = QString("<pre style=\"font-family:%1;text-align:right;\">").arg(font().family());
        rulerFormatted = QString("<pre style=\"font-family:%1;\">").arg(font().family());
        charWidth = QFontMetricsF(font()).averageCharWidth();
        if(wrapSeqs){
            numChars = int(truncf((QRectF(rect()).width()-2.0)/charWidth)-1.0);
            numBlocks = trunc(displayedSeqs.first().length()/numChars);
        }
        else
        {
            noWrapChars = int(truncf((QRectF(rect()).width()-2.0)/charWidth)-1.0);
            numChars = displayedSeqs.first().length(); // all sequences should have same length at this point! may need to validate.
            numBlocks = 0;
        }
        qDebug(lnoView) << "Text"<<charWidth << numChars << numBlocks;
        for(int i = 0; i<=numBlocks; i++) // for each text block...
        {
            if(rulerOn)
            {
                namesFormatted.append("\n\n");
                rulerFormatted.append("\n\n");
            }
            bool lastRuler = true;
            for(int j=0; j<displayedSeqs.length();j++) // for each sequence in the list...
            {

                qDebug(lnoView) << "Current Iteration: Text Block"<<i<<"and sequence"<<j;
                // Name stuff
                namesFormatted.append(displayedNames.at(j)).append("\n");

                // Sequence stuff
                QString seg;
                if(colorOn && !resizing)  // Color uses the displayedSeqsColor List<List<String>> of the sequence expanded with color data
                {
                    if(!(i==numBlocks)) {
                        //qDebug(lnoView) << "not last block";
                        seg = QList<QString>(displayedSeqsColor.at(j).sliced(i*numChars, numChars)).join("").append("\n");
                    }
                    else {
                        seg = displayedSeqsColor.at(j).mid(i*numChars).join("");
                        if(seg!="")
                        {
                            //qDebug(lnoView) <<"last block color!";

                            if((displayedSeqsColor.at(j).mid(i*numChars).length() + displayedRuler.at(j).last().length()) <numChars) {
                                seg.append(" ").append(displayedRuler.at(j).last());
                                lastRuler = false;
                            }
                            seg.append("\n");
                        }
                    }

                } else // Black and white only uses the displayedSeqs parameter -- less resource intensive
                {
                    //qDebug(lnoView) << " using black and white generator";
                    if(!(i==numBlocks)) {
                        //qDebug(lnoView) << "not last block bw";
                        seg = displayedSeqs.at(j).sliced(i*numChars, numChars).append("\n");
                    }
                    else {
                        //qDebug(lnoView) << "last blocK!!!";
                        seg = displayedSeqs.at(j).mid(i*numChars);
                        if(seg!="")
                        {
                            if(displayedSeqs.at(j).mid(i*numChars).length()+displayedRuler.at(j).last().length() < numChars)
                            {
                                //qDebug(lnoView) <<"determined it was too small";
                                seg.append(" ").append(displayedRuler.at(j).last());
                                lastRuler = false;
                            }
                            seg.append("\n");
                        }
                    }
                }
                formatted.append(seg);

                // Ruler stuff
                if(!(i==numBlocks)) rulerFormatted.append(displayedRuler.at(j).at(i*numChars+numChars-1)).append("\n");
                else {
                    if(lastRuler) {
                        wrapSeqs ? rulerFormatted.append(displayedRuler.at(j).last()).append("\n") :
                                   rulerFormatted.append(displayedRuler.at(j).at(noWrapChars)+"|"+displayedRuler.at(j).last()).append("\n");
                    }
                    else
                    {
                        qDebug() << "not placing last ruler because it fit on screen!";
                        rulerFormatted.append("\n");
                    }
                }
            }
            formatted.append("\n");
            namesFormatted.append(" \n");
            rulerFormatted.append(" \n");
        }
        formatted.chop(2);
        formatted.append("</pre>");
        namesFormatted.chop(2);
        namesFormatted.append("</pre>");
        rulerFormatted.chop(2);
        rulerFormatted.append("</pre>");
        this->document()->clear();
        this->document()->setHtml(formatted);
        this->formattedNames = namesFormatted;
        this->formattedRuler = rulerFormatted;
        emit updatedNamesAndRuler(formattedNames, formattedRuler); // Send it back to Linnaeo to add to names panel.
        //qDebug(lnoView) << "The drawing operation took" << timer.elapsed() << "milliseconds";
        if(verticalScrollBar()->maximum() > verticalScrollBar()->minimum()){
            verticalScrollBar()->setSliderPosition(round(scrollPos*double(verticalScrollBar()->maximum()-verticalScrollBar()->minimum())));
        }
        if(horizontalScrollBar()->maximum()>horizontalScrollBar()->minimum()){
            horizontalScrollBar()->setSliderPosition(round(hozScrollPos*double(horizontalScrollBar()->maximum()-horizontalScrollBar()->minimum())));
        }
    }
}

void SeqViewer::noWrapUpdateRuler(int val){
    double charWidth = QFontMetricsF(font()).averageCharWidth();
    int noWrapChars = int(truncf((QRectF(rect()).width()-2.0)/charWidth)-1.0);
    int numChars = displayedSeqs.first().length(); // all sequences should have same length at this point! may need to validate.
    numBlocks = 0;
    double index = 0;
    QScrollBar *bar = horizontalScrollBar();
    if(bar->maximum()>bar->minimum())
    {
        qDebug(lnoEvent) << "Sliding!" << bar->sliderPosition()<<"/"<<bar->maximum()<<"-"<<bar->minimum()<<"*"<<numChars<<"+"<<noWrapChars;
        formattedRuler = QString("<pre style=\"font-family:%1;\">").arg(font().family());
        int index=trunc(double(double(bar->sliderPosition())/(double(bar->maximum())-double(bar->minimum())))*double(numChars-noWrapChars))+noWrapChars;
        qDebug(lnoEvent) << int(index);
        for(int i =0;i<displayedRuler.length();i++)
        {
            QString display = displayedRuler.at(i).at(index);
            if(display.isEmpty()) display = displayedRuler.at(i).last();
            formattedRuler.append(display+"|"+displayedRuler.at(i).last()).append("\n");
        }
        formattedRuler.append("\n");
    }
    emit updatedNamesAndRuler(formattedNames, formattedRuler); // Send it back to Linnaeo to add to names panel.
}

void SeqViewer::fontChanged()
{
    if(!displayedSeqs.isEmpty()) drawSequenceOrAlignment();
}
