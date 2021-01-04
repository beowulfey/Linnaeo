#ifndef MUSCLEADAPTOR_H
#define MUSCLEADAPTOR_H

#include "logging.h"
#include <QObject>
#include "external/muscle/muscle.h"

class MuscleAdaptor : public QObject
{
    Q_OBJECT
public:
    explicit MuscleAdaptor(QObject *parent = nullptr);
    int run(QString input, QString output);

private:

};

#endif // MUSCLEADAPTOR_H
