#ifndef THEMES_H
#define THEMES_H

#include <QHash>

class Themes
{
public:
    static QHash<QChar, QString> defaultTheme();
    static QHash<QChar, QString> debugTheme();
    static QHash<QChar, QString> neonTheme();
    static QHash<QChar, QString> gradientTheme();
};

#endif // THEMES_H
