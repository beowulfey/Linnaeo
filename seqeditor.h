#ifndef SEQEDITOR_H
#define SEQEDITOR_H

#include <QDialog>
#include "seqentrytextedit.h"

namespace Ui {
class SeqEditor;
}

class SeqEditor : public QDialog
{
    Q_OBJECT

public:
    explicit SeqEditor(QWidget *parent = nullptr);
    ~SeqEditor();
    QString submittedSequence();
    QString submittedName();

private:
    Ui::SeqEditor *ui;
    SeqEntryTextEdit *seqEntryEditor;
    QString info;
    QString name;
    QString seq;

private slots:
    void receivedSequence(QString seq);
    void receivedSeqInfo(QString info);
};

#endif // SEQEDITOR_H
