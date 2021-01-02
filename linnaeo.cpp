#include "linnaeo.h"
#include "./ui_linnaeo.h"
#include "seqeditor.h"
#include "preferences.h"
#include "searchuniprot.h"
#include "alignworker.h"
#include "sequence.h"
#include <QDir>
#include <QStandardPaths>
#include <QFileDialog>
#include <QPersistentModelIndex>
#include <QScrollBar>
#include <QFontDatabase>
#include <QClipboard>


Linnaeo::Linnaeo(QWidget *parent): QMainWindow(parent), ui(new Ui::Linnaeo)
    /// The main Linnaeo constructor. Setups the UI using default settings. Builds
    /// the initial treeViews. Connects all slots.
{   ui->setupUi(this);
    QStandardItem *seqRoot;
    QStandardItem *alignRoot;

    // Set up Viewer panel
    QFontDatabase::addApplicationFont(":/fonts/Noto-Custom.ttf");
    defaultFont = QFont("Noto Custom", 10, 1);
    ui->namesEdit->setFont(defaultFont);
    ui->seqViewer->setFont(defaultFont);
    ui->rulerEdit->setFont(defaultFont);
    connect(ui->seqViewer, &SeqViewer::updatedNamesAndRuler, this, &Linnaeo::updateNamesAndRuler);
    connect(ui->seqViewer->verticalScrollBar(), &QScrollBar::valueChanged, ui->namesEdit->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->namesEdit->verticalScrollBar(), &QScrollBar::valueChanged, ui->seqViewer->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->seqViewer->verticalScrollBar(), &QScrollBar::valueChanged, ui->rulerEdit->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->rulerEdit->verticalScrollBar(), &QScrollBar::valueChanged, ui->seqViewer->verticalScrollBar(), &QScrollBar::setValue);

    // Options Panel setup
    ui->optionsPanel->hide();
    ui->optLine->hide();
    ui->themeCombo->addItems(QStringList()= {"Default","Neon","Gradient","New",
            "Clustal X","Annotations"});

    // Sequence TreeView setup
    this->seqModel = new QStandardItemModel(this);
    //this->seqModel->setHorizontalHeaderLabels(QStringList("Sequences"));
    seqRoot = this->seqModel->invisibleRootItem();
    seqStartFolderItem = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("Uncategorized"));
    seqStartFolderItem->setData(true, FolderRole);
    seqRoot->appendRow(seqStartFolderItem);
    connect(ui->seqTreeView, &QTreeView::expanded, this, &Linnaeo::expand_seqTreeView_item);
    connect(ui->seqTreeView, &QTreeView::collapsed, this, &Linnaeo::collapse_seqTreeView_item);
    //connect(ui->seqTreeView, &QTreeView::doubleClicked, this, &Linnaeo::on_seqTreeView_doubleClicked);

    // Connect tool buttons
    ui->quickAlignButton->setDefaultAction(ui->actionMake_Alignment);
    ui->quickAlignButton->setText("Align");
    ui->addSequenceButton->setDefaultAction(ui->actionAdd_Sequence);
    ui->importSequenceButton->setDefaultAction(ui->actionSequence_from_file);
    ui->addSequenceFolderButton->setDefaultAction(ui->actionAdd_Folder_to_Sequence_Panel);
    ui->downloadSeqButton->setDefaultAction(ui->actionGet_Online_Sequence);
    //ui->editSequenceButton
    ui->exportSequenceButton->setDefaultAction(ui->actionExportSequence);
    ui->deleteSequenceButton->setDefaultAction(ui->actionDelete_Selected_Sequences);
    ui->editSequenceButton->setDisabled(true);
    ui->exportSequenceButton->setDisabled(true);
    ui->quickAlignButton->setDisabled(true);

    // Alignment tree setup
    alignModel = new QStandardItemModel(this);
    alignRoot = alignModel->invisibleRootItem();
    alignStartFolderItem = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("Uncategorized"));
    alignStartFolderItem->setData(true, FolderRole);
    alignRoot->appendRow(alignStartFolderItem);
    // Connect tool buttons
    ui->importAlignmentButton->setDefaultAction(ui->actionAlignment_from_file);
    ui->addAlignmentFolderButton->setDefaultAction(ui->actionAdd_Alignment_Folder);
    //ui->editAlignmentButton
    ui->exportAlignmentButton->setDefaultAction(ui->actionExportAlignment);
    ui->deleteAlignmentButton->setDefaultAction(ui->actionDelete_Selected_Alignments);
    connect(ui->alignTreeView, &QTreeView::expanded, this, &Linnaeo::expand_alignTreeView_item);
    connect(ui->alignTreeView, &QTreeView::collapsed, this, &Linnaeo::collapse_alignTreeView_item);
    connect(ui->alignTreeView, &QTreeView::doubleClicked, this, &Linnaeo::on_alignTreeView_doubleClicked);

    ui->seqTreeView->setModel(seqModel);
    ui->alignTreeView->setModel(alignModel);
    connect(ui->seqTreeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Linnaeo::modifySeqActions);

    ui->seqTreeView->installEventFilter(this);
    ui->alignTreeView->installEventFilter(this);


    // DEBUGGING!
    QStandardItem *debugItem = new QStandardItem("DEBUG");
    debugItem->setData( "MDADASTITPEELDFIRQRALRRFDSIVPTAGREGTEIASDIFKGRTLAIYTSGGDSQGM"
                        "NSAVRSITRMAIYCGCKVYLIYEGYEGMIEGGDFIKEATWNTVSDIIQQGGTIIGSARSS"
                        "EFRTREGRLKAATNLINRGIGRLVCIGGDGSLTGANTFRLEWTDLVQELVKNQRVTAAAA"
                        "KKIPYIQIVGLVGSIDNDFCGTDMTIGTDSALQRIISSIDAVVATAQSHQRAFVIEVMGR"
                        "HCGYLALVAALASEADFCFIPEWPAPENWRDVLCDKLSQMRSEGQRLNIIIVAEGAIDRD"
                        "GKAITAEDVKTAVKEKLKYDTRVTILGHVQRGGAPSAFDRLLGCRMGAEAVFALMEMTEE"
                        "SEPCVISIDGNVMVRVPLLKCVERTQMVQKAMADKDWTTAVMLRGRSFQRNLETYKLLTK"
                        "MRTVEKDNLSEGHKFNVAVINVGAPAGGMNAAVRSYVRMALYHQCTVYGIEDSFEGLANG"
                        "SFKQFKWSDVTNWAMNGGSFLGTQKSLPTEKTMPQLAAQLKKHNIQALLLVGGFEAYHST"
                        "IILAENREKYPEFCIPMCVIPCTISNNVPGTMVSLGSDTAINEICQMIDKIKQSATGTKR"
                        "RVFIVETMGGYCGYLATLSALSSGADNAYIFEEPFTVQDLSDDVDVILSKMEVGAKRYLV"
                        "VRNEWADKNLTTDFVQNLFDSEGKKNFTTRVNVLGHVQQGGSPTPFDRNMGTKLAARALE"
                        "FLLIQLKENLTADNKVIAKSAHTATLLGLKGRKVVFTPVQDLKKETDFEHRLPSEQWWMA"
                        "LRPLLRVLARHRSTVESSAILESVEEESADSHMF", SequenceRole);
    seqStartFolderItem->appendRow(debugItem);
    ui->seqTreeView->setExpanded(seqModel->indexFromItem(seqStartFolderItem),true);

}
Linnaeo::~Linnaeo()
{   delete ui;}

