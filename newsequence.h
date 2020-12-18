#ifndef NEWSEQUENCE_H
#define NEWSEQUENCE_H

#include <QDialog>

namespace Ui {
class NewSequence;
}

class NewSequence : public QDialog
{
    Q_OBJECT

public:
    explicit NewSequence(QWidget *parent = nullptr);
    ~NewSequence();

private:
    Ui::NewSequence *ui;
};

#endif // NEWSEQUENCE_H
