#ifndef PROJTREEITEM_H
#define PROJTREEITEM_H

#include <QTreeWidgetItem>

class ProjTreeItem : public QTreeWidgetItem
{
public:
    ProjTreeItem(QTreeWidget* treeview, const QString &name,const QString &path, int type = Type);
    ProjTreeItem(QTreeWidgetItem* parent, const QString &name,const QString &path, QTreeWidgetItem *root,int type = Type);

    const QString& getPath();
    QTreeWidgetItem* getRoot();
    void setPrevItem(QTreeWidgetItem* prevItem);
    void setNextItem(QTreeWidgetItem* nextItem);
    ProjTreeItem* getPrevItem();
    ProjTreeItem* getNextItem();
    ProjTreeItem* getFirstPicChild();
    ProjTreeItem* getLastPicChild();
private:
    QString _name;  //文件名
    QString _path;  //现工程文件地址
    QTreeWidgetItem *_root;
    QTreeWidgetItem *_preItem;
    QTreeWidgetItem *_nextItem;
};

#endif // PROJTREEITEM_H
