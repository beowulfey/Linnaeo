#include "seqentrytextedit.h"
#include <QMimeData>
#include <QRegularExpression>
#include <iostream>
#include "spdlog/spdlog.h"

void SeqEntryTextEdit::insertFromMimeData(const QMimeData * source)
/// SeqEntryTextEdit
/// This is a little code segment that essentially parses the pasted sequence.
/// Will eventually need to abstract this out!
{
    if (source->hasText())
    {
        QString text = source->text();
        QList<QString> list = text.split(QRegularExpression("(\\n|\\r)"));
        QString info;
        QString seq;
        if (QString(text.at(0)) == QString(">"))
        {
            spdlog::debug("Detected FASTA format. Trimming title of sequence.");
            info = list.takeFirst();
            emit extractedSeqName(info);
            seq = list.join("");
        }
        else
        {
            seq = list.join("");
        }
        // Insert the sequence in the text edit
        QTextCursor cursor = textCursor();
        cursor.insertText(seq);
        emit pastedSequence(seq);

    }
}
