#include "linnaeo.h"
#include "./ui_linnaeo.h"
#include "seqeditor.h"
#include "preferences.h"
#include "searchuniprot.h"
#include "alignworker.h"
#include "sequence.h"
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>
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
    defaultFont = QFont("Noto Custom", 10.0, 1);
    ui->namesEdit->setFont(defaultFont);
    ui->seqViewer->setFont(defaultFont);
    ui->rulerEdit->setFont(defaultFont);
    connect(ui->seqViewer, &SeqViewer::updatedNamesAndRuler, this, &Linnaeo::updateNamesAndRuler);
    connect(ui->seqViewer->verticalScrollBar(), &QScrollBar::valueChanged, ui->namesEdit->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->namesEdit->verticalScrollBar(), &QScrollBar::valueChanged, ui->seqViewer->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->seqViewer->verticalScrollBar(), &QScrollBar::valueChanged, ui->rulerEdit->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->rulerEdit->verticalScrollBar(), &QScrollBar::valueChanged, ui->seqViewer->verticalScrollBar(), &QScrollBar::setValue);

    worker = new AlignWorker(this);
    connect(worker, &AlignWorker::resultReady, this, &Linnaeo::addAlignmentToTree);
    connect(worker, &AlignWorker::resultFailed, this, &Linnaeo::alignmentFailed);
    connect(worker, &AlignWorker::finished, worker, &AlignWorker::deleteLater);


    // Options Panel setup
    ui->optionsPanel->hide();
    ui->optLine->hide();
    ui->themeCombo->addItems(QStringList()= {"Linnaeo","Neon","Gradient","New",
            "Clustal X","Annotations"});

    // Sequence TreeView setup
    this->seqModel = new QStandardItemModel(this);
    //this->seqModel->setHorizontalHeaderLabels(QStringList("Sequences"));
    seqRoot = this->seqModel->invisibleRootItem();
    seqStartFolderItem = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("Uncategorized"));
    seqStartFolderItem->setData(QVariant(true), FolderRole);
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
    // disable buttons
    ui->editSequenceButton->setDisabled(true);
    ui->exportSequenceButton->setDisabled(true);
    ui->deleteSequenceButton->setDisabled(true);
    ui->quickAlignButton->setDisabled(true);
    ui->actionEdit_Sequence->setDisabled(true);
    ui->actionExportSequence->setDisabled(true);
    ui->actionQuick_Align->setDisabled(true);
    ui->actionDelete_Selected_Sequences->setDisabled(true);

    // Alignment tree setup
    alignModel = new QStandardItemModel(this);
    alignRoot = alignModel->invisibleRootItem();
    alignStartFolderItem = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("Uncategorized"));
    alignStartFolderItem->setData(QVariant(true), FolderRole);
    alignRoot->appendRow(alignStartFolderItem);
    // Connect tool buttons
    ui->importAlignmentButton->setDefaultAction(ui->actionAlignment_from_file);
    ui->addAlignmentFolderButton->setDefaultAction(ui->actionAdd_Alignment_Folder);
    //ui->editAlignmentButton
    ui->exportAlignmentButton->setDefaultAction(ui->actionExportAlignment);
    ui->deleteAlignmentButton->setDefaultAction(ui->actionDelete_Selected_Alignments);
    ui->editAlignmentButton->setDefaultAction(ui->actionEdit_Alignment);
    connect(ui->alignTreeView, &QTreeView::expanded, this, &Linnaeo::expand_alignTreeView_item);
    connect(ui->alignTreeView, &QTreeView::collapsed, this, &Linnaeo::collapse_alignTreeView_item);
   // connect(ui->alignTreeView, &QTreeView::doubleClicked, this, &Linnaeo::on_alignTreeView_doubleClicked);
    // disable buttons
    ui->editAlignmentButton->setDisabled(true);
    ui->actionEdit_Alignment->setDisabled(true);
    ui->exportAlignmentButton->setDisabled(true);
    ui->actionExportAlignment->setDisabled(true);
    ui->deleteAlignmentButton->setDisabled(true);
    ui->actionDelete_Selected_Alignments->setDisabled(true);

    ui->seqTreeView->setModel(seqModel);
    ui->alignTreeView->setModel(alignModel);
    connect(ui->seqTreeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Linnaeo::modifySeqActions);
    connect(ui->alignTreeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &Linnaeo::modifyAlignActions);

    //ui->seqTreeView->installEventFilter(this);
    //ui->alignTreeView->installEventFilter(this);
    //qApp->installEventFilter(this);


    // DEBUGGING!
    QStandardItem *debugItem = new QStandardItem("DEBUG");
    debugItem->setData(QVariant("MDADASTITPEELDFIRQRALRRFDSIVPTAGREGTEIASDIFKGRTLAIYTSGGDSQGM"
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
                        "LRPLLRVLARHRSTVESSAILESVEEESADSHMF"), SequenceRole);
    seqStartFolderItem->appendRow(debugItem);
    ui->seqTreeView->setExpanded(seqModel->indexFromItem(seqStartFolderItem),true);

    //ui->colorsEnabled->setChecked(false);

}
Linnaeo::~Linnaeo()
{   delete ui;}

