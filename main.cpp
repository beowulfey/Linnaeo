#include "linnaeo.h"
#include <QApplication>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
//#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
    //spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    //spdlog::set_pattern("[%H:%M:%S] %^[%l] [thread %t] %v%$");
    QApplication a(argc, argv);
    Linnaeo w{};
    a.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    w.setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    //spdlog::info("LINNAEO STARTUP COMPLETE");
    w.show();

    return a.exec();
}