bool Linnaeo::eventFilter(QObject *object, QEvent *event)
/// Event filter for turning on certain buttons etc, depending on events that are detected

{
    return QMainWindow::eventFilter(object, event);
    /*if (object == ui->seqTreeView) {
        if (event->type() == QEvent::FocusIn) {
            qDebug() << "SeqTree received focus";
            return true;
        } else if (event->type() == QEvent::FocusOut)
        {
            qDebug() << "SeqTree lost foucs";
            return true;
        }
        else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(object, event);
    }*/
}


// FILE MENU SLOTS
void Linnaeo::on_actionNew_triggered()
    /// Starts a new detached Linnaeo instance.
{   // Almost perfect, except closing the first instance will close the connection to stdout.
    //qint64* pid;
    //QProcess::startDetached(QCoreApplication::applicationFilePath(),{},QDir::homePath(),pid);
    //spdlog::info("Started new window with procID {}", *pid);
    Linnaeo *newLinnaeo = new Linnaeo();
    newLinnaeo->setWindowIcon(QIcon(":/icons/linnaeo.ico"));
    newLinnaeo->show();}
void Linnaeo::on_actionQuit_triggered()
    /// Quits Linnaeo. Does not close other detached instances.
{   //QVector<qint64>::const_iterator iter;
    //if(this->procIds.length()>0){
    //    for(iter=this->procIds.begin();iter != this->procIds.end(); iter++){
    //
    this->close(); }