bool Linnaeo::eventFilter(QObject *object, QEvent *event)
/// Event filter for turning on certain buttons etc, depending on events that are detected

{
    //if(event->type() == QEvent::Resize) qDebug(lnoEvent) << object << event->type();
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
    newLinnaeo->show();
}
void Linnaeo::on_actionOpen_triggered()
/// Opens the file selected and streams in the data.
{
    int ret = QMessageBox::Discard;
    if(changed)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Unsaved changes");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setTextFormat(Qt::MarkdownText);
        msgBox.setText("#### Watch out! You have unsaved changes!");
        msgBox.setInformativeText("Do you want to save your workspace?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        ret = msgBox.exec();
        if(ret == QMessageBox::Save)
        {
            on_actionSave_Workspace_triggered();
        }
    }
    if(ret != QMessageBox::Cancel)
    {

        QString dir;
        (lastDirWorkspace.isEmpty()) ? dir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                                   : dir = lastDirWorkspace;
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Linnaeo Workspace"),dir,tr("Linnaeo Workspace (*.lno)"));
        QFile file = QFile(fileName);
        qInfo(lnoIo) <<"Attempting to read workspace at"<<fileName;
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream in(&file);
            quint32 magicIn;
            in >> magicIn;
            qint32 fileVersion;
            in >> fileVersion;
            if (magicIn != magic || fileVersion < fvers) {
                qWarning(lnoIo) << "Unable to read file! Sorry, this workspace is likely not compatible with this version.";
            }
            else {
                seqModel->clear();
                alignModel->clear();
                in.setVersion(QDataStream::Qt_6_0);
                qDebug(lnoIo) << "Loading SEQUENCE Tree";
                dataStreamThroughTree(seqModel->invisibleRootItem(),in,false);
                qDebug(lnoIo) << "Loading ALIGNMENT Tree";
                dataStreamThroughTree(alignModel->invisibleRootItem(),in,false);
                for(int r = 0; r < seqModel->invisibleRootItem()->rowCount(); ++r)
                {
                    if(seqModel->invisibleRootItem()->child(r)->hasChildren()) ui->seqTreeView->setExpanded((seqModel->invisibleRootItem()->child(r)->index()),true);
                    if(seqModel->invisibleRootItem()->child(r)->data(Qt::DisplayRole).toString() == "Uncategorized")
                    {
                        this->seqStartFolderItem = seqModel->invisibleRootItem()->child(r);
                    }
                }
                for(int r = 0; r < alignModel->invisibleRootItem()->rowCount(); ++r)
                {
                    if(alignModel->invisibleRootItem()->child(r)->hasChildren()) ui->alignTreeView->setExpanded((alignModel->invisibleRootItem()->child(r)->index()),true);
                    if(alignModel->invisibleRootItem()->child(r)->data(Qt::DisplayRole).toString() == "Uncategorized")
                    {
                        this->alignStartFolderItem = alignModel->invisibleRootItem()->child(r);
                    }
                }

                qInfo(lnoIo) << "Workspace loaded successfully!";
            }
            file.close();
            lastDirWorkspace = QFileInfo(file).absolutePath();
            on_actionClose_triggered();
        }
    }
}

