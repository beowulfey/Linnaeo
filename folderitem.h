#ifndef FOLDERITEM_H
#define FOLDERITEM_H

#include <QStandardItem>

class FolderItem : public QStandardItem
{
    Q_OBJECT
public:
    FolderItem();
    int type();

private:

};

#endif // FOLDERITEM_H
