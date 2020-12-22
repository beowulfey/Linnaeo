#ifndef SEARCHUNIPROT_H
#define SEARCHUNIPROT_H

#include <QDialog>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

namespace Ui {
class SearchUniprot;
}

class SearchUniprot : public QDialog
{
    Q_OBJECT

public:
    explicit SearchUniprot(QWidget *parent = nullptr);
    ~SearchUniprot();

private slots:
    void on_searchButton_clicked();
    void httpFinished(QNetworkReply *reply);
    void sslErrorOccured(QNetworkReply *reply, QList<QSslError>);

private:
    Ui::SearchUniprot *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;


};

#endif // SEARCHUNIPROT_H