void Linnaeo::on_actionSave_Workspace_triggered()
{
    QString dir;
    (lastDirWorkspace.isEmpty()) ? dir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"//workspace"
                               : dir = lastDirWorkspace+"//workspace";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Linnaeo Workspace"),dir,tr("Linnaeo Workspace (*.lno)"));
    if(!(fileName == ""))
    {
        QFile file = QFile(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
           QDataStream out(&file);
           // Write a header with a "magic number" and a version
           out << (quint32)magic;
           out << (qint32)fvers;
           out.setVersion(QDataStream::Qt_6_0);

           // Iterate through the sequence tree and save each QStandardItem
           qDebug(lnoIo) << "Saving SEQUENCE Tree";
           dataStreamThroughTree(seqModel->invisibleRootItem(),out,true);
           qDebug(lnoIo) << "Saving ALIGNMENT Tree";
           dataStreamThroughTree(alignModel->invisibleRootItem(),out,true);
           file.close();
           qInfo(lnoIo) << "Saved workspace to"<<fileName;
           lastDirWorkspace = QFileInfo(file).absolutePath();
           changed = false;
        }
    }

}

void Linnaeo::on_actionSequence_from_file_triggered()
/// Import sequence
{
    QString dir;
    (lastDirSequence.isEmpty()) ? dir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                               : dir = lastDirSequence;
    QString result;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sequence"),dir,tr("Protein Sequence (*.fasta *.fa)"));
    if(!(fileName == ""))
    {
        QFile file = QFile(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
           QTextStream in(&file);
           while (!in.atEnd())
           {
              result.append(in.readAll());
           }
           file.close();
           lastDirSequence = QFileInfo(file).absolutePath();
        }
        if(result[0] == '>')
        {
            QList<QStringList> parsed = Sequence::splitFastaAlignmentString(result);

            const QString name = parsed.at(0).at(0);
            const QString seq = parsed.at(1).at(0);
            QStandardItem *item = new QStandardItem(name);
            item->setData(seq, SequenceRole);
            seqStartFolderItem->appendRow(item);
            ui->seqTreeView->expand(seqStartFolderItem->index());

            ui->seqViewer->setDisplaySequence(seq, name);
            this->setWindowTitle(QString("Linnaeo [%1]").arg(item->data(Qt::DisplayRole).toString()));
            changed = true;

        }
    }
}

void Linnaeo::on_actionAlignment_from_file_triggered()
{
    QString result;
    QString dir;
    (lastDirAlignment.isEmpty()) ? dir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                               : dir = lastDirAlignment;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Alignment"),dir,tr("Fasta alignment (*.aln *.fa)"));
    if(!(fileName == ""))
    {
        QFile file = QFile(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
           QTextStream in(&file);
           while (!in.atEnd())
           {
              result.append(in.readAll());
           }
           file.close();
           lastDirAlignment = QFileInfo(file).absolutePath();
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
            item->setData(QVariant(seqs), AlignmentRole);
            item->setData(QVariant(names),NamesRole);
            alignStartFolderItem->appendRow(item);
            ui->alignTreeView->expand(alignStartFolderItem->index());

            ui->seqViewer->setDisplayAlignment(seqs, names);
            this->setWindowTitle(QString("Linnaeo [%1]").arg(item->data(Qt::DisplayRole).toString()));
            changed = true;
        }
    }
}

void Linnaeo::on_actionExportSequence_triggered()
{
    QModelIndex selected = ui->seqTreeView->selectionModel()->selectedIndexes().first();
    if(!selected.data(FolderRole).toBool())
    {
        QString dir;
        (lastDirSequence.isEmpty()) ? dir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+QString("//%1").arg(selected.data(Qt::DisplayRole).toString())
                                   : dir = lastDirSequence+QString("//%1").arg(selected.data(Qt::DisplayRole).toString());
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Sequence"),dir,tr("Fasta Sequence (*.fasta);; Any (*)"));
        if(!(fileName == ""))
        {
            QFile file = QFile(fileName);
            if (file.open(QIODevice::WriteOnly))
            {
                QTextStream stream(&file);
                QString output = Sequence::prettyPrintFastaSequence(selected.data(Qt::DisplayRole).toString(), selected.data(SequenceRole).toString());
                stream << output;
                file.close();
            }
            lastDirSequence = QFileInfo(file).absolutePath();
        }

    }
}
void Linnaeo::on_actionExportAlignment_triggered()
/// Exports the selected alignment as a FASTA. Only formatted supported for now.
{
    QModelIndex selected = ui->alignTreeView->selectionModel()->selectedIndexes().first();
    if(!selected.data(FolderRole).toBool())
    {
        QString dir;
        (lastDirAlignment.isEmpty()) ? dir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+QString("//%1").arg(selected.data(Qt::DisplayRole).toString())
                                   : dir = lastDirAlignment+QString("//%1").arg(selected.data(Qt::DisplayRole).toString());
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Alignment"),dir,tr("Fasta Alignment (*.aln);; Any (*)"));
        if(!(fileName == ""))
        {
            QFile file = QFile(fileName);
            if (file.open(QIODevice::WriteOnly))
            {
                QTextStream stream(&file);
                QList<QString> names = selected.data(NamesRole).toStringList();
                QList<QString> seqs = selected.data(AlignmentRole).toStringList();
                QString output;
                for(int i = 0; i<names.length(); i++)
                {
                    output.append(Sequence::prettyPrintFastaSequence(names.at(i),seqs.at(i)));
                }
                stream << output;
                file.close();
                lastDirAlignment = QFileInfo(file).absolutePath();
            }
        }
    }
}



