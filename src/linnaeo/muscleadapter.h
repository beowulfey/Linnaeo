#ifndef MUSCLEADAPTOR_H
#define MUSCLEADAPTOR_H

#include "logging.h"
#include <QObject>
#include "muscle/muscle.h"

/// This takes the place of "main.cpp" from the MUSCLE program.
/// The constructor just exists to hold the run function and probably
/// isn't necessary.
class MuscleAdaptor : public QObject
{
    Q_OBJECT
public:
    explicit MuscleAdaptor(QObject *parent = nullptr);
    int run(QString input, QString output);

private:

};

#endif // MUSCLEADAPTOR_H
