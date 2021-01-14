#include "logging.h"
#include "seqviewer.h"
#include "themes.h"
#include "sequence.h"
#include <math.h>
#include <QEvent>
#include <QRegularExpression>
#include <QFontDatabase>
#include <QElapsedTimer>
#include <QScrollBar>
#include <QPaintEvent>
#include <QPainter>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QAbstractTextDocumentLayout>

// TODO: COnvert all double to qreal!

SeqViewer::SeqViewer(QWidget *parent): QTextEdit(parent)
{


    resizeTimer = new QTimer(this);
    resizeTimer->setSingleShot(true);
    connect(resizeTimer, &QTimer::timeout, this, &SeqViewer::resizeTimeout);
    //this->horizontalScrollBar()->setTracking(true);


    connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(noWrapUpdateRuler()));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(callUpdateHilighting()));
    connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(callUpdateHilighting())); // turn this off to move with scroll (useful!)
    //this->installEventFilter(this);
    //this->setMouseTracking(false);

}

void SeqViewer::setTheme(int index)
/// Use this to add or update themes.
{
    switch(index) {
    case 0:
        lookup = Themes::defaultTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- default theme";
        break;
    case 1:
        lookup = Themes::clustalXTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- clustalX theme";
        break;
    case 2:
        lookup = Themes::debugTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- gradient theme";
        break;
    case 3:
        lookup = Themes::colorsafeTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- new theme";
        break;
        /*
    case 4:
        lookup = Themes::clustalXTheme();
        qDebug(lnoView) << "Chose"<<index<<"-- Clustal X theme";
        break;
        */
    }
    if(!displayedSeqs.isEmpty()){
        qDebug(lnoView) << "Redrawing with new colors";
        calculateColor();
        drawSequenceOrAlignment();
    }
}

void SeqViewer::setDisplaySequence(QString seq, QString name)
/// Called upon double-clicking in the treeView; initializes the viewer with the sequence of choice.
/// First clears out the stored sequence and name, then calculates the color based on theme and ruler based on window.
{
    qDebug(lnoView) << "Setting viewer to a single sequence:"<<name;
    this->displayedSeqs.clear();
    this->displayedSeqs.append(seq);
    this->displayedNames.clear();
    this->displayedNames.append(name);
    this->currentCur.clear();
    //setSequenceMetrics();
    calculateColor();
    calculateRuler();
    drawSequenceOrAlignment();
    if(infoMode) callUpdateHilighting();
}

void SeqViewer::setDisplayAlignment(QList<QString> seqs, QList<QString> names)
/// Same as sequence version.
{
    qDebug(lnoView) << "Setting viewer to show an alignment";
    displayedSeqs.clear();
    displayedNames.clear();
    displayedSeqsColor.clear();
    displayedSeqs = seqs;
    displayedNames = names;
    this->currentCur.clear();
    //setSequenceMetrics();
    calculateColor();
    calculateRuler();
    drawSequenceOrAlignment();
    if(infoMode) callUpdateHilighting();
}

void SeqViewer::calculateColor()
/// Uses the lookup from the theme (themes.cpp) to build an extra layer into the list.
/// Essentially, instead of a QList<QString> the residues are abstracted
/// into another list (QList<QList<QString> where each residue ("A") is
/// converted into an html snippet that contains the color info, e.g.
/// "<span style=\"background-color:#FFFFFF\">A</span>"
///
{
    QElapsedTimer timer;
    timer.start();
    // Define themes:
    displayedSeqsColor.clear();
    seqsConservation.clear();
    QList<QString> colorSeq;
    if(displayedSeqs.length() > 1)
    {
        QList<QList<QChar>> consvWrongOrientation;
        for(int i=0; i<displayedSeqs.first().length(); i++)
        {
            QList<QChar> resList;
            for(auto&& seq: displayedSeqs)
            {
                resList.append(seq.at(i));
            }
            consvWrongOrientation.append(Sequence::calculateConservation(resList));
        }


        seqsConservation.resize(displayedSeqs.length());
        for(int i=0; i<displayedSeqs.length();i++)
        {
            for(int j=0; j<displayedSeqs.first().length(); j++)
            {
                seqsConservation[i].append(consvWrongOrientation.at(j).at(i));
            }
        }
    }
    if(consvOn && displayedSeqs.length() >1)
    {
        for(auto&& seq: seqsConservation)
        {
            colorSeq.clear();
            for(auto&& resi: seq) colorSeq.append(lookup[resi]);
            displayedSeqsColor.append(colorSeq);
        }
    }
    else
    {
        for(auto&& seq: displayedSeqs)
        {
            colorSeq.clear();
            for(auto&& resi: seq) colorSeq.append(lookup[resi]);
            displayedSeqsColor.append(colorSeq);
        }
    }


    qDebug(lnoView) << "Creating color version took" << timer.elapsed() << "milliseconds";
}

