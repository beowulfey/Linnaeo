#include "searchuniprot.h"
#include "ui_searchuniprot.h"

SearchUniprot::SearchUniprot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchUniprot)
{
    ui->setupUi(this);
}

SearchUniprot::~SearchUniprot()
{
    delete ui;
}
