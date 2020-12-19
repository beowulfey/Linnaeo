#include "linnaeo.h"
#include "./ui_linnaeo.h"
#include "preferences.h"
#include <QProcess>
#include <QDir>
#include <spdlog/spdlog.h>
#include <iostream>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileIconProvider>


/// LINNAEO
/// Oh shit welcome to the bitchin' C++ version.

Linnaeo::Linnaeo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Linnaeo)
{
    ui->setupUi(this);
    ui->optionsPanel->hide();

    // TreeViews setup
    seqModel = new QStandardItemModel(this);
    this->seqModel->setHorizontalHeaderLabels(QStringList("Sequences"));
    QStandardItem *seqRoot = seqModel->invisibleRootItem();
    QStandardItem *seqStartFolderItem = new QStandardItem(QString("Uncategorized"));
    seqStartFolderItem->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
    seqRoot->appendRow(seqStartFolderItem);
    seqStartFolderItem->appendRow(new QStandardItem(QString("Testing")));
    connect(ui->seqTreeView, &QTreeView::expanded, this, &Linnaeo::expand_seqTreeView_item);
    connect(ui->seqTreeView, &QTreeView::collapsed, this, &Linnaeo::collapse_seqTreeView_item);

    alignModel = new QStandardItemModel(this);
    alignModel->setHorizontalHeaderLabels(QStringList("Alignments"));
    QStandardItem *alignRoot = alignModel->invisibleRootItem();
    QStandardItem *alignStartFolderItem = new QStandardItem(QString("Uncategorized"));
    alignStartFolderItem->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
    alignRoot->appendRow(alignStartFolderItem);
    connect(ui->alignTreeView, &QTreeView::expanded, this, &Linnaeo::expand_alignTreeView_item);
    connect(ui->alignTreeView, &QTreeView::collapsed, this, &Linnaeo::collapse_alignTreeView_item);

    ui->seqTreeView->setModel(seqModel);
    ui->alignTreeView->setModel(alignModel);

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

// OTHER SLOTS
void Linnaeo::expand_seqTreeView_item(const QModelIndex &index)
{
    spdlog::debug("Expanded SeqView tree at position {}", index.row());
    this->seqModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder-open.svg"),Qt::DecorationRole);
}

void Linnaeo::collapse_seqTreeView_item(const QModelIndex &index)
{
    spdlog::debug("Expanded SeqView tree at position {}", index.row());
    this->seqModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}
void Linnaeo::expand_alignTreeView_item(const QModelIndex &index)
{
    spdlog::debug("Expanded AlignView tree at position {}", index.row());
    this->alignModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder-open.svg"),Qt::DecorationRole);
}

void Linnaeo::collapse_alignTreeView_item(const QModelIndex &index)
{
    spdlog::debug("Expanded AlignView tree at position {}", index.row());
    this->alignModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}
