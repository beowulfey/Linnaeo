#include "searchuniprot.h"
#include "ui_searchuniprot.h"
#include "logging.h"
#include <QNetworkReply>


// TODO: MOVE THE SEARCH INTO A NEW THREAD! Otherwise it crashes if I try and close early!

SearchUniprot::SearchUniprot(QWidget *parent) :
    QDialog(parent),
    LABELS({"Entry", "Name", "Gene Name", "Organism", "Description", "Sequence"}),
    ui(new Ui::SearchUniprot)
{
    QStringList comboLabels = LABELS;
    this->setWindowTitle("Sequence Browser");
    comboLabels.remove(3,3);
    ui->setupUi(this);
    ui->nameCombo->addItems(comboLabels);
    ui->nameCombo->setCurrentIndex(2);
    manager = new QNetworkAccessManager(this);
    connect(this->manager, &QNetworkAccessManager::finished, this, &SearchUniprot::httpFinished);
    connect(manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT( sslErrorOccured(QNetworkReply*,QList<QSslError>)));
    resultsModel = new QStandardItemModel(this);
    resultsModel->setColumnCount(6);
    resultsModel->setHorizontalHeaderLabels(LABELS);
    ui->resultsTable->setModel(resultsModel);
    ui->resultsTable->setColumnHidden(5,true);
    bar = new QStatusBar(this);
    ui->verticalLayout->addWidget(bar);
    bar->showMessage("Waiting for query!", 2500);
}

SearchUniprot::~SearchUniprot()
{
    delete ui;
    delete manager;
}

void SearchUniprot::on_searchButton_clicked()
{
    if (ui->queryBox->text().isEmpty())
    {
        bar->showMessage("Please enter a query!",1500);
    }
    else
    {
        ui->searchButton->setDisabled(true);
        resultsModel->removeRows(0, resultsModel->rowCount());
        bar->showMessage("Searching online, please wait...");
        QUrl url;
        if(ui->reviewedCheckBox)
        {
            url = QUrl(QString("https://www.uniprot.org/uniprot/?query=reviewed:yes+AND+").append(QString(ui->queryBox->text()))//.replace(" ","+").replace(":","%3A")))
                             .append("&sort=score&limit=10&format=tab&columns=id,entry%20name,genes(PREFERRED),organism,protein%20names,sequence"));
        }
        else
        {
            url = QUrl(QString("https://www.uniprot.org/uniprot/?query=").append(QString(ui->queryBox->text()))//.replace(" ","+").replace(":","%3A")))
                             .append("&sort=score&limit=10&format=tab&columns=id,entry%20name,genes(PREFERRED),organism,protein%20names,sequence"));
        }

        request.setUrl(url);
        qInfo(lnoIo)<<"Searching with URL\n" << url.toDisplayString();
        manager->get(request);
    }

}

void SearchUniprot::httpFinished(QNetworkReply *reply)
/// Takes the response from UniPROT and parses it into a TableView for users.
/// Highlighted rows are copied into the Linnaeo Sequence Table
{
    ui->searchButton->setDisabled(false);
    bar->showMessage("Search complete");
    if (reply->error())
    {
        qDebug(lnoIo) << reply->errorString();
        bar->showMessage("Unable to search UniPROT!");
        return;
    }
    // If no error, parse the result:
    QString answer = reply->readAll();
    QList<QString> resultList = answer.split("\n", Qt::SkipEmptyParts);
    // First row is the header (already known) so just drop it
    resultList.takeFirst();
    //spdlog::info("Search returned {} items", resultList.size());
    QString row;
    QString column;
    QStandardItem *item;
    QList<QStandardItem*> rowItems;
    foreach(row, resultList)
    {
        rowItems.clear();
        foreach(column, row.split("\t"))
        {
            item = new QStandardItem(column);
            rowItems.append(item);

        }
        resultsModel->appendRow(rowItems);
    }


}

QStringList SearchUniprot::chosenIds()
{
    QList<QModelIndex> selectedFromColumn = ui->resultsTable->selectionModel()->selectedRows(0);
    QModelIndex itemIndex;
    QStringList convertedToStrings;
    foreach(itemIndex, selectedFromColumn)
    {
        convertedToStrings.append(itemIndex.data().toString());
    }
    return convertedToStrings;
}

QStringList SearchUniprot::chosenNames()
{
    QList<QModelIndex> selectedFromColumn = ui->resultsTable->selectionModel()->selectedRows(1);
    QModelIndex itemIndex;
    QStringList convertedToStrings;
    foreach(itemIndex, selectedFromColumn)
    {
        convertedToStrings.append(itemIndex.data().toString());
    }
    return convertedToStrings;
}

QStringList SearchUniprot::chosenOrganisms()
{
    QList<QModelIndex> selectedFromColumn = ui->resultsTable->selectionModel()->selectedRows(3);
    QModelIndex itemIndex;
    QStringList convertedToStrings;
    foreach(itemIndex, selectedFromColumn)
    {
        convertedToStrings.append(itemIndex.data().toString());
    }
    return convertedToStrings;
}

QStringList SearchUniprot::chosenGenes(){
    QList<QModelIndex> selectedFromColumn = ui->resultsTable->selectionModel()->selectedRows(2);
    QModelIndex itemIndex;
    QStringList convertedToStrings;
    foreach(itemIndex, selectedFromColumn)
    {
        convertedToStrings.append(itemIndex.data().toString());
    }
    return convertedToStrings;
}

QStringList SearchUniprot::chosenProteins(){
    QList<QModelIndex> selectedFromColumn = ui->resultsTable->selectionModel()->selectedRows(4);
    QModelIndex itemIndex;
    QStringList convertedToStrings;
    foreach(itemIndex, selectedFromColumn)
    {
        convertedToStrings.append(itemIndex.data().toString());
    }
    return convertedToStrings;
}

QStringList SearchUniprot::chosenSequences()
/// Returns the column of sequences selected in the tableview.
{
    QList<QModelIndex> selectedFromColumn = ui->resultsTable->selectionModel()->selectedRows(5);
    QModelIndex itemIndex;
    QStringList convertedToStrings;
    foreach(itemIndex, selectedFromColumn)
    {
        convertedToStrings.append(itemIndex.data().toString());
    }
    return convertedToStrings;
}

int SearchUniprot::chosenNameSource()
{
    QString chosen = ui->nameCombo->currentText();
    if(chosen == LABELS.at(0)) return 0;
    if(chosen == LABELS.at(1)) return 1;
    if(chosen == LABELS.at(2)) return 2;
    return -1;
}

void SearchUniprot::sslErrorOccured(QNetworkReply *reply, QList<QSslError>)
{
    if(reply->error())
    {
        qDebug(lnoIo) << reply->errorString();
        return;
    }
}
