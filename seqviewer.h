#ifndef SEQVIEWER_H
#define SEQVIEWER_H

#include <QTextEdit>
#include <QTimer>

class SeqViewer : public QTextEdit
{
    Q_OBJECT
public:
    explicit SeqViewer(QWidget *parent);

    void clearViewer();
    void setDisplaySequence(QString seq, QString name);
    void setDisplayAlignment(QList<QString> seqs, QList<QString> names);
    void setTheme(int index);
    void setColors(bool colors);
    //void startDisplayThread();
    QList<QString> getSeqList();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool colorOn = true;
    bool resizing = false;
    int numBlocks;
    QTimer *resizeTimer;
    QHash<QChar, QString> lookup;
    QList<QString> displayedNames;
    QList<QString> displayedSeqs;
    QList<QList<QString>> displayedSeqsColor;

    void calculateColor();
    void drawSequenceOrAlignment();
    void resizeTimeout();

signals:
    void updatedNamesAndRuler(const QString names);
};



#endif // SEQVIEWER_H
