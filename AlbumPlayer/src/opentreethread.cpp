#include "opentreethread.h"
#include <QDir>
#include <QFileInfoList>
#include "projtreeitem.h"
#include "const.h"


OpenTreeThread::OpenTreeThread(const QString &srcPath, int &fileCnt, QTreeWidget *self, QObject *parent):
    QThread(parent),_srcPath(srcPath),_self(self),_root(nullptr),_fileCnt(fileCnt),_bStop(false)
{

}

void OpenTreeThread::run(void)
{
    openProjTree(_srcPath,_fileCnt,_self);  //_root会在此设置

    if(_bStop)
    {
        if(_root)
        {
            //auto path = dynamic_cast<ProjTreeItem*>(_root)->getPath();
            auto index = _self->indexOfTopLevelItem(_root);

            //移除工程目录
            delete _self->takeTopLevelItem(index);

            //如果是“打开文件夹“动作中止了，本来就没有文件的复制转移就最好不删除本地文件
        }
        return;
    }

    emit sigFinishProgress(_fileCnt);
}

void OpenTreeThread::recursiveProjTree(const QString &srcPath, int &fileCnt, QTreeWidget *self,
                                       QTreeWidgetItem *parent, QTreeWidgetItem *root, QTreeWidgetItem * &preItem)
{
    QDir srcDir(srcPath);
    srcDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    srcDir.setSorting(QDir::Name|QDir::DirsFirst);
    auto filenames = srcDir.entryInfoList();

    for(const auto &i:filenames)
    {
        if(_bStop)
        {
            return;
        }
        if(i.isDir())
        {
            fileCnt++;
            emit sigUpdateProgress(fileCnt);

            auto item = new ProjTreeItem(parent,i.fileName(),i.absoluteFilePath(),root,TreeItemType::TreeItemDir);
            item->setData(0,Qt::DisplayRole,i.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/icon/dir.svg"));
            item->setData(0,Qt::ToolTipRole,i.absoluteFilePath());
            recursiveProjTree(i.absoluteFilePath(),fileCnt,self,item,root,preItem);
        }
        else
        {
            if(_bStop)
            {
                return;
            }
            QString suffix = i.completeSuffix();
            suffix = suffix.toLower();
            if(suffix != "jpg" && suffix != "jpeg" && suffix != "png")
            {
                continue;
            }

            fileCnt++;
            emit sigUpdateProgress(fileCnt);

            //图片文件注意path
            auto item = new ProjTreeItem(parent,i.fileName(),i.absoluteFilePath(),root,TreeItemType::TreeItemPic);
            item->setData(0,Qt::DisplayRole,i.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/icon/pic.png"));
            item->setData(0,Qt::ToolTipRole,i.absoluteFilePath());

            if(preItem)
            {
                auto *preProjItem = dynamic_cast<ProjTreeItem*>(preItem);
                preProjItem->setNextItem(item);
            }
            item->setPrevItem(preItem);
            preItem = item;
        }
    }
}

void OpenTreeThread::slotCanceledProgressThread()
{
    _bStop = true;
}

void OpenTreeThread::openProjTree(const QString &srcPath, int &fileCnt, QTreeWidget *self)
{
    QDir srcDir(srcPath);
    QString projName = srcDir.dirName(); //非路径名，而是目录名
    auto *item = new ProjTreeItem(self,projName,srcPath,TreeItemType::TreeItemProj);

    item->setData(0,Qt::DisplayRole,projName);
    item->setData(0,Qt::DecorationRole,QIcon(":/icon/proj.png"));
    item->setData(0,Qt::ToolTipRole,srcPath);
    _root = item;   //根节点在此设置
    QTreeWidgetItem* preItem = nullptr;
    recursiveProjTree(srcPath,fileCnt,self,item,_root,preItem);
}
