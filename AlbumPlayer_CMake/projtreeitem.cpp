#include "projtreeitem.h"
#include "const.h"

ProjTreeItem::ProjTreeItem(QTreeWidget *treeview, const QString &name, const QString &path, int type):
    QTreeWidgetItem(treeview,type),_name(name),_path(path),_root(this),_preItem(nullptr),_nextItem(nullptr)
{

}

ProjTreeItem::ProjTreeItem(QTreeWidgetItem *parent, const QString &name, const QString &path, QTreeWidgetItem *root, int type):
    QTreeWidgetItem(parent,type),_name(name),_path(path),_root(root),_preItem(nullptr),_nextItem(nullptr)
{

}

const QString& ProjTreeItem::getPath()
{
    return _path;
}

QTreeWidgetItem* ProjTreeItem::getRoot()
{
    return _root;
}

void ProjTreeItem::setPrevItem(QTreeWidgetItem *prevItem)
{
    _preItem = prevItem;
}

void ProjTreeItem::setNextItem(QTreeWidgetItem *nextItem)
{
    _nextItem = nextItem;
}

ProjTreeItem *ProjTreeItem::getPrevItem()
{
    return dynamic_cast<ProjTreeItem *>(_preItem);
}

ProjTreeItem *ProjTreeItem::getNextItem()
{
    return dynamic_cast<ProjTreeItem *>(_nextItem);
}

ProjTreeItem *ProjTreeItem::getFirstPicChild()
{
    if(this->type() == TreeItemType::TreeItemPic)
    {
        return nullptr;
    }

    auto childCnt = this->childCount();
    for(int i = 0;i < childCnt;i++)
    {
        auto * firstChild = this->child(i);
        auto * firstProjChild = dynamic_cast<ProjTreeItem*>(firstChild);
        if(firstProjChild->type() == TreeItemType::TreeItemPic)
        {
            return firstProjChild;
        }

        firstChild = firstProjChild->getFirstPicChild();

        if(!firstChild)
        {
            continue;
        }
        firstProjChild = dynamic_cast<ProjTreeItem*>(firstChild);
        return firstProjChild;
    }
    return nullptr;
}

ProjTreeItem *ProjTreeItem::getLastPicChild()
{
    if(this->type() == TreeItemType::TreeItemPic)
    {
        return nullptr;
    }

    auto childCnt = this->childCount();

    for(int i = childCnt-1;i >= 0;i--)
    {
        auto * lastChild = this->child(i);
        auto * lastProjChild = dynamic_cast<ProjTreeItem*>(lastChild);
        if(lastProjChild->type() == TreeItemType::TreeItemPic)
        {
            return lastProjChild;
        }

        lastChild = lastProjChild->getLastPicChild();

        if(!lastChild)
        {
            continue;
        }
        lastProjChild = dynamic_cast<ProjTreeItem*>(lastChild);
        return lastProjChild;
    }
    return nullptr;
}