void Linnaeo::on_actionQuit_triggered()
    /// Quits Linnaeo. Does not close other detached instances.
{
    int ret = QMessageBox::Discard;
    if(changed)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Unsaved changes");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setTextFormat(Qt::MarkdownText);
        msgBox.setText("#### Watch out! You have unsaved changes!");
        msgBox.setInformativeText("Do you want to save your workspace?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        ret = msgBox.exec();
        if(ret == QMessageBox::Save)
        {
            on_actionSave_Workspace_triggered();
        }
    }
    if(ret != QMessageBox::Cancel)
    {
        this->close();
    }
}

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
            newSeq->setData(QVariant(false),FolderRole);
            newSeq->setData(QVariant(seq),SequenceRole);
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
            changed = true;
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
        changed = true;
    }
}
void Linnaeo::on_actionAdd_Folder_to_Sequence_Panel_triggered()
    /// Adds a folder to the sequence panel. Without having anything selected, it will insert the
    /// new folder above the "Uncategorized" folder. If things are selected, it will add to the first folder
    /// it finds; otherwise, it will add to the parent of the selected object.
{
    QStandardItem *newFolder = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("New Folder"));
    newFolder->setData(QVariant(true),FolderRole);
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
    changed = true;

}
void Linnaeo::on_actionMake_Alignment_triggered()
{
    QString unaligned;
    QModelIndex exists;
    QStringList query;
    QList<QModelIndex> indexes = ui->seqTreeView->selectionModel()->selectedIndexes();
    for(auto&& index: indexes)
    {
        query.append(index.data(SequenceRole).toString()); // create a hash of name:seq
        unaligned.append(">").append(index.data(Qt::DisplayRole).toString())
                 .append("\n").append(index.data(SequenceRole).toString())
                 .append("\n");
    }
    query.sort();
    exists = searchForMadeAlignment(alignModel->invisibleRootItem()->index(), query);
    //qDebug(lnoMain) << "Returned value" <<exists;
    if(!exists.isValid())
    {
        qDebug(lnoMain) << "Unable to find item, making new";
        worker->setSeqs(unaligned);
        worker->run();
    }
    else
    {
        qDebug(lnoMain) << "using previously generated alignment!";
        ui->seqViewer->setDisplayAlignment(exists.data(AlignmentRole).toStringList(), exists.data(NamesRole).toStringList());
        this->setWindowTitle(QString("Linnaeo [%1]").arg(exists.data(Qt::DisplayRole).toString()));
        ui->alignTreeView->selectionModel()->select(exists,QItemSelectionModel::ClearAndSelect);
        ui->alignTreeView->setFocus();
    }
}
void Linnaeo::addAlignmentToTree(const QList<QStringList> result)
{
    QList<QString> names = result.at(0);
    QList<QString> seqs = result.at(1);
    QStandardItem *item = new QStandardItem(QString("New Alignment (%1)").arg(names.join(", ")));
    item->setData(QVariant(seqs), AlignmentRole);
    item->setData(QVariant(names),NamesRole);
    alignStartFolderItem->appendRow(item);
    ui->alignTreeView->expand(alignStartFolderItem->index());
    ui->seqViewer->setDisplayAlignment(seqs, names);
    this->setWindowTitle(QString("Linnaeo [%1]").arg(item->data(Qt::DisplayRole).toString()));
    ui->alignTreeView->selectionModel()->select(item->index(),QItemSelectionModel::ClearAndSelect);
    ui->alignTreeView->setFocus();
    changed = true;
}

void Linnaeo::alignmentFailed(int err)
{
    qInfo(lnoProc) << "Internal muscle error"<<err<<" please try again";
}

