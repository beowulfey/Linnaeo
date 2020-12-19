#include "folderitem.h"

FolderItem::FolderItem()
{
    setData(QString("New Folder"));
    setText(QString("New Folder"));
    setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}

FolderItem::FolderItem(const QString &text)
{
    setData(text);
    setText(text);
    setData(QIcon(":/icons/ui/folder.svg"),Qt::DecorationRole);
}

int FolderItem::type()
{
    return 1000;
}
