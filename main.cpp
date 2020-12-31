#include "linnaeo.h"
#include <QApplication>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
//#include <spdlog/spdlog.h>


int main(int argc, char *argv[])

{

    QString version = QString("%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    //spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    //spdlog::set_pattern("[%H:%M:%S] %^[%l] [thread %t] %v%$");
    QApplication a(argc, argv);
    Linnaeo w{};
    a.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    w.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    //spdlog::info("LINNAEO STARTUP COMPLETE");
    w.show();
    qDebug() << "Startup complete: version:" << version;

    return a.exec();
}
