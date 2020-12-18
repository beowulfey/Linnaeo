#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include "optionspanel.h"

namespace Ui {
class Workspace;
}

class Workspace : public QWidget
{
    Q_OBJECT

public:
    explicit Workspace(QWidget *parent = nullptr);
    ~Workspace();

private:
    Ui::Workspace *ui;
    void optionsPanel(QWidget *parent);
};

#endif // WORKSPACE_H
