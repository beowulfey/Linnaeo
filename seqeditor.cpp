#include "seqeditor.h"
#include "ui_seqeditor.h"
#include "seqentrytextedit.h"
#include <iostream>
#include <QRegularExpression>
#include "spdlog/spdlog.h"

/// Opens up a window for creating and editing sequence information.

SeqEditor::SeqEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeqEditor)
{
    ui->setupUi(this);
    seqEntryEditor = new SeqEntryTextEdit(this);
    ui->verticalLayout->insertWidget(3,seqEntryEditor);
    connect(this->seqEntryEditor, &SeqEntryTextEdit::pastedSequence, this, &SeqEditor::receivedSequence);
    connect(this->seqEntryEditor, &SeqEntryTextEdit::extractedSeqName, this, &SeqEditor::receivedSeqInfo);
}

SeqEditor::~SeqEditor()
{
    delete ui;
}

QString SeqEditor::submittedSequence()
{
    // TODO: VALIDATE THE SEQUENCE!!
    this->seq = this->seqEntryEditor->toPlainText();
    return this->seq;
}

QString SeqEditor::submittedName()
{
    this->info = ui->seqNameEdit->text();
    return this->info;
}

void SeqEditor::receivedSequence(QString seq)
{
    this->seq = seq;
    spdlog::debug("Sequence imported:\n{}", seq.toStdString());

}

void SeqEditor::receivedSeqInfo(QString infoIn)
{
    this->info = infoIn.split(QRegularExpression("\\s"))[0];
    ui->seqNameEdit->setText(this->info);
}
