#include "sequence.h"
#include "logging.h"

namespace Sequence
{
    QList<QStringList> splitFastaAlignmentString(QString input)
    /// Reads in an alignment string and returns a 2mer list of lists
    /// First list is a list of names of each sequence
    /// Second list is a list of the sequences themselves.
    {
        //qDebug()<<input.trimmed();
        QList<QStringList> result;
        QStringList names;
        QStringList seqs;
        QString curName;
        QString curSeq;
        QListIterator<QString> seg(input.trimmed().split("\n"));
        while(seg.hasNext())
        {

            if(seg.peekNext()[0] == '>' && seg.hasPrevious())
            {
                //qDebug() << "Looking at"<<seg.peekNext() << "Found new seq! Saved previous.";
                names.append(curName);
                seqs.append(curSeq);
                //[curSeq]=curName;
                curSeq.clear();
                curName = QString(seg.next()).remove(0,1);
            }
            else if (seg.peekNext()[0] == '>' && !seg.hasPrevious())
            {
                //qDebug() << "Looking at"<<seg.peekNext() << "Found first name!";
                curName = QString(seg.next()).remove(0,1);
            }
            else
            {
                //qDebug() << "Looking at"<<seg.peekNext() << "appending to seq!";
                curSeq.append(seg.next());
            }
        }
       // qDebug() << "Saved final seq!";
        names.append(curName);
        seqs.append(curSeq);
        //result[curSeq]=curName;
        //qDebug() << result;
        result.append(names);
        result.append(seqs);

        return result;
    }

    QString prettyPrintFastaSequence(QString name, QString seq, int lineLength)
    /// Returns a formatted Fasta sequence as a string. By default it splits the sequence into
    /// lines of length "lineLength".
    {
        QString result;
        QString seg;
        result.append(">").append(name).append("\n");
        while(seq.length()>lineLength)
        {
            seg = seq.first(lineLength); // This might be a little unsafe.
            seq.remove(seg);
            result.append(seg).append("\n");
        }
        result.append(seq).append("\n");
        return result;

    }

    QList<QChar> calculateIdentityToReference(QList<QChar> resList, int ref)
    {
        QList<QChar> consList;
        for(auto&& res: resList)
        {
            res == resList.at(ref) ? consList.append(res) : consList.append(res.toLower());
        }
        return consList;
    }

