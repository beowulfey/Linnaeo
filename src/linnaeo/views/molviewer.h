#ifndef MOLVIEWER_H
#define MOLVIEWER_H

#include <QDialog>
#include <QtQuick3D/qquick3d.h>

namespace Ui {
class MolViewer;
}

class MolViewer : public QDialog
{
    Q_OBJECT

public:
    explicit MolViewer(QWidget *parent = nullptr);
    ~MolViewer();

private:
    Ui::MolViewer *ui;
};

#endif // MOLVIEWER_H