void Linnaeo::on_actionAdd_Alignment_Folder_triggered()
    /// Identical behavior as for the Sequence equivalent.
{
    QStandardItem *newFolder = new QStandardItem(QIcon(":/icons/ui/folder.svg"),QString("New Folder"));
    newFolder->setData(QVariant(true),FolderRole);
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
    changed = true;
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
        changed = true;
    }

}
void Linnaeo::on_actionEdit_Sequence_triggered()
{
    changed = true;
}

// OTHER SLOTS
void Linnaeo::expand_seqTreeView_item(const QModelIndex &index)
    /// Expand/collapse slots are for animating the icon in the tree view!
{
    //spdlog::debug("Expanded SeqView tree at position {}", index.row());
    seqModel->itemFromIndex(index)->setData(QVariant(QIcon(":/icons/ui/folder-open.svg")),Qt::DecorationRole);
}
void Linnaeo::collapse_seqTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Collapsed SeqView tree at position {}", index.row());
    seqModel->itemFromIndex(index)->setData(QVariant(QIcon(":/icons/ui/folder.svg")),Qt::DecorationRole);
}
void Linnaeo::expand_alignTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Expanded AlignView tree at position {}", index.row());
    alignModel->itemFromIndex(index)->setData(QVariant(QIcon(":/icons/ui/folder-open.svg")),Qt::DecorationRole);
}
void Linnaeo::collapse_alignTreeView_item(const QModelIndex &index)
{
    //spdlog::debug("Collapsed AlignView tree at position {}", index.row());
    alignModel->itemFromIndex(index)->setData(QVariant(QIcon(":/icons/ui/folder.svg")),Qt::DecorationRole);
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
                item->setData(QVariant(false), FolderRole);
                item->setData(QVariant(seqs.at(i)),SequenceRole);
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
    changed = true;

}
void Linnaeo::on_actionClose_triggered()
{
    this->setWindowTitle(QString("Linnaeo"));
    ui->seqViewer->clearViewer();
    ui->namesEdit->document()->clear();
    ui->rulerEdit->document()->clear();
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
                ui->actionEdit_Sequence->setDisabled(true);
                ui->exportSequenceButton->setDisabled(true);
                ui->actionExportSequence->setDisabled(true);
                ui->quickAlignButton->setDisabled(true);
                ui->actionQuick_Align->setDisabled(true);
                //ui->actionDelete_Selected_Sequences->setDisabled(true);

                (ui->seqTreeView->selectionModel()->selectedIndexes().first() == seqStartFolderItem->index()) ? ui->deleteSequenceButton->setDisabled(true) :
                    ui->deleteSequenceButton->setDisabled(false);
                (ui->seqTreeView->selectionModel()->selectedIndexes().first() == seqStartFolderItem->index()) ? ui->actionDelete_Selected_Sequences->setDisabled(true) :
                    ui->actionDelete_Selected_Sequences->setDisabled(false);
            }
            else
            {
                ui->actionEdit_Sequence->setDisabled(false);
                ui->editSequenceButton->setDisabled(false);
                ui->exportSequenceButton->setDisabled(false);
                ui->actionExportSequence->setDisabled(false);
                ui->quickAlignButton->setDisabled(true);
                ui->actionQuick_Align->setDisabled(true);
                ui->deleteSequenceButton->setDisabled(false);
                ui->actionDelete_Selected_Sequences->setDisabled(false);
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
            if (count > 1) {
                ui->quickAlignButton->setDisabled(false);
                ui->actionQuick_Align->setDisabled(false);
            }
            else {
                ui->actionQuick_Align->setDisabled(true);
                ui->quickAlignButton->setDisabled(true);
            }
            if (count > 0) {
                ui->exportSequenceButton->setDisabled(false);
                ui->actionExportSequence->setDisabled(false);
                ui->editSequenceButton->setDisabled(false);
                ui->actionEdit_Sequence->setDisabled(false);

            }
            ui->deleteSequenceButton->setEnabled(true);
            ui->actionDelete_Selected_Sequences->setEnabled(true);

        }

    }
    else
    {
        ui->editSequenceButton->setDisabled(true);
        ui->actionEdit_Sequence->setDisabled(true);
        ui->exportSequenceButton->setDisabled(true);
        ui->actionExportSequence->setDisabled(true);
        ui->quickAlignButton->setDisabled(true);
        ui->actionQuick_Align->setDisabled(true);
        ui->deleteSequenceButton->setDisabled(true);
        ui->actionDelete_Selected_Sequences->setDisabled(true);
    }
}

