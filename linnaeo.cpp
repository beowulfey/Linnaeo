#include "linnaeo.h"
#include "./ui_linnaeo.h"
#include "workspace.h"
#include "preferences.h"
#include <QProcess>
#include <QDir>
#include <spdlog/spdlog.h>
#include <iostream>


/// LINNAEO
/// Oh shit welcome to the bitchin' C++ version.

Linnaeo::Linnaeo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Linnaeo)
{
    ui->setupUi(this);
    ui->optionsPanel->hide();

    //QVector<qint64> procIds;
}
Linnaeo::~Linnaeo()
{
    delete ui;
}

// Slot connections for the main menu.
// FILE MENU SLOTS
void Linnaeo::on_actionNew_triggered()
/// New: Starts a new detached Linnaeo instance.
/// Almost perfect, except closing the first instance will close the connection to stdout.
{
    qint64* pid;
    QProcess::startDetached(QCoreApplication::applicationFilePath(),{},QDir::homePath(),pid);
    spdlog::info("Started proc at {}", *pid);
    //this->procIds.append(*pid);

}

// VIEW MENU SLOTS
void Linnaeo::on_actionShow_Viewer_Options_triggered(bool checked)
/// Show side panel of viewer.
{
    if(checked){
        ui->optionsPanel->show();
        spdlog::debug("Showing options panel");
    }else{
        ui->optionsPanel->hide();
        spdlog::debug("Hiding options panel");
    }
}

void Linnaeo::on_actionPreferences_triggered()
{
    Preferences *pref = new Preferences(this);
    pref->show();
}

void Linnaeo::on_actionQuit_triggered()
{
    //QVector<qint64>::const_iterator iter;
    //if(this->procIds.length()>0){
    //    for(iter=this->procIds.begin();iter != this->procIds.end(); iter++){
    //
    this->close();
}