void SeqViewer::calculateRuler()
/// Residues get shifted after alignment with hyphens. This creates a list of equivalent
/// length containing the count value minus the hyphens. Essentially a poor man's graph map.
{
    displayedRuler.clear();
    int count;
    for(auto&& seq : displayedSeqs)
    {
        count = 0;
        QList<QString> counter; //is this big enough?
        for(auto && res : seq)
        {
            if(res != '-')
            {
                count += 1;
                counter.append(QString::number(count));
            }
            else counter.append("");
        }
        displayedRuler.append(counter);
        //qDebug() << displayedRuler;
    }

}

void SeqViewer::setSequenceMetrics()
/// Abstracted out this calculation (used to be done in the drawSequenceOrAlignment func)
/// in case I want to update the values elsewhere or access them in other functions.
{
    if(!displayedSeqs.isEmpty()){
        charWidth = QFontMetricsF(font()).averageCharWidth();
        if(wrapSeqs){
            numChars = trunc((QRectF(rect()).width()-document()->documentMargin()*2.0-charWidth)/charWidth);
            numBlocks = trunc(displayedSeqs.first().length()/numChars);
        }
        else
        {
            noWrapChars = trunc((QRectF(rect()).width()-document()->documentMargin()*2.0-charWidth)/charWidth);
            numChars = displayedSeqs.first().length(); // all sequences should have same length at this point! may need to validate.
            numBlocks = 0;
        }
    }
}

