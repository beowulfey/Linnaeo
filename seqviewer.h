#ifndef SEQVIEWER_H
#define SEQVIEWER_H

#include <QTextEdit>

class SeqViewer : public QTextEdit
{
    Q_OBJECT
public:
    explicit SeqViewer(QWidget *parent);

    void clearViewer();
    void displaySequence(QString seq, QString name);
    void displayAlignment(QList<QString> alignment);
    void startDisplayThread();
    QList<QString> getSeqList();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool colorOn;
    QList<QString> displayedNames;
    QList<QString> displayedSeqs;
    QList<QList<QString>> displayedSeqsColor;

    void calculateColor();
    void drawSequenceOrAlignment();

signals:

};



#endif // SEQVIEWER_H