// EDIT MENU SLOTS
void Linnaeo::on_actionPreferences_triggered()
    /// Opens preference panel.
{   Preferences *pref = new Preferences(this);
    pref->show(); }
void Linnaeo::on_actionCopy_triggered()
    /// Copies either all sequences or first alignment, depending on what is highlighted in focus.
{
    if(ui->seqTreeView->hasFocus() && ui->seqTreeView->selectionModel()->selectedIndexes().length() > 0)
    {
        //qDebug() << "SeqTree clicked";
        QString copied;
        for(int i = 0; i<ui->seqTreeView->selectionModel()->selectedIndexes().length(); i++)
        {
            QModelIndex index = ui->seqTreeView->selectionModel()->selectedIndexes().at(i);
            if(!index.data(FolderRole).toBool())
            {
                //qDebug() << "Sending to printer";
                copied.append(Sequence::prettyPrintFastaSequence(index.data(Qt::DisplayRole).toString(),index.data(SequenceRole).toString()));

            }
        }
        QClipboard *clippy = QGuiApplication::clipboard();
        clippy->setText(copied);
        qInfo(lnoIo) << "Copied out sequences!" << "\n" << qPrintable(copied);
    }
    else if (ui->alignTreeView->hasFocus() && ui->alignTreeView->selectionModel()->selectedIndexes().length() > 0)
    {
        QModelIndex index = ui->alignTreeView->selectionModel()->selectedIndexes().at(0);
        QString copied;
        if(!index.data(FolderRole).toBool())
        {
            QStringList names = index.data(NamesRole).toStringList();
            QStringList seqs = index.data(AlignmentRole).toStringList();
            //qDebug() <<names <<seqs;
            for(int i = 0; i<names.length(); i++)
            {
                copied.append(Sequence::prettyPrintFastaSequence(names.at(i),seqs.at(i)));
            }


        }
        QClipboard *clippy = QGuiApplication::clipboard();
        clippy->setText(copied);
        qInfo() << "Copied out alignment!" << "\n" << copied;
    }
    else qDebug(lnoIo)<<"not selected!";
}

// MANAGE MENU SLOTS
void Linnaeo::on_actionShow_Viewer_Options_triggered(bool checked)
    /// Show side panel of viewer.
{   if(checked){
        ui->optionsPanel->show();
        ui->optLine->show();
        //spdlog::debug("Showing options panel");
    }else{
        ui->optLine->hide();
        //spdlog::debug("Hiding options panel");
        ui->optionsPanel->hide(); }}

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
            newSeq->setData(false,FolderRole);
            newSeq->setData(seq,SequenceRole);
            newSeq->setDropEnabled(false);
            QStandardItem *item;
            bool found = false;
            for(const QModelIndex& index : indexes)
            {
                // Check each selected item (if any) to see if it is a folder. Add it to the first
                // folder it finds, otherwise add it to the "uncategorized" folder.
                item = this->seqModel->itemFromIndex(index);
                if (item->data(FolderRole).toBool())
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
            this->setWindowTitle(QString("Linnaeo [%1]").arg(newSeq->data(Qt::DisplayRole).toString()));
            ui->seqViewer->setDisplaySequence(newSeq->data(SequenceRole).toString(),newSeq->data(Qt::DisplayRole).toString());
        }
        else
        {
            //spdlog::warn("At least one of Name or Sequence field was left empty; please try again!");
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
    newFolder->setData(true,FolderRole);
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
            if (item->data(FolderRole).toBool())
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
    QString unaligned;
    QStandardItem *item;
    QList<QModelIndex> indexes = ui->seqTreeView->selectionModel()->selectedIndexes();
    for(auto&& index: indexes)
    {
        item = seqModel->itemFromIndex(index);
        unaligned.append(">").append(item->data(Qt::DisplayRole).toString())
                 .append("\n").append(item->data(SequenceRole).toString())
                 .append("\n");
    }
    AlignWorker *worker = new AlignWorker(unaligned);
    connect(worker, &AlignWorker::resultReady, this, &Linnaeo::addAlignmentToTree);
    connect(worker, &AlignWorker::finished, worker, &AlignWorker::deleteLater);
    worker->run();
}
void Linnaeo::addAlignmentToTree(const QList<QStringList> result)
{
    QList<QString> names = result.at(0);
    QList<QString> seqs = result.at(1);
    QStandardItem *item = new QStandardItem(QString("New Alignment (%1)").arg(names.join(", ")));
    item->setData(seqs, AlignmentRole);
    item->setData(names,NamesRole);
    alignStartFolderItem->appendRow(item);
    ui->alignTreeView->expand(alignStartFolderItem->index());
    ui->seqViewer->setDisplayAlignment(seqs, names);
    this->setWindowTitle(QString("Linnaeo [%1]").arg(item->data(Qt::DisplayRole).toString()));
}

