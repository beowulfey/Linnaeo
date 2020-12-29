#ifndef CLUSTALO_H
#define CLUSTALO_H

#include "linnaeo.h"
extern "C" {
#include "clustal-omega.h"
}

/// Static function wrapper for calling clustal omega.
class ClustalO
{
public:

    static QHash<QString,QString> align(QHash<QString,QString> seqs);
    typedef struct {
        /* auto: Clustal (know what) is good for you
         */
        bool bAutoOptions;

        /* Distance matrix
         */
        /** distance matrix input file */
        char *pcDistmatInfile;
        /** distance matrix output file */
        char *pcDistmatOutfile;

        /* Clustering / guide-tree
         */
        /** clustering type (from cmdline arg) */
        int iClusteringType;
        /** number of sequences in cluster */
        int iClustersizes;
        /** file with clustering information */
        char *pcClustfile;
        /** use transitivity */
        int iTransitivity;
        /** file with posterior probability information */
        char *pcPosteriorfile;
        /** pairwise distance method */
        int iPairDistType;
        /** use mbed-like clustering */
        bool bUseMbed;
        /** use mbed-like clustering also during iteration */
        bool bUseMbedForIteration;
        /** pile-up flag */
        bool bPileup;
        /** guidetree output file */
        char *pcGuidetreeOutfile;
        /** guidetree input file */
        char *pcGuidetreeInfile;
        /** use Kimura corrected distance */
        bool bUseKimura;
        /** print percentage identity */
        bool bPercID;

        /* HMMs
         */
        /** HMM input files. index range: 0..iHMMInputFiles */
        char **ppcHMMInput;
        /** number of provided HMM input files. not really a user
           option but need for ppcHMMInput */
        int iHMMInputFiles;
        /** HMM batch-file, specify HMMs for individual sequences. FS, r291 -> */
        char *pcHMMBatch;

        /* Iteration
         */
        /** number of iterations */
        int iNumIterations;
        /** determine number of iterations automatically */
        bool bIterationsAuto;
        /** maximum number of hmm iterations */
        int iMaxHMMIterations;
        /** max number of guidetree iterations */
        int iMaxGuidetreeIterations;

        /* WOLFEY ADDED */
        int iOutputOrder;

        hhalign_para rHhalignPara;

        /* changes here will have to be reflected in FreeAlnOpts(),
         * SetDefaultAlnOpts(), AlnOptsLogicCheck() etc
         */
    } opts_t;
};


#endif // CLUSTALO_H
