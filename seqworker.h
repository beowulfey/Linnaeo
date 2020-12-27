#ifndef SEQWORKER_H
#define SEQWORKER_H

#include <QObject>
class SeqWorker : public QObject
{
    Q_OBJECT
public:
    explicit SeqWorker(QObject *parent);
    void generateSeqDisplay();

signals:
    void resultReady(const QString &s);

private:
    bool colors;
    bool ruler;
    bool secstruct;

};
#endif // SEQWORKER_H

