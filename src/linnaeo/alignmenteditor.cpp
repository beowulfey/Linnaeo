#include "alignmenteditor.h"
#include "ui_alignmenteditor.h"

AlignmentEditor::AlignmentEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlignmentEditor)
{
    ui->setupUi(this);
    ui->seqPreview->setWordWrapMode(QTextOption::WrapAnywhere);


}

AlignmentEditor::~AlignmentEditor()
{
    delete ui;
    //QFontDatabase::addApplicationFont(":/fonts/Noto-Custom.ttf");
    //ui->seqPreview->document()->setDefaultFont(QFont("Noto Custom", 10.0, 1));
}

void AlignmentEditor::setData(QStringList names, QStringList seqs)
{
    qDebug(lnoView) << names << seqs;
    QStandardItemModel *model = new QStandardItemModel;
    for(int i = 0; i < seqs.length(); i++)
    {
        QStandardItem *listItem = new QStandardItem(names.at(i));
        listItem->setData(seqs.at(i),Linnaeo::SequenceRole);
        listItem->setDropEnabled(false);
        model->appendRow(listItem);
    }
    ui->alignListView->setModel(model);
}

void AlignmentEditor::setDocFont(QFont font)
{
    ui->alignListView->setFont(font);
    ui->seqPreview->setFont(font);
}

void AlignmentEditor::on_alignListView_clicked(const QModelIndex &index)
{
    ui->seqPreview->setPlainText(Sequence::prettyPrintFastaSequence(
                                     index.data(Qt::DisplayRole).toString(),
                                     index.data(Linnaeo::SequenceRole).toString(),
                                     index.data(Linnaeo::SequenceRole).toString().length()));
}

QList<QStringList> AlignmentEditor::chosenArrangement()
{
    QStringList names;
    QStringList seqs;
    for(int i=0;i<ui->alignListView->model()->rowCount();i++)
    {
        names.append(ui->alignListView->model()->index(i,0).data(Qt::DisplayRole).toString());
        seqs.append(ui->alignListView->model()->index(i,0).data(Linnaeo::SequenceRole).toString());
    }
    return {names, seqs};
}
