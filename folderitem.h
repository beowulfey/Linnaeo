#ifndef FOLDERITEM_H
#define FOLDERITEM_H

#include <QStandardItem>

class FolderItem : public QStandardItem
{
public:
    FolderItem();
    FolderItem(const QString &text);
    int type();

private:

};

#endif // FOLDERITEM_H
