#ifndef SEQENTRYTEXTEDIT_H
#define SEQENTRYTEXTEDIT_H

#include <QPlainTextEdit>

class SeqEntryTextEdit : public QPlainTextEdit
{
    /// This exists solely so I can capture the pasted input into the text box.
    Q_OBJECT
public:
    SeqEntryTextEdit(QWidget *parent) : QPlainTextEdit(parent) {}
    void insertFromMimeData(const QMimeData * source) override;
signals:
    void pastedSequence(QString seq);
    void extractedSeqName(QString name);
};

#endif // SEQENTRYTEXTEDIT_H
