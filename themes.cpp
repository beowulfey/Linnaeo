#include "themes.h"



QHash<QChar, QString> Themes::debugTheme()
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("<span style=\"background-color:#FFFFFF\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#FFFFFF\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#FFFFFF\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#FFFFFF\">V</span>");
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#FFFFFF\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#FFFFFF\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#FFFFFF\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#FFFFFF\">T</span>");
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#FFFFFF\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#FFFFFF\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#FFFFFF\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#FFFFFF\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#FFFFFF\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#FFFFFF\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#FFFFFF\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#FFFFFF\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#FFFFFF\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#FFFFFF\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#FFFFFF\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#FFFFFF\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    return lookup;
}


QHash<QChar, QString> Themes::defaultTheme()
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("<span style=\"background-color:#97A4E8\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#97A4E8\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#97A4E8\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#97A4E8\">V</span>");
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#BEF1AC\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#BEF1AC\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#BEF1AC\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#BEF1AC\">T</span>");
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#DB8A8B\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#DB8A8B\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#E190E2\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#E190E2\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#A0EDD8\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#A0EDD8\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#A0EDD8\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#A0EDD8\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#F7EDEC\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#F4F2BA\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#EFEFEF\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#F6DECC\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    return lookup;
}