void Linnaeo::modifyAlignActions(const QItemSelection &sel, const QItemSelection &desel)
{
    if(ui->alignTreeView->selectionModel()->selectedIndexes().size() > 0)
    {
        if(ui->alignTreeView->selectionModel()->selectedIndexes().first().data(FolderRole).toBool()) // if it's a folder...
        {
            ui->editAlignmentButton->setDisabled(true);
            ui->actionEdit_Alignment->setDisabled(true);
            ui->exportAlignmentButton->setDisabled(true);
            ui->actionExportAlignment->setDisabled(true);
            (ui->alignTreeView->selectionModel()->selectedIndexes().first() == alignStartFolderItem->index()) ?
                        ui->deleteAlignmentButton->setDisabled(true): ui->deleteAlignmentButton->setDisabled(false);
            (ui->alignTreeView->selectionModel()->selectedIndexes().first() == alignStartFolderItem->index()) ?
                        ui->actionDelete_Selected_Alignments->setDisabled(true): ui->actionDelete_Selected_Alignments->setDisabled(false);
        }
        else
        {
            ui->editAlignmentButton->setDisabled(false);
            ui->actionEdit_Alignment->setDisabled(false);
            ui->exportAlignmentButton->setDisabled(false);
            ui->actionExportAlignment->setDisabled(false);
            ui->deleteAlignmentButton->setDisabled(false);
            ui->actionDelete_Selected_Alignments->setDisabled(false);
        }
    }
    else
    {
        ui->editAlignmentButton->setDisabled(true);
        ui->actionEdit_Alignment->setDisabled(true);
        ui->exportAlignmentButton->setDisabled(true);
        ui->actionExportAlignment->setDisabled(true);
        ui->deleteAlignmentButton->setDisabled(true);
        ui->actionDelete_Selected_Alignments->setDisabled(true);
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


QModelIndex Linnaeo::searchForMadeAlignment(QModelIndex root, QStringList query)
/// Utility function for improving user experience. Prevents duplicate alignments from being added to the tree.
/// Searches through the nodes of the alignment tree until it finds one that contains the combination of names and sequences.
/// Will create a new alignment if the sequence names have changed, but I'm not sure how to
{
    QModelIndex found;
    //qDebug(lnoMain) << "Searching for node";
    for(int r = 0; r < alignModel->rowCount(root); ++r)
    {
        QStringList compare;
        //qDebug(lnoMain) << "Current parent node" << root.data(Qt::DisplayRole) << "checking row"<<r;
        QModelIndex index = alignModel->index(r, 0, root);
        for(int i = 0; i < index.data(AlignmentRole).toStringList().length(); i++)
        {
            compare.append(QString(index.data(AlignmentRole).toStringList().at(i)).replace("-","",Qt::CaseInsensitive));
            //qDebug(lnoMain) << "Building dictionary for row"<<r;
            //compare[index.data(NamesRole).toStringList().at(i)] = QString(index.data(AlignmentRole).toStringList().at(i)).replace("-","",Qt::CaseInsensitive);
        }
        //qDebug(lnoMain) <<"Compare"<<compare<<"vs"<<query;
        compare.sort();
        if(compare == query) {
            found = index;
            qDebug(lnoMain) << "Found match!";// << found;
            break;
        }
        else{
            qDebug(lnoMain) <<"Searching deeper...";
            if(alignModel->hasChildren(index)) found = searchForMadeAlignment(index, query);
        }
    }
    //qDebug(lnoMain) << "returning found" <<found;
    return found;
}


void Linnaeo::dataStreamThroughTree(QStandardItem *root, QDataStream &stream, bool out)
/// Utility function. Needed for iterating through a tree to rebuild after loading data.
{
    if(out)
    {
        qint32 rowCount = root->rowCount();
        stream<<(qint32)rowCount; // save row count for root
        qDebug(lnoIo) << "Current root has"<<rowCount<<"children";
        for(int r = 0; r < rowCount; ++r) // for each row under the root
        {
             QStandardItem *child = root->child(r);
             child->write(stream);
             qint32 childCount = child->rowCount();
             qDebug(lnoIo) << "Saved tree node" << child->data(Qt::DisplayRole).toString()<<"with"<<childCount<<"children";
             stream << (qint32)childCount;
             if(child->hasChildren()) dataStreamThroughTree(child, stream, true);
        }
        //qDebug(lnoMain) <<"Completed tree traversal";
    }
    else
    {
        qint32 rowCount;
        stream >> rowCount;
        qDebug(lnoIo) << "Current root has"<<rowCount<<"children";

        for(int r = 0; r < rowCount; ++r) // for each row under the root
        {
            QStandardItem *child = new QStandardItem;
            qint32 childCount;
            child->read(stream);
            root->appendRow(child);
            stream >> childCount;
            qDebug(lnoIo) << "Loaded tree node" << child->data(Qt::DisplayRole).toString()<<"with"<<childCount<<"children";
            if(childCount > 0){
                dataStreamThroughTree(child, stream, false);
            }
        }
        //qDebug(lnoMain) <<"Completed tree traversal";
    }

}



void Linnaeo::openFromFile(QString fileName)
{
    if(fileName.right(3)!="lno") qInfo(lnoMain) << "File not opened successfully:" << fileName;
    QFile file = QFile(fileName);
    qInfo(lnoIo) <<"Attempting to read workspace at"<<fileName;
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        quint32 magicIn;
        in >> magicIn;
        qint32 fileVersion;
        in >> fileVersion;
        if (magicIn != magic || fileVersion < fvers) {
            qWarning(lnoIo) << "Unable to read file! Sorry, this workspace is likely not compatible with this version.";
        }
        else {
            seqModel->clear();
            alignModel->clear();
            in.setVersion(QDataStream::Qt_6_0);
            qDebug(lnoIo) << "Loading SEQUENCE Tree";
            dataStreamThroughTree(seqModel->invisibleRootItem(),in,false);
            qDebug(lnoIo) << "Loading ALIGNMENT Tree";
            dataStreamThroughTree(alignModel->invisibleRootItem(),in,false);
            for(int r = 0; r < seqModel->invisibleRootItem()->rowCount(); ++r)
            {
                if(seqModel->invisibleRootItem()->child(r)->hasChildren()) ui->seqTreeView->setExpanded((seqModel->invisibleRootItem()->child(r)->index()),true);
                if(seqModel->invisibleRootItem()->child(r)->data(Qt::DisplayRole).toString() == "Uncategorized")
                {
                    this->seqStartFolderItem = seqModel->invisibleRootItem()->child(r);
                }
            }
            for(int r = 0; r < alignModel->invisibleRootItem()->rowCount(); ++r)
            {
                if(alignModel->invisibleRootItem()->child(r)->hasChildren()) ui->alignTreeView->setExpanded((alignModel->invisibleRootItem()->child(r)->index()),true);
                if(alignModel->invisibleRootItem()->child(r)->data(Qt::DisplayRole).toString() == "Uncategorized")
                {
                    this->alignStartFolderItem = alignModel->invisibleRootItem()->child(r);
                }
            }

            qInfo(lnoIo) << "Workspace loaded successfully!";
        }
        file.close();
        changed = false;
    }
}





void Linnaeo::on_actionCapture_Image_triggered()
{
    QSize out(ui->frame_2->size());
    out.scale(ui->frame_2->rect().width()*3,1080,Qt::KeepAspectRatioByExpanding);
    QPixmap img(out);
    img.setDevicePixelRatio(3);
    ui->frame_2->render(&img);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"),QStandardPaths::writableLocation(QStandardPaths::HomeLocation),tr("PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)"));
    img.save(fileName, nullptr, -1);
}



void Linnaeo::on_actionIncrease_Font_triggered()
{
    defaultFont.setPointSizeF(defaultFont.pointSizeF()+0.5);
    ui->seqViewer->setFont(defaultFont);
    ui->namesEdit->setFont(defaultFont);
    ui->rulerEdit->setFont(defaultFont);
    ui->seqViewer->fontChanged();
}

void Linnaeo::on_actionDecrease_Font_triggered()
{
    defaultFont.setPointSizeF(defaultFont.pointSizeF()-0.5);
    ui->seqViewer->setFont(defaultFont);
    ui->namesEdit->setFont(defaultFont);
    ui->rulerEdit->setFont(defaultFont);
    ui->seqViewer->fontChanged();
}

void Linnaeo::on_actionInfo_Mode_triggered(bool checked)
{
    ui->seqViewer->setInfoMode(checked);
}
