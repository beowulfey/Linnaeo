#ifndef SEARCHUNIPROT_H
#define SEARCHUNIPROT_H

#include <QDialog>

namespace Ui {
class SearchUniprot;
}

class SearchUniprot : public QDialog
{
    Q_OBJECT

public:
    explicit SearchUniprot(QWidget *parent = nullptr);
    ~SearchUniprot();

private:
    Ui::SearchUniprot *ui;
};

#endif // SEARCHUNIPROT_H
