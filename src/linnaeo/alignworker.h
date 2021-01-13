#ifndef ALIGNWORKER_H
#define ALIGNWORKER_H

#include "muscleadapter.h"
#include <QThread>

class AlignWorker : public QThread
{
    Q_OBJECT
public:
    AlignWorker(QObject *parent);
    void setSeqs(QString);
    void run() override;
    ~AlignWorker();
signals:
    void resultReady(const QList<QStringList> s);
    void resultFailed(int err);
private:
    QString seqs;
    MuscleAdaptor *mcsl;

};

#endif // ALIGNWORKER_H
