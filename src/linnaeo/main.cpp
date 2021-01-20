#include "linnaeo.h"
#include "palette.h"

#include <QApplication>
#include <QStyle>


int main(int argc, char *argv[])

{
    bool darkMode = true;
    qSetMessagePattern("%{category}.%{type}: %{message}");
    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\n"));// "*.proc.debug=true"));
    QString version = QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    QApplication a(argc, argv);
    Linnaeo w{};
    a.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    w.setWindowIcon(QIcon(":/icons/linnaeo.ico"));

    qInfo(lnoMain) <<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n                "
                               "Welcome to Linnaeo v."<<qPrintable(version)
                   <<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

    if(a.arguments().length()>1 && a.arguments().at(1).right(3) == "lno") w.openFromFile(a.arguments().at(1));

    qApp->setPalette(a.style()->standardPalette());
    //if(darkMode)
   // {
     //   QPalette darkPalette = Palette::getDarkPalette();
     //   qApp->setPalette(darkPalette);
     //   //qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    //}
    w.show();
    return a.exec();
}
