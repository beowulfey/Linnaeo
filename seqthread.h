#ifndef SEQTHREAD_H
#define SEQTHREAD_H

#include <QThread>
#include "seqviewer.h"

class SeqThread : public QThread
{
    Q_OBJECT
public:
    SeqThread(SeqViewer *parent, QString *input, bool showColor);
    void run() override;

signals:
    void resultReady(const QString &s);

private:
    QString result;
    //bool showRuler;

    int width;
    float charWidth;
    int numChars;
    int numBlocks;
};

#endif // SEQTHREAD_H
