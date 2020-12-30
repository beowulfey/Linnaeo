#ifndef LINNAEO_H
#define LINNAEO_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelection>

QT_BEGIN_NAMESPACE
namespace Ui { class Linnaeo; }
class QStandardItemModel;
QT_END_NAMESPACE

class Linnaeo : public QMainWindow
{
    Q_OBJECT

public:
    Linnaeo(QWidget *parent = nullptr);
    ~Linnaeo();

private:
    Ui::Linnaeo *ui;
    enum ItemType
    {
        FolderRole=Qt::UserRole,
        SequenceRole=Qt::UserRole+1,
        InfoRole=Qt::UserRole+2,
        AlignmentRole=Qt::UserRole+3
    };
    enum seqTheme
    {
        DEFAULT = 0,
    };

    //QVector<qint64> procIds;
    QStandardItemModel *seqModel = nullptr;
    QStandardItem *seqStartFolderItem = nullptr;
    QStandardItemModel *alignModel = nullptr;
    QStandardItem *alignStartFolderItem = nullptr;
    QFont defaultFont;
protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

private slots:
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
    void addAlignmentToTree(const QHash<QString, QString> &seqDict);
    void on_actionCopy_triggered();
    //void on_seqTreeView_clicked(const QModelIndex &index);
    void modifySeqActions(const QItemSelection &sel, const QItemSelection &desel);
    void updateNamesAndRuler(const QString);
};


#endif // LINNAEO_H
