/*
#ifndef SEQWORKER_H
#define SEQWORKER_H

#include <QThread>
class SeqWorker : public QThread
{
    Q_OBJECT
public:
    explicit SeqWorker(QObject *parent);
    void run(QString *input) override;

signals:
    void resultReady(const QString &s);

};
#endif // SEQWORKER_H
*/
