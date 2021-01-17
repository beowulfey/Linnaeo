#ifndef LINNAEO_H
#define LINNAEO_H

#include "logging.h"
#include "alignworker.h"
#include "alignmenteditor.h"
#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelection>

QT_BEGIN_NAMESPACE
namespace Ui { class Linnaeo; }
//class QStandardItemModel;
QT_END_NAMESPACE



class Linnaeo : public QMainWindow
{
    Q_OBJECT


public:
    Linnaeo(QWidget *parent = nullptr);
    QModelIndex searchForMadeAlignment(QModelIndex root, QStringList query);
    void dataStreamThroughTree(QStandardItem *root, QDataStream &stream, bool out=false);
    void openFromFile(QString fileName); // is run from main.cpp for parsing cmd line options
    ~Linnaeo();

    quint32 magic = 0xA0B0C0D0;
    qint32 fvers = 100;
    enum ItemType
    {
        FolderRole=Qt::UserRole,        // bool           // Is this a folder
        SequenceRole=Qt::UserRole+1,    // QString        // (SEQUENCE) contains a single sequence
        InfoRole=Qt::UserRole+2,        // QString        // (SEQUENCE) contains additional information from uniprot
        AlignmentRole=Qt::UserRole+3,   // QList<QString> // contains the alignment
        NamesRole=Qt::UserRole+4        // QList<QString> // used for saving
    };
    Q_ENUM(Linnaeo::ItemType);


private:
    Ui::Linnaeo *ui;
    AlignWorker *worker;


    //QVector<qint64> procIds;
    QStandardItemModel *seqModel = nullptr;
    QStandardItem *seqStartFolderItem = nullptr;
    QStandardItemModel *alignModel = nullptr;
    QStandardItem *alignStartFolderItem = nullptr;
    QFont defaultFont;
    bool changed = false;
    QString lastDirWorkspace;
    QString lastDirSequence;
    QString lastDirAlignment;




protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

private slots:
    void updateSequenceCombo(QStringList names);
    void addAlignmentToTree(const QList<QStringList> result);
    void alignmentFailed(int err);

    void on_actionNew_triggered();
    void on_actionShow_Viewer_Options_triggered(bool checked);
    void on_actionPreferences_triggered();
    void on_actionQuit_triggered();
    void expand_seqTreeView_item(const QModelIndex &index);
    void collapse_seqTreeView_item(const QModelIndex &index);
    void expand_alignTreeView_item(const QModelIndex &index);
    void collapse_alignTreeView_item(const QModelIndex &index);
    void on_actionAdd_Sequence_triggered();
    void on_actionDelete_Selected_Sequences_triggered();
    void on_actionAdd_Folder_to_Sequence_Panel_triggered();
    void on_actionMake_Alignment_triggered();
    void on_actionAdd_Alignment_Folder_triggered();
    void on_actionDelete_Selected_Alignments_triggered();
    void on_actionEdit_Sequence_triggered();
    void on_actionGet_Online_Sequence_triggered();
    void on_actionClose_triggered();
    void on_themeCombo_currentIndexChanged(int index);
    void on_colorsEnabled_toggled(bool checked);
    void on_seqTreeView_doubleClicked(const QModelIndex &index);
    void on_actionCopy_triggered();
    //void on_seqTreeView_clicked(const QModelIndex &index);
    void modifySeqActions(const QItemSelection &sel, const QItemSelection &desel);
    void modifyAlignActions(const QItemSelection &sel, const QItemSelection &desel);
    void updateNamesAndRuler(const QString, const QString);
    void on_wrapEnabled_toggled(bool checked);
    void on_alignTreeView_doubleClicked(const QModelIndex &index);
    void on_actionExportAlignment_triggered();
    void on_actionAlignment_from_file_triggered();
    void on_actionSave_Workspace_triggered();
    void on_actionSequence_from_file_triggered();
    void on_actionOpen_triggered();
    void on_actionCapture_Image_triggered();
    void on_actionExportSequence_triggered();
    void on_actionIncrease_Font_triggered();
    void on_actionDecrease_Font_triggered();
    void on_actionInfo_Mode_triggered(bool checked);
    void on_actionPaste_triggered();
    void on_conservedEnabled_toggled(bool checked);
    void on_conservedCombo_currentIndexChanged(int index);
    void on_actionEdit_Alignment_triggered();
    void on_actionAbout_triggered();
};

//Q_DECLARE_METATYPE(Linnaeo::ItemType);
#endif // LINNAEO_H
