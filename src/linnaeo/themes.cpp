#include "themes.h"

/// Theme designs
/// Adding a theme here requires updating two locations: the themeCombo selections
/// as well as the setTheme method in the SeqViewer
///
/// TO ADD:
/// Percent identity (single color)
/// Hydrophobicity (recreate from PyLinnaeo)
/// Helix Propensity (purple to green)
/// Some variant of my conservation mode?
/// Conservation highlighting (implement threshold slider?)
///


QHash<QChar, QString> Themes::debugTheme()
/// Currently set to red-green color blind of default.
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("<span style=\"background-color:#9B9AD3\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#9B9AD3\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#9B9AD3\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#9B9AD3\">V</span>");
    lookup['B'] = QString("<span style=\"background-color:#9B9AD3\">A</span>"); //
    lookup['b'] = QString("<span style=\"background-color:#9B9AD3\">F</span>"); //
    lookup['O'] = QString("<span style=\"background-color:#9B9AD3\">T</span>"); //
    lookup['o'] = QString("<span style=\"background-color:#9B9AD3\">Y</span>");
    lookup['Z'] = QString("<span style=\"background-color:#9B9AD3\">W</span>"); //
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#B3B7B8\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#B3B7B8\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#B3B7B8\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#B3B7B8\">T</span>");
    lookup['J'] = QString("<span style=\"background-color:#B3B7B8\">H</span>"); //
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#F1F4C9\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#F1F4C9\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#E2E572\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#E2E572\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#DDDEFB\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#DDDEFB\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#DDDEFB\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#DDDEFB\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#DBD8CE\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#BEB9DB\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#E0E0E0\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#E9EDC8\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    // not conserved!
    lookup['a'] = QString("<span style=\"background-color:#FFFFFF\">A</span>");
    lookup['i'] = QString("<span style=\"background-color:#FFFFFF\">I</span>");
    lookup['l'] = QString("<span style=\"background-color:#FFFFFF\">L</span>");
    lookup['m'] = QString("<span style=\"background-color:#FFFFFF\">M</span>");
    lookup['f'] = QString("<span style=\"background-color:#FFFFFF\">F</span>");
    lookup['w'] = QString("<span style=\"background-color:#FFFFFF\">W</span>");
    lookup['v'] = QString("<span style=\"background-color:#FFFFFF\">V</span>");
    lookup['c'] = QString("<span style=\"background-color:#FFFFFF\">C</span>");

    lookup['n'] = QString("<span style=\"background-color:#FFFFFF\">N</span>");
    lookup['q'] = QString("<span style=\"background-color:#FFFFFF\">Q</span>");
    lookup['s'] = QString("<span style=\"background-color:#FFFFFF\">S</span>");
    lookup['t'] = QString("<span style=\"background-color:#FFFFFF\">T</span>");

    lookup['k'] = QString("<span style=\"background-color:#FFFFFF\">K</span>");
    lookup['r'] = QString("<span style=\"background-color:#FFFFFF\">R</span>");

    lookup['d'] = QString("<span style=\"background-color:#FFFFFF\">D</span>");
    lookup['e'] = QString("<span style=\"background-color:#FFFFFF\">E</span>");

    lookup['h'] = QString("<span style=\"background-color:#FFFFFF\">H</span>");
    lookup['y'] = QString("<span style=\"background-color:#FFFFFF\">Y</span>");

    lookup['g'] = QString("<span style=\"background-color:#FFFFFF\">G</span>");
    lookup['p'] = QString("<span style=\"background-color:#FFFFFF\">P</span>");
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
    lookup['B'] = QString("<span style=\"background-color:#97A4E8\">A</span>"); //
    lookup['b'] = QString("<span style=\"background-color:#97A4E8\">F</span>"); //
    lookup['O'] = QString("<span style=\"background-color:#97A4E8\">T</span>"); //
    lookup['o'] = QString("<span style=\"background-color:#97A4E8\">Y</span>"); //
    lookup['Z'] = QString("<span style=\"background-color:#97A4E8\">W</span>"); //
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#BEF1AC\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#BEF1AC\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#BEF1AC\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#BEF1AC\">T</span>");
    lookup['J'] = QString("<span style=\"background-color:#97A4E8\">H</span>"); //
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
    lookup['A'] = QString("<span style=\"background-color:#F1EBD5\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#F2F0B5\">C</span>"); //F4F2BA
    lookup['G'] = QString("<span style=\"background-color:#E0E0E0\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#F4D5BE\">P</span>"); //F6DECC F0CAAD
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    // not conserved!
    lookup['a'] = QString("<span style=\"background-color:#FFFFFF\">A</span>");
    lookup['i'] = QString("<span style=\"background-color:#FFFFFF\">I</span>");
    lookup['l'] = QString("<span style=\"background-color:#FFFFFF\">L</span>");
    lookup['m'] = QString("<span style=\"background-color:#FFFFFF\">M</span>");
    lookup['f'] = QString("<span style=\"background-color:#FFFFFF\">F</span>");
    lookup['w'] = QString("<span style=\"background-color:#FFFFFF\">W</span>");
    lookup['v'] = QString("<span style=\"background-color:#FFFFFF\">V</span>");
    lookup['c'] = QString("<span style=\"background-color:#FFFFFF\">C</span>");

    lookup['n'] = QString("<span style=\"background-color:#FFFFFF\">N</span>");
    lookup['q'] = QString("<span style=\"background-color:#FFFFFF\">Q</span>");
    lookup['s'] = QString("<span style=\"background-color:#FFFFFF\">S</span>");
    lookup['t'] = QString("<span style=\"background-color:#FFFFFF\">T</span>");

    lookup['k'] = QString("<span style=\"background-color:#FFFFFF\">K</span>");
    lookup['r'] = QString("<span style=\"background-color:#FFFFFF\">R</span>");

    lookup['d'] = QString("<span style=\"background-color:#FFFFFF\">D</span>");
    lookup['e'] = QString("<span style=\"background-color:#FFFFFF\">E</span>");

    lookup['h'] = QString("<span style=\"background-color:#FFFFFF\">H</span>");
    lookup['y'] = QString("<span style=\"background-color:#FFFFFF\">Y</span>");

    lookup['g'] = QString("<span style=\"background-color:#FFFFFF\">G</span>");
    lookup['p'] = QString("<span style=\"background-color:#FFFFFF\">P</span>");
    return lookup;
}

