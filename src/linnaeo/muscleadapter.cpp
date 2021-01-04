#include "muscleadapter.h"

MuscleAdaptor::MuscleAdaptor(QObject *parent) : QObject(parent)
{

}

int MuscleAdaptor::run(QString input, QString output)
{
    char argc = 4;
    QByteArray inputName = input.toLocal8Bit();
    QByteArray outputName = output.toLocal8Bit();

    char *argv[] = {
        (char*)("-in"),
        (char*)(inputName.data()),
        (char*)("-out"),
        (char*)(outputName.data())
    };

    SetNewHandler();
    SetStartTime();
    ProcessArgVect(argc, argv);
    SetParams();
    SetLogFile();
    qInfo(lnoProc) << "Beginning MUSCLE run";
    if (g_bCatchExceptions)
        {
        try
            {
            qDebug(lnoProc) << "In try/catch";
            Run();
            }
        catch (...)
            {
            qWarning(lnoProc) << "Detected MUSCLE exception!";
            OnException();
            exit(EXIT_Except);
            return EXIT_Except;

            }
        }
    else

        Run();
    qInfo(lnoProc) << "Run completed with success!";
    //exit(EXIT_Success);
    return 0;
}

