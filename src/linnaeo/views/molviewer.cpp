#include "molviewer.h"
#include "ui_molviewer.h"
#include <QQuickView>
#include <QQuickItem>

MolViewer::MolViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MolViewer)
{
    ui->setupUi(this);
    this->setModal(false);
    QQuickView *view = new QQuickView;
    view->setSource(QUrl::fromLocalFile(":/qml/molviewer.qml"));
    this->resize(view->rootObject()->width(),view->rootObject()->height());
    view->setResizeMode(QQuickView::SizeViewToRootObject);
    QWidget *container = QWidget::createWindowContainer(view);
    ui->verticalLayout->addWidget(container);
    view->show();
}

MolViewer::~MolViewer()
{
    delete ui;
}
