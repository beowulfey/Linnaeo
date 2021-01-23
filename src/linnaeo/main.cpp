#include "linnaeo.h"

#include <QApplication>

// NOTE: This application requires the TIFF plugin to export TIFF images.
// Make sure to compile the QTiff plugin (available in the QtImageFormats add-on) and
// drop it into the build directory plugins folder!

int main(int argc, char *argv[])

{
    qSetMessagePattern("%{category}.%{type}: %{message}");
    //QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\n"));// "*.proc.debug=true"));
    QString version = QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    QApplication a(argc, argv);
    Linnaeo w{};
    a.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    w.setWindowIcon(QIcon(":/icons/linnaeo.ico"));

    qInfo(lnoMain) <<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n                "
                               "Welcome to Linnaeo v."<<qPrintable(version)
                   <<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

    if(a.arguments().length()>1 && a.arguments().at(1).right(3) == "lno") w.openFromFile(a.arguments().at(1));
    w.show();
    return a.exec();
}
