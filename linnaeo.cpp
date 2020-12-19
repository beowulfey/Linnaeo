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
#include "folderitem.h"
#include <QPersistentModelIndex>

/// LINNAEO
/// Oh shit welcome to the bitchin' C++ version.

Linnaeo::Linnaeo(QWidget *parent): QMainWindow(parent), ui(new Ui::Linnaeo)
{
    ui->setupUi(this);
    ui->optionsPanel->hide();
    QStandardItem *seqRoot;
    QStandardItem *alignRoot;

    // Sequence TreeView setup
    this->seqModel = new QStandardItemModel(this);
    this->seqModel->setHorizontalHeaderLabels(QStringList("Sequences"));
    seqRoot = this->seqModel->invisibleRootItem();
    seqStartFolderItem = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("Uncategorized"));
    seqStartFolderItem->setData(true, FOLDER);
    seqRoot->appendRow(seqStartFolderItem);
    connect(ui->seqTreeView, &QTreeView::expanded, this, &Linnaeo::expand_seqTreeView_item);
    connect(ui->seqTreeView, &QTreeView::collapsed, this, &Linnaeo::collapse_seqTreeView_item);
    // Connect tool buttons
    //ui->quickAlign
    ui->addSequenceButton->setDefaultAction(ui->actionAdd_Sequence);
    ui->importSequenceButton->setDefaultAction(ui->actionSequence_from_file);
    ui->addSequenceFolderButton->setDefaultAction(ui->actionAdd_Folder_to_Sequence_Panel);
    //ui->editSequenceButton
    ui->exportSequenceButton->setDefaultAction(ui->actionExportSequence);
    ui->deleteSequenceButton->setDefaultAction(ui->actionDelete_Selected_Sequences);


    alignModel = new QStandardItemModel(this);
    alignModel->setHorizontalHeaderLabels(QStringList("Alignments"));
    alignRoot = alignModel->invisibleRootItem();
    alignStartFolderItem = new QStandardItem(QString("Uncategorized"));
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
    spdlog::info("Started new window with procID {}", *pid);
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
    spdlog::debug("Collapsed SeqView tree at position {}", index.row());
    this->seqModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}
void Linnaeo::expand_alignTreeView_item(const QModelIndex &index)
{
    spdlog::debug("Expanded AlignView tree at position {}", index.row());
    this->alignModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder-open.svg"),Qt::DecorationRole);
}

void Linnaeo::collapse_alignTreeView_item(const QModelIndex &index)
{
    spdlog::debug("Collapsed AlignView tree at position {}", index.row());
    this->alignModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}

void Linnaeo::on_actionAdd_Sequence_triggered()
/// Add a new sequence to the sequence tree. Opens up the "New Sequence" dialog.
/// By default, adds to the permanent "uncategorized" folder (hidden if empty).
/// Otherwise, it will add to whatever folder is selected.
{
    QList<QModelIndex>indexes = ui->seqTreeView->selectionModel()->selectedIndexes();
    QStandardItem *newSeq = new QStandardItem(QString("Default"));
    newSeq->setData(false,FOLDER);
    newSeq->setDropEnabled(false);
    QStandardItem *item;
    bool found = false;
    for(const QModelIndex& index : indexes)
    {
        // Check each selected item (if any) to see if it is a folder. Add it to the first
        // folder it finds, otherwise add it to the "uncategorized" folder.
        item = this->seqModel->itemFromIndex(index);
        if (item->data(FOLDER).toBool())
        {
            item->appendRow(newSeq);
            ui->seqTreeView->expand(index);
            found = true;
            break;
        }
    }
    if (!found)
    {
        this->seqStartFolderItem->appendRow(newSeq);
        ui->seqTreeView->expand(this->seqStartFolderItem->index());
    }
    //TODO: Launch New Seq Panel here. Will override placement of new sequence anyway.

}

void Linnaeo::on_actionDelete_Selected_Sequences_triggered()
{
    QList<QModelIndex> indexes = ui->seqTreeView->selectionModel()->selectedIndexes();
    QList<QPersistentModelIndex> pindexes;

    if(indexes.size() >= 1)
    {
        foreach (const QModelIndex &index, indexes)
        {
            if(index != this->seqStartFolderItem->index())
            {
                pindexes << QPersistentModelIndex(index);
            }
        }
        foreach (const QPersistentModelIndex &i, pindexes)
            this->seqModel->removeRow(i.row(), i.parent());
    }
}

void Linnaeo::on_actionAdd_Folder_to_Sequence_Panel_triggered()
/// Adds a folder to the sequence panel. Without having anything selected, it will insert the
/// new folder above the "Uncategorized" folder. If things are selected, it will add to the first folder
/// it finds; otherwise, it will add to the parent of the selected object.
{
    QStandardItem *newFolder = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("New Folder"));
    newFolder->setData(true,FOLDER);
    QList<QModelIndex> indexes = ui->seqTreeView->selectionModel()->selectedIndexes();
    if (indexes.size() == 0)// || this->seqModel->itemFromIndex(indexes.at(0))->parent() == NULL)
    {
        // Nothing selected: add new top level directory.
        this->seqModel->invisibleRootItem()->insertRow(0, newFolder);
        ui->seqTreeView->edit(newFolder->index());
    }
    else
    {
        QStandardItem *item;
        bool found = false;
        for(const QModelIndex& index : indexes)
        {
            // Check each selected item (if any) to see if it is a folder. Add it to the first
            // folder it finds, otherwise add it to the "uncategorized" folder.
            item = this->seqModel->itemFromIndex(index);
            if (item->data(FOLDER).toBool())
            {
                item->appendRow(newFolder);
                ui->seqTreeView->expand(index);
                found = true;
                break;
            }
        }
        if (!found)
        {
            if(this->seqModel->itemFromIndex(indexes.at(0).parent()) != NULL)
            {
                this->seqModel->itemFromIndex(indexes.at(0).parent())->appendRow(newFolder);
            }
            else
            {
                this->seqModel->invisibleRootItem()->insertRow(0,newFolder);
            }
        }



        //{
        // Add directory within parent
        //if
        //this->seqModel->itemFromIndex(indexes.at(0).parent())->appendRow(newFolder);
        //ui->seqTreeView->edit(newFolder->index());
    }

}
