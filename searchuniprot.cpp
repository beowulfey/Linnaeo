#include "searchuniprot.h"
#include "ui_searchuniprot.h"
#include "spdlog/spdlog.h"
#include <QNetworkReply>

SearchUniprot::SearchUniprot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchUniprot)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(this->manager, &QNetworkAccessManager::finished, this, &SearchUniprot::httpFinished);
    connect(manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT( sslErrorOccured(QNetworkReply*,QList<QSslError>)));

}

SearchUniprot::~SearchUniprot()
{
    delete ui;
    delete manager;
}

void SearchUniprot::on_searchButton_clicked()
{
    const QUrl url = QUrl(QString("https://www.uniprot.org/uniprot/?query=").append(QString(ui->queryBox->text().replace(" ","+")))
                          .append("&limit=10&format=tab&columns=id,entry%20name,gene%20name,organism,protein%20names,sequence"));

    request.setUrl(url);
    spdlog::info("Searching with URL {}", url.toDisplayString().toStdString());
    manager->get(request);

}

void SearchUniprot::httpFinished(QNetworkReply *reply)
{
    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }
        QString answer = reply->readAll();
        QList<QString> list = answer.split("\\n");
        qDebug() << list;
}

void SearchUniprot::sslErrorOccured(QNetworkReply *reply, QList<QSslError>)
{
    if(reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }
}