QHash<QChar, QString> Themes::colorsafeTheme()
/// Hopefully looks okay for red-green colorblind
{
    QHash<QChar, QString> lookup;
    // Hydrophobic
    lookup['I'] = QString("<span style=\"background-color:#97A4E8\">I</span>");
    lookup['L'] = QString("<span style=\"background-color:#97A4E8\">L</span>");
    lookup['M'] = QString("<span style=\"background-color:#97A4E8\">M</span>");
    lookup['V'] = QString("<span style=\"background-color:#97A4E8\">V</span>");
    lookup['B'] = QString("<span style=\"background-color:#97A4E8\">A</span>"); //
    lookup['b'] = QString("<span style=\"background-color:#97A4E8\">F</span>"); //
    lookup['O'] = QString("<span style=\"background-color:#97A4E8\">T</span>"); //
    lookup['o'] = QString("<span style=\"background-color:#97A4E8\">Y</span>");
    lookup['Z'] = QString("<span style=\"background-color:#97A4E8\">W</span>"); //
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#C892C9\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#C892C9\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#C892C9\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#C892C9\">T</span>");
    lookup['J'] = QString("<span style=\"background-color:#C892C9\">H</span>"); //
    // Positive
    lookup['K'] = QString("<span style=\"background-color:#FFDCC2\">K</span>");
    lookup['R'] = QString("<span style=\"background-color:#FFDCC2\">R</span>");
    // Negative
    lookup['D'] = QString("<span style=\"background-color:#F0CD4C\">D</span>");
    lookup['E'] = QString("<span style=\"background-color:#F0CD4C\">E</span>");
    // Aromatic
    lookup['H'] = QString("<span style=\"background-color:#D1EFFF\">H</span>");
    lookup['F'] = QString("<span style=\"background-color:#D1EFFF\">F</span>");
    lookup['W'] = QString("<span style=\"background-color:#D1EFFF\">W</span>");
    lookup['Y'] = QString("<span style=\"background-color:#D1EFFF\">Y</span>");
    // Misc
    lookup['A'] = QString("<span style=\"background-color:#CCF4BE\">A</span>");
    lookup['C'] = QString("<span style=\"background-color:#A6E8D6\">C</span>");
    lookup['G'] = QString("<span style=\"background-color:#E0E0E0\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#FEC8C8\">P</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    // not conserved!
    lookup['a'] = QString("<span style=\"background-color:#FFFFFF\">A</span>");
    lookup['i'] = QString("<span style=\"background-color:#FFFFFF\">I</span>");
    lookup['l'] = QString("<span style=\"background-color:#FFFFFF\">L</span>");
    lookup['m'] = QString("<span style=\"background-color:#FFFFFF\">M</span>");
    lookup['f'] = QString("<span style=\"background-color:#FFFFFF\">F</span>");
    lookup['w'] = QString("<span style=\"background-color:#FFFFFF\">W</span>");
    lookup['v'] = QString("<span style=\"background-color:#FFFFFF\">V</span>");
    lookup['c'] = QString("<span style=\"background-color:#FFFFFF\">C</span>");

    lookup['n'] = QString("<span style=\"background-color:#FFFFFF\">N</span>");
    lookup['q'] = QString("<span style=\"background-color:#FFFFFF\">Q</span>");
    lookup['s'] = QString("<span style=\"background-color:#FFFFFF\">S</span>");
    lookup['t'] = QString("<span style=\"background-color:#FFFFFF\">T</span>");

    lookup['k'] = QString("<span style=\"background-color:#FFFFFF\">K</span>");
    lookup['r'] = QString("<span style=\"background-color:#FFFFFF\">R</span>");

    lookup['d'] = QString("<span style=\"background-color:#FFFFFF\">D</span>");
    lookup['e'] = QString("<span style=\"background-color:#FFFFFF\">E</span>");

    lookup['h'] = QString("<span style=\"background-color:#FFFFFF\">H</span>");
    lookup['y'] = QString("<span style=\"background-color:#FFFFFF\">Y</span>");

    lookup['g'] = QString("<span style=\"background-color:#FFFFFF\">G</span>");
    lookup['p'] = QString("<span style=\"background-color:#FFFFFF\">P</span>");
    return lookup;
}

QHash<QChar, QString> Themes::clustalXTheme()
//ClustalX colors
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
    lookup['B'] = QString("<span style=\"background-color:#197FE5\">A</span>"); //
    lookup['b'] = QString("<span style=\"background-color:#197FE5\">F</span>"); //
    lookup['O'] = QString("<span style=\"background-color:#197FE5\">T</span>"); //
    lookup['o'] = QString("<span style=\"background-color:#197FE5\">Y</span>"); //
    lookup['Z'] = QString("<span style=\"background-color:#197FE5\">W</span>"); //
    // Polar
    lookup['N'] = QString("<span style=\"background-color:#19CC19\">N</span>");
    lookup['Q'] = QString("<span style=\"background-color:#19CC19\">Q</span>");
    lookup['S'] = QString("<span style=\"background-color:#19CC19\">S</span>");
    lookup['T'] = QString("<span style=\"background-color:#19CC19\">T</span>");
    lookup['J'] = QString("<span style=\"background-color:#19CC19\">H</span>"); //
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
    lookup['G'] = QString("<span style=\"background-color:#E0E0E0\">G</span>");
    lookup['P'] = QString("<span style=\"background-color:#CCCC00\">P</span>");
    lookup['C'] = QString("<span style=\"background-color:#E57F7F\">C</span>");
    lookup['-'] = QString("<span style=\"background-color:#FFFFFF\">-</span>");
    // not conserved!
    lookup['a'] = QString("<span style=\"background-color:#FFFFFF\">A</span>");
    lookup['i'] = QString("<span style=\"background-color:#FFFFFF\">I</span>");
    lookup['l'] = QString("<span style=\"background-color:#FFFFFF\">L</span>");
    lookup['m'] = QString("<span style=\"background-color:#FFFFFF\">M</span>");
    lookup['f'] = QString("<span style=\"background-color:#FFFFFF\">F</span>");
    lookup['w'] = QString("<span style=\"background-color:#FFFFFF\">W</span>");
    lookup['v'] = QString("<span style=\"background-color:#FFFFFF\">V</span>");
    lookup['c'] = QString("<span style=\"background-color:#FFFFFF\">C</span>");

    lookup['n'] = QString("<span style=\"background-color:#FFFFFF\">N</span>");
    lookup['q'] = QString("<span style=\"background-color:#FFFFFF\">Q</span>");
    lookup['s'] = QString("<span style=\"background-color:#FFFFFF\">S</span>");
    lookup['t'] = QString("<span style=\"background-color:#FFFFFF\">T</span>");

    lookup['k'] = QString("<span style=\"background-color:#FFFFFF\">K</span>");
    lookup['r'] = QString("<span style=\"background-color:#FFFFFF\">R</span>");

    lookup['d'] = QString("<span style=\"background-color:#FFFFFF\">D</span>");
    lookup['e'] = QString("<span style=\"background-color:#FFFFFF\">E</span>");

    lookup['h'] = QString("<span style=\"background-color:#FFFFFF\">H</span>");
    lookup['y'] = QString("<span style=\"background-color:#FFFFFF\">Y</span>");

    lookup['g'] = QString("<span style=\"background-color:#FFFFFF\">G</span>");
    lookup['p'] = QString("<span style=\"background-color:#FFFFFF\">P</span>");

    return lookup;
}

/*
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
    lookup['G'] = QString("<span style=\"background-color:#E0E0E0\">G</span>");
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
*/