void SeqViewer::drawSequenceOrAlignment()
/// Gets the current width of the window and calculates the sequence split.
/// If there is color enabled, uses the color version of the sequences lists.
/// This is very slow in debug mode but fine in release. The crunch appears to be the
/// "setHtml" step at the end. Setting black and white text is very fast, but including
/// HTML makes it slow down from <10 ms to >20-50 ms sometimes. Obviously too slow for
/// rapid redraw, so during a resize event I use the black and white version to go fast.
{

    QString formatted;
    QString namesFormatted;
    QString rulerFormatted;
    setSequenceMetrics();


    if(!displayedSeqs.isEmpty())
    {

        qDebug(lnoView) << "Lengths:"<<displayedNames.length()<<displayedSeqs.length()<<displayedRuler.length()<<displayedSeqsColor.length();
        for(int i = 0; i<displayedNames.length();i++)
        {
            qDebug(lnoView)<< "Inner Lengths:"<<displayedNames.at(i).length()<<displayedSeqs.at(i).length()<<displayedRuler.at(i).length()<<displayedSeqsColor.at(i).length();
        }
        if(verticalScrollBar()->maximum() > verticalScrollBar()->minimum())
        {
            scrollPos = qreal(verticalScrollBar()->sliderPosition())/qreal(verticalScrollBar()->maximum()-verticalScrollBar()->minimum());
            //qDebug(lnoView)<<scrollPos;
            if(scrollPos < 0.05) scrollPos = 0;
        }
        if(horizontalScrollBar()->maximum()>horizontalScrollBar()->minimum())
        {
            hozScrollPos = qreal(horizontalScrollBar()->sliderPosition())/qreal(horizontalScrollBar()->maximum()-horizontalScrollBar()->minimum());
        }
        //QElapsedTimer timer;
        //timer.start();
        formatted = QString("<pre style=\"font-family:%1;;margin-left:%2px;\">").arg(font().family()).arg(round(charWidth/2.0));
        qDebug(lnoView) << formatted;
        namesFormatted = QString("<pre style=\"font-family:%1;text-align:right;\">").arg(font().family());
        rulerFormatted = QString("<pre style=\"font-family:%1;\">").arg(font().family());

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
        // lazy removal of the extra \n from the end"
        formatted.chop(2);
        formatted.append("</pre>");
        //qDebug(lnoEvent) << formatted;
        namesFormatted.chop(2);
        namesFormatted.append("</pre>");
        rulerFormatted.chop(2);
        rulerFormatted.append("</pre>");
        this->document()->setHtml(formatted);
        this->formattedNames = namesFormatted;
        this->formattedRuler = rulerFormatted;
        emit updatedNamesAndRuler(formattedNames, formattedRuler); // Send it back to Linnaeo to add to names panel.
        //qDebug(lnoView) << "The drawing operation took" << timer.elapsed() << "milliseconds";
        // This resets the scroll bar positions to their original placement.
        if(verticalScrollBar()->maximum() > verticalScrollBar()->minimum()){
            verticalScrollBar()->setSliderPosition(round(scrollPos*qreal(verticalScrollBar()->maximum()-verticalScrollBar()->minimum())));
        }
        if(horizontalScrollBar()->maximum()>horizontalScrollBar()->minimum()){
            horizontalScrollBar()->setSliderPosition(round(hozScrollPos*qreal(horizontalScrollBar()->maximum()-horizontalScrollBar()->minimum())));
        }
    }
}

void SeqViewer::noWrapUpdateRuler(){
/// Because wrap mode vs nowrap mode uses slightly different calculations, and nowrap does not need to be resized dynamically,
/// this is used in place of drawSequenceOrAlignment during resize operations.
/// It updates the position in the right hand ruler pane with the rightmost residue number (hopefully).
/// Some of this code is run in the initial drawSequence func but I don't think I can avoid the duplication;
/// just make sure to change it there too if you modify this!
    QScrollBar *bar = horizontalScrollBar();
    if(bar->maximum()>bar->minimum())
    {
        qDebug(lnoEvent) << "Sliding!" << bar->sliderPosition()<<"/"<<bar->maximum()<<"-"<<bar->minimum()<<"*"<<numChars<<"+"<<noWrapChars;
        formattedRuler = QString("<pre style=\"font-family:%1;\">").arg(font().family());
        int index=trunc(qreal(qreal(bar->sliderPosition())/(qreal(bar->maximum())-qreal(bar->minimum())))*qreal(numChars-noWrapChars))+noWrapChars;
        qDebug(lnoEvent) << int(index);
        for(int i =0;i<displayedRuler.length();i++)
        {
            QString display;
            (index < displayedRuler.at(i).length()) ? display = displayedRuler.at(i).at(index):
                                                      display = displayedRuler.at(i).last();
            qDebug(lnoEvent) << display;
            formattedRuler.append(display+"|"+displayedRuler.at(i).last()).append("\n");
        }
        formattedRuler.append("\n");
    }
    emit updatedNamesAndRuler(formattedNames, formattedRuler); // Send it back to Linnaeo to add to names panel.
    this->horizontalScrollBar()->setSingleStep(int(charWidth));

}



// Below here are all additional set-settings functions. Called by Linnaeo.


void SeqViewer::setInfoMode(bool infoMode)
{
    this->infoMode = infoMode;
    drawSequenceOrAlignment();
    callUpdateHilighting();
}

void SeqViewer::setConsv(bool consv){
    qDebug(lnoView) << "Set show colors to" << consv;
    consvOn = consv;
    if(!displayedSeqs.isEmpty()){
        calculateColor();
        drawSequenceOrAlignment();
    }
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
    currentCur.clear();
    displayedNames.clear();
    displayedRuler.clear();
    this->document()->setHtml("");
}

