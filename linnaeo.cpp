#include "linnaeo.h"
#include "./ui_linnaeo.h"
#include "seqeditor.h"
#include "preferences.h"
#include "searchuniprot.h"
#include <QProcess>
#include <QDir>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileIconProvider>
#include <QPersistentModelIndex>
#include <spdlog/spdlog.h>
#include <iostream>


Linnaeo::Linnaeo(QWidget *parent): QMainWindow(parent), ui(new Ui::Linnaeo)
{
    ui->setupUi(this);
    ui->optionsPanel->hide();
    QStandardItem *seqRoot;
    QStandardItem *alignRoot;

    // Sequence TreeView setup
    this->seqModel = new QStandardItemModel(this);
    //this->seqModel->setHorizontalHeaderLabels(QStringList("Sequences"));
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

    this->alignModel = new QStandardItemModel(this);
    //this->alignModel->setHorizontalHeaderLabels(QStringList("Alignments"));
    alignRoot = this->alignModel->invisibleRootItem();
    alignStartFolderItem = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("Uncategorized"));
    alignStartFolderItem->setData(true, FOLDER);
    alignRoot->appendRow(alignStartFolderItem);
    connect(ui->alignTreeView, &QTreeView::expanded, this, &Linnaeo::expand_alignTreeView_item);
    connect(ui->alignTreeView, &QTreeView::collapsed, this, &Linnaeo::collapse_alignTreeView_item);
    // Connect tool buttons
    //ui->quickAlign
    //ui->addAlignmentButton->setDefaultAction(ui->actionAdd_Alignment);
    ui->importAlignmentButton->setDefaultAction(ui->actionAlignment_from_file);
    ui->addAlignmentFolderButton->setDefaultAction(ui->actionAdd_Alignment_Folder);
    //ui->editAlignmentButton
    ui->exportAlignmentButton->setDefaultAction(ui->actionExportAlignment);
    ui->deleteAlignmentButton->setDefaultAction(ui->actionDelete_Selected_Alignments);

    /*alignModel = new QStandardItemModel(this);
    alignModel->setHorizontalHeaderLabels(QStringList("Alignments"));
    alignRoot = alignModel->invisibleRootItem();
    alignStartFolderItem = new QStandardItem(QString("Uncategorized"));
    alignStartFolderItem->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
    alignRoot->appendRow(alignStartFolderItem);
    connect(ui->alignTreeView, &QTreeView::expanded, this, &Linnaeo::expand_alignTreeView_item);
    connect(ui->alignTreeView, &QTreeView::collapsed, this, &Linnaeo::collapse_alignTreeView_item);
    */

    ui->seqTreeView->setModel(seqModel);
    ui->alignTreeView->setModel(alignModel);

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
    Linnaeo *newLinnaeo = new Linnaeo();
    newLinnaeo->show();

    //qint64* pid;
    //QProcess::startDetached(QCoreApplication::applicationFilePath(),{},QDir::homePath(),pid);
    //spdlog::info("Started new window with procID {}", *pid);
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



void Linnaeo::on_actionAdd_Sequence_triggered()
/// Add a new sequence to the sequence tree. Opens up the "New Sequence" dialog.
/// By default, adds to the permanent "uncategorized" folder (hidden if empty).
/// Otherwise, it will add to whatever folder is selected.
{
    SeqEditor seqEdit(this);

    if (seqEdit.exec() == QDialog::Accepted) {
        QString name, seq;
        name = seqEdit.submittedName();
        seq = seqEdit.submittedSequence();
        if(name != "" && seq != "")
        {
            QList<QModelIndex>indexes = ui->seqTreeView->selectionModel()->selectedIndexes();
            QStandardItem *newSeq = new QStandardItem(name);
            newSeq->setData(false,FOLDER);
            newSeq->setData(seq,SEQUENCE);
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
            // TODO: Extract this step through a formatting function!
            ui->seqBrowser->setText(newSeq->data(SEQUENCE).toString());
        }
        else
        {
            spdlog::warn("At least one of Name or Sequence field was left empty; please try again!");
            // TODO: Also give status alert here.
        }
    }
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
    }

}

void Linnaeo::on_actionMake_Alignment_triggered()
{

}

void Linnaeo::on_actionAdd_Alignment_Folder_triggered()
/// Identical behavior as for the Sequence equivalent.
{
    QStandardItem *newFolder = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("New Folder"));
    newFolder->setData(true,FOLDER);
    QList<QModelIndex> indexes = ui->alignTreeView->selectionModel()->selectedIndexes();
    if (indexes.size() == 0)
    {
        // Nothing selected: add new top level directory.
        this->alignModel->invisibleRootItem()->insertRow(0, newFolder);
        ui->alignTreeView->edit(newFolder->index());
    }
    else
    {
        QStandardItem *item;
        bool found = false;
        for(const QModelIndex& index : indexes)
        {
            // Check each selected item (if any) to see if it is a folder. Add it to the first
            // folder it finds, otherwise add it to the "uncategorized" folder.
            item = this->alignModel->itemFromIndex(index);
            if (item->data(FOLDER).toBool())
            {
                item->appendRow(newFolder);
                ui->alignTreeView->expand(index);
                found = true;
                break;
            }
        }
        if (!found)
        {
            if(this->alignModel->itemFromIndex(indexes.at(0).parent()) != NULL)
            {
                this->alignModel->itemFromIndex(indexes.at(0).parent())->appendRow(newFolder);
            }
            else
            {
                this->alignModel->invisibleRootItem()->insertRow(0,newFolder);
            }
        }
    }
}

void Linnaeo::on_actionDelete_Selected_Alignments_triggered()
{
    QList<QModelIndex> indexes = ui->alignTreeView->selectionModel()->selectedIndexes();
    QList<QPersistentModelIndex> pindexes;

    if(indexes.size() >= 1)
    {
        foreach (const QModelIndex &index, indexes)
        {
            if(index != this->alignStartFolderItem->index())
            {
                pindexes << QPersistentModelIndex(index);
            }
        }
        foreach (const QPersistentModelIndex &i, pindexes)
            this->alignModel->removeRow(i.row(), i.parent());
    }
}

void Linnaeo::on_actionEdit_Sequence_triggered()
{

}

// OTHER SLOTS
void Linnaeo::expand_seqTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Expanded SeqView tree at position {}", index.row());
    this->seqModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder-open.svg"),Qt::DecorationRole);
}

void Linnaeo::collapse_seqTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Collapsed SeqView tree at position {}", index.row());
    this->seqModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}
void Linnaeo::expand_alignTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Expanded AlignView tree at position {}", index.row());
    this->alignModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder-open.svg"),Qt::DecorationRole);
}

void Linnaeo::collapse_alignTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Collapsed AlignView tree at position {}", index.row());
    this->alignModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}

void Linnaeo::on_actionGet_Online_Sequence_triggered()
{
    SearchUniprot search(this);
    search.exec();
    //if (search.exec() == QDialog::Accepted) {)

}
