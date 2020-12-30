#include "clustalo.h"

#include "clustal-omega.h"


QHash<QString,QString> ClustalO::align(QHash<QString, QString> seqs)
{
    QHash<QString,QString> aligned;
    aligned["TEST"] = "testing";

    mseq_t *prMSeq = NULL;
    int iThreads = 1;
    opts_t rAlnOpts;

    LogDefaultSetup(&rLog);
    SetDefaultAlnOpts(&rAlnOpts);
    return aligned;
}

