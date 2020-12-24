#ifndef SEQVIEWER_H
#define SEQVIEWER_H

#include <QTextEdit>

class SeqViewer : public QTextEdit
{
    Q_OBJECT
public:
    explicit SeqViewer(QWidget *parent);

    void clearViewer();
    void displaySequence(QString seq);
    void displayAlignment(QList<QString> alignment);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QFont seqFont;
    QList<QString> displayedSeqs; //can this be on the stack?

    void drawSequenceOrAlignment();

signals:



};

#endif // SEQVIEWER_H
