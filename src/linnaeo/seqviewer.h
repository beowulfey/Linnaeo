#ifndef SEQVIEWER_H
#define SEQVIEWER_H

#include <QTextEdit>
#include <QTimer>
//#include <QTextFrame>

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
    void fontChanged();
    void setInfoMode(bool);
    //void startDisplayThread();
    QList<QString> getSeqList();

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void paintEvent(QPaintEvent *event) override;

private:
    qreal charWidth;
    int numChars;
    int numBlocks;
    int noWrapChars;

    bool infoMode = false;
    bool wrapSeqs = true;
    bool resizing = false;
    bool colorOn = true;
    bool rulerOn = false;
    double scrollPos;
    double hozScrollPos;

    QTextFrameFormat *form;
    QTimer *resizeTimer;
    QHash<QChar, QString> lookup;
    QList<QString> displayedNames;
    QList<QString> displayedSeqs;
    QList<QList<QString>> displayedSeqsColor;
    QList<QList<QString>> displayedRuler;
    QString formattedNames;
    QString formattedRuler;

    void calculateColor();
    void calculateRuler();
    void drawSequenceOrAlignment();
    void resizeTimeout();
    void drawCursor();
    void setSequenceMetrics();

private slots:
    void noWrapUpdateRuler(int val=0);

signals:
    void updatedNamesAndRuler(const QString names, const QString ruler);
};



#endif // SEQVIEWER_H
