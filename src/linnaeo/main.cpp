#include "linnaeo.h"
#include "palette.h"

#include <QApplication>
#include <QStyle>
#include <QStyleFactory>


int main(int argc, char *argv[])

{
    //bool darkMode = true;
    qSetMessagePattern("%{category}.%{type}: %{message}");
    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false\n"));// "*.proc.debug=true"));
    QString version = QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication::setPalette(QApplication::style()->standardPalette());
    //QApplication::setFont(font);
    QApplication a(argc, argv);
    Linnaeo w{};
    QFont font = QFont("Consolas");
    //font.setPointSizeF(10.0);
#ifdef Q_OS_MACOS
    qInfo() << "ON A MAC";
    a.setFont(font);
    w.setFont(font);
    //w.setStyleSheet("QMainWindow{font-size:large}");
#endif
    a.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    w.setWindowIcon(QIcon(":/icons/linnaeo.ico"));

    qInfo(lnoMain) <<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n                "
                               "Welcome to Linnaeo v."<<qPrintable(version)
                   <<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";

    if(a.arguments().length()>1 && a.arguments().at(1).right(3) == "lno") w.openFromFile(a.arguments().at(1));


    //if(darkMode)
   // {
     //   QPalette darkPalette = Palette::getDarkPalette();
     //   qApp->setPalette(darkPalette);
     //   //qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    //}
    w.show();
    return a.exec();
}