void Linnaeo::on_actionAdd_Alignment_Folder_triggered()
    /// Identical behavior as for the Sequence equivalent.
{
    QStandardItem *newFolder = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("New Folder"));
    newFolder->setData(true,FolderRole);
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
            if (item->data(FolderRole).toBool())
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
    /// Expand/collapse slots are for animating the icon in the tree view!
{
    //spdlog::debug("Expanded SeqView tree at position {}", index.row());
    seqModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder-open.svg"),Qt::DecorationRole);
}
void Linnaeo::collapse_seqTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Collapsed SeqView tree at position {}", index.row());
    seqModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}
void Linnaeo::expand_alignTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Expanded AlignView tree at position {}", index.row());
    alignModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder-open.svg"),Qt::DecorationRole);
}
void Linnaeo::collapse_alignTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Collapsed AlignView tree at position {}", index.row());
    alignModel->itemFromIndex(index)->setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}
void Linnaeo::on_actionGet_Online_Sequence_triggered()
{
    SearchUniprot search(this);
    int nameSource;
    QStringList ids;
    QStringList names;
    QStringList organisms;
    QStringList genes;
    QStringList descs;
    QStringList seqs;
    QStandardItem *item;
    QStringList info;
    QString infoStr;

    if (search.exec() == QDialog::Accepted)
    {
        nameSource = search.chosenNameSource();
        if(nameSource >= 0)
        {
            ids = search.chosenIds();
            names = search.chosenNames();
            organisms = search.chosenOrganisms();
            genes = search.chosenGenes();
            descs = search.chosenProteins();
            seqs = search.chosenSequences();
            for(int i = 0; i<seqs.length(); i++)
            {
                item = new QStandardItem();
                item->setData(false, FolderRole);
                item->setData(seqs.at(i),SequenceRole);
                info.append(ids.at(i));
                info.append(names.at(i));
                info.append(genes.at(i));
                info.append(organisms.at(i));
                info.append(descs.at(i));
                infoStr = info.join("||");
                //qDebug(lnoIo) << infoStr << "\n";
                item->setData(infoStr, InfoRole);
                if(nameSource == 0) {item->setText(ids.at(i));}
                else if(nameSource == 1) {item->setText(names.at(i));}
                else if(nameSource == 2) {item->setText(genes.at(i));}
                else {item->setText("New Sequence");}
                item->setDropEnabled(false);

                QList<QModelIndex>indexes = ui->seqTreeView->selectionModel()->selectedIndexes();
                QStandardItem *sourceItem;
                bool found = false;
                for(const QModelIndex& index : indexes)
                {
                    // Check each selected item (if any) to see if it is a folder. Add it to the first
                    // folder it finds, otherwise add it to the "uncategorized" folder.
                    sourceItem = seqModel->itemFromIndex(index);
                    if (sourceItem->data(FolderRole).toBool())
                    {
                        sourceItem->appendRow(item);
                        ui->seqTreeView->expand(index);
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    seqStartFolderItem->appendRow(item);
                    ui->seqTreeView->expand(seqStartFolderItem->index());
                }
            }
        }
    }

}
void Linnaeo::on_actionClose_triggered()
{
    this->setWindowTitle(QString("Linnaeo"));
    ui->seqViewer->clearViewer();
}
void Linnaeo::on_themeCombo_currentIndexChanged(int index)
{
    ui->seqViewer->setTheme(index);
}
void Linnaeo::on_colorsEnabled_toggled(bool checked)
{
    ui->seqViewer->setColors(checked);
}
void Linnaeo::on_seqTreeView_doubleClicked(const QModelIndex &index)
{
    if(!index.data(FolderRole).toBool()){
        QString name;
        QString seq;
        name = index.data(Qt::DisplayRole).toString();
        seq = index.data(SequenceRole).toString();
        this->setWindowTitle(QString("Linnaeo [%1]").arg(name));
        // Call sequence formatter.
        ui->seqViewer->setDisplaySequence(seq, name);
    }
}

void Linnaeo::modifySeqActions(const QItemSelection &sele, const QItemSelection &desel)
/// This code is here to specifically turn on the different SeqTreeView buttons on and off depending on selection.
{
    if(ui->seqTreeView->selectionModel()->selectedIndexes().size() > 0)
    {
        if(ui->seqTreeView->selectionModel()->selectedIndexes().size() == 1) // if one item selected...
        {
            if(ui->seqTreeView->selectionModel()->selectedIndexes().first().data(FolderRole).toBool()) // if it's a folder...
            {
                ui->editSequenceButton->setDisabled(true);
                ui->exportSequenceButton->setDisabled(true);
                ui->quickAlignButton->setDisabled(true);
            }
            else
            {
                ui->editSequenceButton->setDisabled(false);
                ui->exportSequenceButton->setDisabled(false);
                ui->quickAlignButton->setDisabled(true);
            }
        }
        else
        {
            int count = 0;
            for(auto&& index: ui->seqTreeView->selectionModel()->selectedIndexes())
            {
                if(index.data(SequenceRole).isValid())
                {
                    count += 1;
                }
            }
            if (count > 1) ui->quickAlignButton->setDisabled(false);
            else ui->quickAlignButton->setDisabled(true);
        }

    }
    else
    {
        ui->editSequenceButton->setDisabled(true);
        ui->exportSequenceButton->setDisabled(true);
        ui->quickAlignButton->setDisabled(true);
    }
}

void Linnaeo::updateNamesAndRuler(QString names, QString ruler)
{
    ui->namesEdit->document()->clear();
    ui->namesEdit->document()->setHtml(names);
    ui->rulerEdit->document()->clear();
    ui->rulerEdit->document()->setHtml(ruler);
}



void Linnaeo::on_wrapEnabled_toggled(bool checked)
{
    ui->seqViewer->setWrapSeqs(checked);
}

void Linnaeo::on_alignTreeView_doubleClicked(const QModelIndex &index)
{
    if(!index.data(FolderRole).toBool()){
        this->setWindowTitle(QString("Linnaeo [%1]").arg(index.data(Qt::DisplayRole).toString()));
        ui->seqViewer->setDisplayAlignment(index.data(AlignmentRole).toStringList(), index.data(NamesRole).toStringList());
    }

}

void Linnaeo::on_actionExportAlignment_triggered()
{

}

void Linnaeo::on_actionAlignment_from_file_triggered()
{
    QString result;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Alignment"),QStandardPaths::locate(QStandardPaths::DesktopLocation,""),tr("Alignment File (*.aln *.fa)"));
    QFile file = QFile(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
          result.append(in.readAll());
       }
       file.close();
    }
    if(result[0] == '>')
    {
        QList<QStringList> parsed = Sequence::splitFastaAlignmentString(result);

        QList<QString> names = parsed.at(0);
        QList<QString> seqs = parsed.at(1);
        if(seqs.length() > 15)
        {
            ui->wrapEnabled->setChecked(false);
            qInfo(lnoView) << "Detected"<<seqs.length()<<"sequences in alignment, disabling sequence wrapping to improve performance";
        }
        QStandardItem *item = new QStandardItem(QString("New Alignment (HUGE)"));//.arg(names.join(", ")));
        item->setData(seqs, AlignmentRole);
        item->setData(names,NamesRole);
        alignStartFolderItem->appendRow(item);
        ui->alignTreeView->expand(alignStartFolderItem->index());

        ui->seqViewer->setDisplayAlignment(seqs, names);
    }
}
