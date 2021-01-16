#include "alignmenteditor.h"
#include "ui_alignmenteditor.h"

AlignmentEditor::AlignmentEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlignmentEditor)
{
    ui->setupUi(this);
}

AlignmentEditor::~AlignmentEditor()
{
    delete ui;
}

