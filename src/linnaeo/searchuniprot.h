#ifndef SEARCHUNIPROT_H
#define SEARCHUNIPROT_H

#include <QDialog>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QStandardItemModel>
#include <QStatusBar>

namespace Ui {
class SearchUniprot;
}

class SearchUniprot : public QDialog
{
    Q_OBJECT

public:
    explicit SearchUniprot(QWidget *parent = nullptr);
    ~SearchUniprot();
    QStringList chosenIds();
    QStringList chosenNames();
    QStringList chosenOrganisms();
    QStringList chosenGenes();
    QStringList chosenProteins();
    QStringList chosenSequences();
    int chosenNameSource();

private slots:
    void on_searchButton_clicked();
    void httpFinished(QNetworkReply *reply);
    void sslErrorOccured(QNetworkReply *reply, QList<QSslError>);

private:
    const QStringList LABELS;
    Ui::SearchUniprot *ui;
    QStatusBar *bar;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QStandardItemModel *resultsModel;


};

#endif // SEARCHUNIPROT_H
