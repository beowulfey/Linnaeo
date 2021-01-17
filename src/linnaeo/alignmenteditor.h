#ifndef ALIGNMENTEDITOR_H
#define ALIGNMENTEDITOR_H

#include "linnaeo.h"
#include "logging.h"
#include "sequence.h"
#include <QDialog>
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class AlignmentEditor;
}

class AlignmentEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AlignmentEditor(QWidget *parent = nullptr);
    ~AlignmentEditor();
    void setData(QStringList names, QStringList seqs);
    void setDocFont(QFont);
    QList<QStringList> chosenArrangement();

private slots:
    void on_alignListView_clicked(const QModelIndex &index);

private:
    Ui::AlignmentEditor *ui;
};

#endif // ALIGNMENTEDITOR_H