    QList<QChar> calculateConservation(QList<QChar> resList)
    /// Returns an integer value that equates to the ClustalX conservation category.
    /// See here: http://www.jalview.org/help/html/colourSchemes/clustal.html
    /// There are 9 categories. 0 is unconserved; 1 is if the residue is either AILMFWV or C,
    /// where >60% of the residues are WLVIMAFCHP; 2 is if the residue is K,R and the total is either
    {
        QList<QChar> consv;
        qreal len = static_cast<qreal>(resList.length());
        qreal phb = static_cast<qreal>(resList.count('F')+resList.count('H')+resList.count('I')+
                resList.count('L')+resList.count('M')+resList.count('P')+resList.count('V')+resList.count('W'))/len;
        qreal renq = static_cast<qreal>(resList.count('E')+resList.count('N')+resList.count('Q')+resList.count('R'))/len; // histidine
        qreal pol = static_cast<qreal>(resList.count('S')+resList.count('T')+resList.count('H')+resList.count('Q'))/len;
        qreal kr = static_cast<qreal>(resList.count('K')+resList.count('R'))/len;
        qreal qe = static_cast<qreal>(resList.count('Q')+resList.count('E'))/len;
        qreal ed =static_cast<qreal>(resList.count('E')+resList.count('D'))/len;
        qreal ts = static_cast<qreal>(resList.count('T')+resList.count('S'))/len;
        qreal a = static_cast<qreal>(resList.count('A'))/len;
        qreal c = static_cast<qreal>(resList.count('C'))/len;
        qreal d = static_cast<qreal>(resList.count('D'))/len;
        qreal e = static_cast<qreal>(resList.count('E'))/len;
        qreal f = static_cast<qreal>(resList.count('F'))/len;
        qreal g = static_cast<qreal>(resList.count('G'))/len;
        qreal h = static_cast<qreal>(resList.count('H'))/len;
        qreal i = static_cast<qreal>(resList.count('I'))/len;
        qreal k = static_cast<qreal>(resList.count('K'))/len;
        qreal l = static_cast<qreal>(resList.count('L'))/len;
        qreal m = static_cast<qreal>(resList.count('M'))/len;
        qreal n = static_cast<qreal>(resList.count('N'))/len;
        qreal p = static_cast<qreal>(resList.count('P'))/len;
        qreal q = static_cast<qreal>(resList.count('Q'))/len;
        qreal r = static_cast<qreal>(resList.count('R'))/len;
        qreal s = static_cast<qreal>(resList.count('S'))/len;
        qreal t = static_cast<qreal>(resList.count('T'))/len;
        qreal v = static_cast<qreal>(resList.count('V'))/len;
        qreal w = static_cast<qreal>(resList.count('W'))/len;
        qreal y = static_cast<qreal>(resList.count('Y'))/len;

        for(auto&& resi: resList)
            /// Based on Blosum62
            /// Extra residues: B,b,J,O,o,Z
        {
            if(resi == '-') consv.append(resi);
            else if(resi == 'A') {
                if(a>0.60) consv.append(resi);
                else if(phb > 0.8) consv.append('B'); // color it like a hydrophobe
                else consv.append(resi.toLower()); }
            else if(resi == 'C'){
                if(c>0.6) consv.append(resi);
                else consv.append(resi.toLower()); }
            else if(resi == 'D') (kr>0.8||ed>0.60||k>0.8||r>0.8||q>0.8) ? consv.append(resi): consv.append(resi.toLower()); // fix this to be more BLOSUM62-like
            else if(resi == 'E') (kr>0.8||qe>0.8||q>0.8||e>0.6||d>0.6||ed>0.6) ? consv.append(resi): consv.append(resi.toLower()); // fix this
            else if(resi == 'F') {
                if(f>0.60) consv.append(resi);
                else if(phb>0.8) consv.append('b'); // hydrophobe color
                else consv.append(resi.toLower()); }
            else if(resi == 'G') (g>0.60) ? consv.append(resi): consv.append(resi.toLower());
            else if(resi == 'H') {
                if(h>0.60) consv.append(resi);
                else if(y>0.80) consv.append(resi);   // aromatic still
                else if (renq >0.8) consv.append('J'); // color like it's polar
                else if (pol > 0.8) consv.append('J');
                else consv.append(resi.toLower()); }
            else if(QList<QChar>({'I','L','M','V'}).contains(resi)) (phb > 0.6)? consv.append(resi): consv.append(resi.toLower());
            else if(QList<QChar>({'K','R'}).contains(resi)) (kr > 0.6 || (q>0.80||h>0.80)) ? consv.append(resi): consv.append(resi.toLower());
            else if(resi == 'N') (n>0.60 || pol>0.8) ? consv.append(resi): consv.append(resi.toLower());
            else if(resi == 'Q') (kr>0.8 || qe>0.80 || q>0.60||e>0.80||pol>0.8) ? consv.append(resi): consv.append(resi.toLower());    // fix this to be more BLOSUM62-like?
            else if(resi == 'S') (s>0.6 || pol>0.8) ? consv.append(resi): consv.append(resi.toLower());
            else if(resi == 'T') {
                if(ts>0.8||(s>0.8||t>0.6)) consv.append(resi);
                else if(phb>0.8) consv.append('O'); // color like phobe
                else consv.append(resi.toLower()); }
            else if(resi == 'P') (p>0.6) ? consv.append(resi): consv.append(resi.toLower());
            else if(resi == 'Y') {
                if(y>0.6) consv.append(resi);
                else if(f>0.8) consv.append(resi);
                else if(phb>0.8) consv.append('o'); // color like hydrophobe
                else consv.append(resi.toLower()); }
            else if(resi == 'W') {
                if(w>0.6) consv.append(resi);
                else if(f>0.6) consv.append(resi);
                else if(phb>0.8) consv.append('Z'); // color like hydrophobe
                else consv.append(resi.toLower()); }
            else consv.append(resi.toLower());

        }
        //qDebug(lnoProc) << consv;
        return consv;
    }
}
