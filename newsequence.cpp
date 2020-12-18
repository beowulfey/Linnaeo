#include "newsequence.h"
#include "ui_newsequence.h"

NewSequence::NewSequence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSequence)
{
    ui->setupUi(this);
}

NewSequence::~NewSequence()
{
    delete ui;
}
