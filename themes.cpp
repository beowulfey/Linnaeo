#include "themes.h"




QHash<QChar, QString> Themes::defaultTheme()
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("#97A4E8\">I</span>");
    lookup['L'] = QString("#97A4E8\">L</span>");
    lookup['M'] = QString("#97A4E8\">M</span>");
    lookup['V'] = QString("#97A4E8\">V</span>");
    // Polar
    lookup['N'] = QString("#BEF1AC\">N</span>");
    lookup['Q'] = QString("#BEF1AC\">Q</span>");
    lookup['S'] = QString("#BEF1AC\">S</span>");
    lookup['T'] = QString("#BEF1AC\">T</span>");
    // Positive
    lookup['K'] = QString("#DB8A8B\">K</span>");
    lookup['R'] = QString("#DB8A8B\">R</span>");
    // Negative
    lookup['D'] = QString("#E190E2\">D</span>");
    lookup['E'] = QString("#E190E2\">E</span>");
    // Aromatic
    lookup['H'] = QString("#A0EDD8\">H</span>");
    lookup['F'] = QString("#A0EDD8\">F</span>");
    lookup['W'] = QString("#A0EDD8\">W</span>");
    lookup['Y'] = QString("#A0EDD8\">Y</span>");
    // Misc
    lookup['A'] = QString("#F7EDEC\">A</span>");
    lookup['C'] = QString("#F4F2BA\">C</span>");
    lookup['G'] = QString("#EFEFEF\">G</span>");
    lookup['P'] = QString("#F6DECC\">P</span>");
    return lookup;
}