QStringList SeqViewer::getSeqList()
{
    return displayedSeqs;
}

void SeqViewer::fontChanged()
{
    charWidth = QFontMetricsF(font()).averageCharWidth();
    if(!displayedSeqs.isEmpty()) {
        drawSequenceOrAlignment();
        if(infoMode) callUpdateHilighting();
    }
}

// Events below here
void SeqViewer::resizeEvent(QResizeEvent *event)
{

    QTextEdit::resizeEvent(event);
    resizing = true;
    resizeTimer->start(100);
    wrapSeqs ? drawSequenceOrAlignment() : noWrapUpdateRuler();
    if(!displayedSeqs.isEmpty() && infoMode) callUpdateHilighting();

}

void SeqViewer::resizeTimeout()
{
    resizing = false;

    wrapSeqs ? drawSequenceOrAlignment() : noWrapUpdateRuler();
    if(!displayedSeqs.isEmpty() && infoMode) callUpdateHilighting();
}

void SeqViewer::updateHilighting(QTextCursor curs)
// Might be nice to have this move with the line above or below if currently over a blank line
{
    if(curs.block().text().trimmed() != "") // don't do blank lines.
    {
        if(curs.positionInBlock() < numChars) // This prevents it from highlighting the \n at the end of each line.
        {
            int line = curs.blockNumber();
            int seqBlock = trunc(line/(displayedSeqs.length()+1)); // seqBlock is all the wrapped sequences for this section
            int seq = line-seqBlock*(displayedSeqs.length()+1);
            int index = seqBlock*numChars+curs.positionInBlock();
            if(index <= displayedSeqs.at(seq).length()-1)
            {
                currentCur = {seqBlock,seq,index,curs.position()};
                //int topBlock = line-seq;
                //int botBlock = line+displayedSeqs.length()-1;
                int left = cursorRect(curs).left();
                curs.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor);
                int right =cursorRect(curs).right();
                for(int i=0; i<seq;i++) curs.movePosition(QTextCursor::Up,QTextCursor::MoveAnchor);
                int top = cursorRect(curs).top();
                for(int i=0; i<displayedSeqs.length()-1;i++) curs.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor);
                int bottom = cursorRect(curs).bottom();

                //qDebug(lnoEvent) << "top line is"<<topBlock << "bottom is" <<botBlock;
                highlightRect = {QPoint(left,top),QPoint(right,bottom)};
                this->viewport()->update();
            }
        }
    }
}



