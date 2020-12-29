#include "clustalo.h"

extern "C" {
#include "clustal-omega.h"
#include "clustal/seq.h"
}

QHash<QString,QString> ClustalO::align(QHash<QString, QString> seqs)
{
    QHash<QString,QString> aligned;

    mseq_t *prMSeq = NULL;
    int iThreads = 1;
    opts_t rAlnOpts;

    return aligned;

}
