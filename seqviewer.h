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
    void setWrapSeqs(bool wrap);
    //void startDisplayThread();
    QList<QString> getSeqList();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool wrapSeqs = true;
    bool resizing = false;
    bool colorOn = true;
    bool rulerOn = false;
    int numBlocks;
    double scrollPos;
    QTimer *resizeTimer;
    QHash<QChar, QString> lookup;
    QList<QString> displayedNames;
    QList<QString> displayedSeqs;
    QList<QList<QString>> displayedSeqsColor;
    QList<QList<QString>> displayedRuler;

    void calculateColor();
    void calculateRuler();
    void drawSequenceOrAlignment();
    void resizeTimeout();


signals:
    void updatedNamesAndRuler(const QString names, const QString ruler);
};



#endif // SEQVIEWER_H
