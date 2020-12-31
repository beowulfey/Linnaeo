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
    lookup['I'] = QString("<span style=\"background-color:#FFFFA6\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#FFFFA6\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#FFFFA6\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#FFFFA6\">V</span>");
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#93E6E3\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#93E6E3\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#93E6E3\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#93E6E3\">T</span>");
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#B699CC\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#B699CC\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#5CCC90\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#5CCC90\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#F2C230\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#F2C230\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#F2C230\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#F2C230\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#FFB0C1\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#D97D59\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#E6E6E6\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#6F7FBF\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    return lookup;
}

QHash<QChar, QString> Themes::gradientTheme()
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("<span style=\"background-color:#92A2E3\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#92A2E3\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#92A2E3\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#92A2E3\">V</span>");
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#ECEC93\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#ECEC93\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#ECEC93\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#ECEC93\">T</span>");
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#C6ECD7\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#C6ECD7\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#F2CC5A\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#F2CC5A\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#E05C8F\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#E05C8F\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#E05C8F\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#E05C8F\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#A8F0EE\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#D2722D\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#E6E6E6\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#AE7CD5\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    return lookup;
}

QHash<QChar, QString> Themes::newTheme()
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("<span style=\"background-color:#FFE666\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#FFE666\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#FFE666\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#FFE666\">V</span>");
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#B3E6C9\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#B3E6C9\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#B3E6C9\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#B3E6C9\">T</span>");
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#C2CBF0\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#C2CBF0\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#F5C73D\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#F5C73D\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#C39FDF\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#C39FDF\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#C39FDF\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#C39FDF\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#F2F2F2\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#DB7099\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#E5FFFE\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#D28D2D\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    return lookup;
}

QHash<QChar, QString> Themes::clustalXTheme()
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['A'] = QString("<span style=\"background-color:#197FE5\">A</span>");
    lookup['I'] = QString("<span style=\"background-color:#197FE5\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#197FE5\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#197FE5\">M</span>");
    lookup['F'] = QString("<span style=\"background-color:#197FE5\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#197FE5\">W</span>");
    lookup['V'] = QString("<span style=\"background-color:#197FE5\">V</span>");
    lookup['C'] = QString("<span style=\"background-color:#E57F7F\">C</span>");
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#19CC19\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#19CC19\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#19CC19\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#19CC19\">T</span>");
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#E53319\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#E53319\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#CC4CCC\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#CC4CCC\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#19B2B2\">H</span>");
    lookup['Y'] = QString("<span style=\"background-color:#19B2B2\">Y</span>");
    // Misc
    lookup['G'] = QString("<span style=\"background-color:#E5994C\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#CCCC00\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    return lookup;
}
