#include "linnaeo.h"

#include <QApplication>


int main(int argc, char *argv[])

{
    qSetMessagePattern("%{category}.%{type}: %{message}");
    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false"));
    QString version = QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    QApplication a(argc, argv);
    Linnaeo w{};
    a.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    w.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    qInfo(lnoMain) << a.arguments();

    qInfo(lnoMain) << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\t\tWelcome to LINNAEO\t\t\n" << "\t\tLoaded ver."<<qPrintable(version)<<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

    return a.exec();
}
