#include "alignworker.h"
#include "sequence.h"
#include <QTemporaryFile>
#include <QTemporaryDir>
#include <QDir>
#include <QStandardPaths>
#include <QProcess>
#include <QMessageBox>

AlignWorker::AlignWorker(QString input)
{
    seqs = input;

}

void AlignWorker::run()
// Currently hardcoded. Need to make it more flexible!!
{
    QTemporaryDir tempDir;
    QString result;
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
        qDebug() <<result;
        emit resultReady(Sequence::parseFastaString(result));


    }

}
