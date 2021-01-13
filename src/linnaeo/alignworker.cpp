#include "muscleadapter.h"
#include "logging.h"
#include "alignworker.h"
#include "sequence.h"
#include <QTemporaryFile>
#include <QTemporaryDir>
#include <QDir>
#include <QStandardPaths>
#include <QProcess>
#include <QMessageBox>

/// MEMORY LEAK PROBLEMS HERE (KEEPS SAME MUSCLE INSTANCE!?)

AlignWorker::AlignWorker(QObject *parent) : QThread(parent)
{
    mcsl = new MuscleAdaptor();

}


AlignWorker::~AlignWorker()
{
    delete mcsl;
    this->quit();

}

void AlignWorker::setSeqs(QString input)
{
    seqs = input;
}

void AlignWorker::run()
{
    QString result;
    QTemporaryDir tempDir;
    if(tempDir.isValid())
    {
        QFile input(tempDir.path()+"/input.fasta");
        if (input.open(QIODevice::WriteOnly | QIODevice::Text))
        {
           QTextStream out(&input);
           out << seqs;
           input.close();
        }
        int mcslResult = mcsl->run(input.fileName(), tempDir.path()+"/output.fasta");
        if(mcslResult == 0)
        {
            QFile aligned(tempDir.path()+"/output.fasta");
            if (aligned.open(QIODevice::ReadOnly | QIODevice::Text))
            {
               QTextStream in(&aligned);
               while (!in.atEnd())
               {
                  result.append(in.readAll());
               }
               aligned.close();
            }
            tempDir.remove();
            emit resultReady(Sequence::splitFastaAlignmentString(result));
        }
        else
        {
            emit resultFailed(mcslResult);
        }
    }



    /*
     * QString result;
    QStringList args;

    if(tempDir.isValid())
    {
        QProcess proc = QProcess(this);
        proc.setWorkingDirectory(tempDir.path());
        args <<"-i"<<tempDir.path()+"/input.fasta"<<"--output-order=tree-order"<<"--threads=8"<<"--verbose"<<"--force"<<"-o"<<tempDir.path()+"/output.fasta";
        QFile input(tempDir.path()+"/input.fasta");
        if (input.open(QIODevice::WriteOnly | QIODevice::Text))
        {
           QTextStream out(&input);
           out << seqs;
           input.close();
        }
        QString outputFile = tempDir.path()+"/output.fasta";
        QFile aligned(outputFile);

        proc.execute("C:/Users/wolfe/devel/clustal-omega/dist/clustalo/bin/clustalo.exe",args);

        if (aligned.open(QIODevice::ReadOnly | QIODevice::Text))
        {
           QTextStream in(&aligned);
           while (!in.atEnd())
           {
              result.append(in.readAll());
           }
           aligned.close();
        }
        tempDir.remove();
        emit resultReady(Sequence::splitFastaAlignmentString(result));


    }*/

}
