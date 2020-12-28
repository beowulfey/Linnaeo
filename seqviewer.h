#ifndef SEQVIEWER_H
#define SEQVIEWER_H

#include <QTextEdit>

class SeqViewer : public QTextEdit
{
    Q_OBJECT
public:
    explicit SeqViewer(QWidget *parent);

    void clearViewer();
    void setDisplaySequence(QString seq, QString name);
    void setDisplayAlignment(QList<QString> alignment);
    void setTheme(int index);
    void setColors(bool colors);
    //void startDisplayThread();
    QList<QString> getSeqList();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool colorOn = true;
    QHash<QChar, QString> lookup;
    QList<QString> displayedNames;
    QList<QString> displayedSeqs;
    QList<QList<QString>> displayedSeqsColor;

    void calculateColor();
    void drawSequenceOrAlignment();

signals:

};



#endif // SEQVIEWER_H
