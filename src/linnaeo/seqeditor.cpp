#include "seqeditor.h"
#include "ui_seqeditor.h"
#include "seqentrytextedit.h"
#include <iostream>
#include <QRegularExpression>
//#include "spdlog/spdlog.h"
#include "sequence.h"

/// Opens up a window for creating and editing sequence information.

SeqEditor::SeqEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeqEditor)
{
    ui->setupUi(this);
    connect(ui->seqEntryEditor, &SeqEntryTextEdit::pastedSequence, this, &SeqEditor::receivedSequence);
    connect(ui->seqEntryEditor, &SeqEntryTextEdit::extractedSeqName, this, &SeqEditor::receivedSeqInfo);
}

SeqEditor::SeqEditor(QWidget *parent, QString seqName, QString seq, QString seqInfo) :
    QDialog(parent),
    ui(new Ui::SeqEditor)
{
    ui->setupUi(this);
    connect(ui->seqEntryEditor, &SeqEntryTextEdit::pastedSequence, this, &SeqEditor::receivedSequence);
    connect(ui->seqEntryEditor, &SeqEntryTextEdit::extractedSeqName, this, &SeqEditor::receivedSeqInfo);
    QLineEdit *infoLine = new QLineEdit(seqInfo);
    ui->verticalLayout->addWidget(infoLine);
    ui->seqEntryEditor->setPlainText(seq);
    ui->seqNameEdit->setText(seqName);
}

SeqEditor::~SeqEditor()
{
    delete ui;
}

QString SeqEditor::submittedSequence()
{
    // TODO: VALIDATE THE SEQUENCE!!
    this->seq = ui->seqEntryEditor->toPlainText();
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
    //spdlog::debug("Sequence imported:\n{}", seq.toStdString());

}

void SeqEditor::receivedSeqInfo(QString infoIn)
{
    this->info = infoIn.split(QRegularExpression("\\s"))[0];
    ui->seqNameEdit->setText(this->info);
}
