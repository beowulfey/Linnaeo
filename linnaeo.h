#ifndef LINNAEO_H
#define LINNAEO_H

#include <QMainWindow>
#include <QStandardItemModel>

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
    //QVector<qint64> procIds;
    QStandardItemModel *seqModel = nullptr;
    QStandardItemModel *alignModel = nullptr;

private slots:
    void on_actionNew_triggered();
    void on_actionShow_Viewer_Options_triggered(bool checked);
    void on_actionPreferences_triggered();
    void on_actionQuit_triggered();
    void expand_seqTreeView_item(const QModelIndex &index);
    void collapse_seqTreeView_item(const QModelIndex &index);
    void expand_alignTreeView_item(const QModelIndex &index);
    void collapse_alignTreeView_item(const QModelIndex &index);
};

#endif // LINNAEO_H
