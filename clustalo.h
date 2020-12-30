#ifndef CLUSTALO_H
#define CLUSTALO_H

extern "C" {
#include "clustal-omega.h"
#include "hhalign/general.h"
}
#include "linnaeo.h"



// Static function wrapper for calling clustal omega.
class ClustalO
{
public:

    static QHash<QString,QString> align(QHash<QString,QString> seqs);

    typedef struct {
        /// Wrapped opt_t from clustal-omega.h for simplicity!
        /// changes here will have to be reflected in FreeAlnOpts(),
        /// SetDefaultAlnOpts(), AlnOptsLogicCheck() etc
        ///
        bool bAutoOptions;                      // auto: Clustal knows what is good for you

        // Distance matrix
        char *pcDistmatInfile;                  // distance matrix input file
        char *pcDistmatOutfile;                 // distance matrix output file

        // Clustering / guide-tree
        int iClusteringType;                    // clustering type (from cmdline arg)
        int iClustersizes;                      // number of sequences in cluster
        char *pcClustfile;                      // file with clustering information
        int iTransitivity;                      // use transitivity
        char *pcPosteriorfile;                  // file with posterior probability information
        int iPairDistType;                      // pairwise distance method
        bool bUseMbed;                          // use mbed-like clustering
        bool bUseMbedForIteration;              // use mbed-like clustering also during iteration
        bool bPileup;                           // pile-up flag
        char *pcGuidetreeOutfile;               // guidetree output file
        char *pcGuidetreeInfile;                // guidetree input file
        bool bUseKimura;                        // use Kimura corrected distance
        bool bPercID;                           // print percentage identity

        // HMMs
        char **ppcHMMInput;                     // HMM input files. index range: 0..iHMMInputFiles
        int iHMMInputFiles;                     // No. of HMM input files provided. Need for ppcHMMInput
        char *pcHMMBatch;                       // HMM batch-file, specify HMMs for individual sequences

        // Iteration
        int iNumIterations;                     // number of iterations
        bool bIterationsAuto;                   // determine number of iterations automatically
        int iMaxHMMIterations;                  // maximum number of hmm iterations
        int iMaxGuidetreeIterations;            // max number of guidetree iterations

        hhalign_para rHhalignPara;

    } opts_t;

};

#endif // CLUSTALO_H