void SeqViewer::paintEvent(QPaintEvent *event)
/// This modified painter is for overlaying the INFO MODE information, based on the selected
/// cursor information.
{
    QTextEdit::paintEvent(event);
    if(infoMode && !displayedSeqs.isEmpty()){
        QRect rect = QRect(this->rect());
        if(currentCur.isEmpty()) currentCur = {0,0,4}; // Default cursor position. Need it here since I clear it sometimes.
        //
        if(highlightRect.isEmpty()){
            highlightRect = {rect.topLeft(),rect.bottomRight()};
            QTextCursor curs = QTextCursor(document());
            curs.setPosition(5);
            updateHilighting(curs);
        }

        //qDebug(lnoEvent) << "Clicked block:"<<currentCur.at(0)<<
        //                    "line" << currentCur.at(0)*(displayedSeqs.length()+1)<<
        //                    document()->findBlockByLineNumber(currentCur.at(0)*(displayedSeqs.length()+1)).text() <<
        //                    "Seq" << currentCur.at(1) <<
        //                    "Index" << currentCur.at(2) <<
        //                    "True Index" << displayedRuler.at(currentCur.at(1)).at(currentCur.at(2));

        // Set up painter.
        QPainter p(viewport());
        QPen pen = QPen("black");
        pen.setWidthF(0.5);
        p.setPen(pen);

        // Gather the clipping region that will be focused and draw a semi-transparent window over the rest.
        QRegion colReg = QRegion(rect).subtracted(QRegion(QRect(highlightRect.at(0), highlightRect.at(1))));
        QRegion orig = p.clipRegion();
        p.setClipping(true);
        p.setClipRegion(colReg);
        p.fillRect(rect,QColor(237, 237, 237, 180));
        p.setClipping(false);
        p.drawRect(QRect(highlightRect.at(0),highlightRect.at(1)));

        // Give it a bold "handle".
        pen.setWidthF(2.0);
        p.setPen(pen);
        p.drawLine(QPoint(highlightRect.at(0).x()-1,highlightRect.at(0).y()-charWidth),QPoint(highlightRect.at(0).x()-1,highlightRect.at(1).y()+charWidth));

        // Add the information about the sequences.
        p.setFont(this->font());
        //p.setBackgroundMode(Qt::OpaqueMode);
        //p.setBackground(QBrush("white"));
        QPoint textTopLeft;
        QPoint textBotRight;
        QStringList indices;
        int longestNumber = 0;
        for(int i=0; i<displayedRuler.length(); i++)
        {
            indices.append(displayedRuler.at(i).at(currentCur.at(2)));
            if(indices.last().length() > longestNumber) longestNumber = indices.last().length();
        }
        textTopLeft = QPoint(highlightRect.at(0).x()+1.5*charWidth,highlightRect.at(0).y()); // shifted to the right, aligned with the top line
        textBotRight = QPoint(textTopLeft.x()+charWidth*longestNumber,highlightRect.at(1).y());
        if(textBotRight.x() > rect.right()) // if this doesn't fit on the right side...
        {
            textTopLeft = QPoint(textTopLeft.x()-(3+longestNumber)*charWidth,textTopLeft.y());
            textBotRight = QPoint(textTopLeft.x()+charWidth*longestNumber,highlightRect.at(1).y());
        }

        QRect textRect = QRect(QPoint(textTopLeft.x()-1,textTopLeft.y()),textBotRight);
        //p.fillRect(textRect,QColor("#FFFFBF"));
        p.fillRect(textRect,QColor("#FFE9C6"));
        pen.setWidthF(0.5);
        p.setPen(pen);
        p.drawRect(textRect);

        p.drawText(QRect(textTopLeft, textBotRight),Qt::AlignLeft,indices.join("\n"));

    }
}

void SeqViewer::mousePressEvent(QMouseEvent *event)
{
    if(infoMode && !displayedSeqs.isEmpty()){
        mouseMoving = true;
        updateHilighting(cursorForPosition(event->pos()));
    }
    else
    {
        currentCur.clear();
        highlightRect.clear();
    }
}

void SeqViewer::mouseMoveEvent(QMouseEvent *event)
{
    if(infoMode && !displayedSeqs.isEmpty() && mouseMoving) updateHilighting(cursorForPosition(event->pos()));
}

void SeqViewer::mouseReleaseEvent(QMouseEvent *event)
{
    mouseMoving = false;
    //QTextEdit::mouseReleaseEvent(event);
}

void SeqViewer::callUpdateHilighting()
/// When the cursor isn't moving but the window is, this method
/// will use the saved cursor to update its position (such as
/// during a window resize, or scrolling)
{

    if(!displayedSeqs.isEmpty() && infoMode)
    {
        if(currentCur.isEmpty()) currentCur = {0,0,4};
        QTextCursor curs = QTextCursor(document());
        curs.setPosition(currentCur.at(3));
        updateHilighting(curs);
    }

}

bool SeqViewer::eventFilter(QObject *object, QEvent *ev)
{
    //qDebug(lnoEvent) << object<<ev->type();
    //if(object==this->verticalScrollBar() && (ev->type() == QEvent::Wheel || ev->type() == QEvent::Timer)) {
    //    QTextCursor curs = QTextCursor(document());
    //    curs.setPosition(currentCur.at(3));
    //    updateHilighting(curs);
    //}
    return QTextEdit::eventFilter(object, ev);
}
