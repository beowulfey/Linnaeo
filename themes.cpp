#include "themes.h"

/// Theme designs
/// Adding a theme here requires updating two locations: the themeCombo selections
/// as well as the setTheme method in the SeqViewer

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

QHash<QChar, QString> Themes::neonTheme()
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("<span style=\"background-color:#DBDBDB\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#DBDBDB\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#DBDBDB\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#DBDBDB\">V</span>");
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#FFBF00\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#FFBF00\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#FFBF00\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#FFBF00\">T</span>");
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#00E6DE\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#00E6DE\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#C689F5\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#C689F5\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#3EF794\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#3EF794\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#3EF794\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#3EF794\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#FE8DA5\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#466CFF\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#F2F281\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#C4866E\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    return lookup;
}

QHash<QChar, QString> Themes::gradientTheme()
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("<span style=\"background-color:#007db7\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#007db7\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#007db7\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#007db7\">V</span>");
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#ff754a\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#ff754a\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#ff754a\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#ff754a\">T</span>");
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#cc69c0\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#cc69c0\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#587cca\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#587cca\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#ff9401\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#ff9401\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#ff9401\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#ff9401\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#f65ea2\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#ff6079\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#DEDEDE\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#9675ce\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    return lookup;
}
