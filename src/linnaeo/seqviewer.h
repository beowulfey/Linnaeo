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
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    qreal charWidth;
    int numChars;
    int numBlocks;
    int noWrapChars;
    int infoPos = 5;
    bool mouseMoving = false;
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
    QList<QList<QChar>> seqsConservation;
    QString formattedNames;
    QString formattedRuler;
    QList<int> currentCur;
    QList<QPoint> highlightRect;

    void calculateColor();
    void calculateRuler();
    void drawSequenceOrAlignment();
    void resizeTimeout();
    void setSequenceMetrics();
    void updateHilighting(QTextCursor);

private slots:
    void noWrapUpdateRuler();
    void callUpdateHilighting();

signals:
    void updatedNamesAndRuler(const QString names, const QString ruler);
};



#endif // SEQVIEWER_H
