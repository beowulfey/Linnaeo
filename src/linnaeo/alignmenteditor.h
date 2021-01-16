#ifndef ALIGNMENTEDITOR_H
#define ALIGNMENTEDITOR_H

#include <QDialog>

namespace Ui {
class AlignmentEditor;
}

class AlignmentEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AlignmentEditor(QWidget *parent = nullptr);
    ~AlignmentEditor();

private:
    Ui::AlignmentEditor *ui;
};

#endif // ALIGNMENTEDITOR_H
