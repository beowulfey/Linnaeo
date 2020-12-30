#ifndef ALIGNWORKER_H
#define ALIGNWORKER_H

#include <QThread>

class AlignWorker : public QThread
{
    Q_OBJECT
public:
    AlignWorker(QString input);
    void run() override;
signals:
    void resultReady(const QHash<QString,QString> &s);
private:
    QString seqs;
};

#endif // ALIGNWORKER_H
