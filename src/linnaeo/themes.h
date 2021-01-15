#ifndef THEMES_H
#define THEMES_H

#include <QHash>

class Themes
{
public:
    static QHash<QChar, QString> debugTheme();
    static QHash<QChar, QString> defaultTheme();
    static QHash<QChar, QString> clustalXTheme();
    static QHash<QChar, QString> colorsafeTheme();
    static QHash<QChar, QString> hydrophobicityTheme();
    /*
    static QHash<QChar, QString> conservationTheme();
    static QHash<QChar, QString> neonTheme();
    static QHash<QChar, QString> gradientTheme();
    static QHash<QChar, QString> newTheme();
    */
};

#endif // THEMES_H
