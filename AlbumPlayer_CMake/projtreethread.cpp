#include "projtreethread.h"
#include <QDir>
#include "projtreeitem.h"
#include "const.h"


ProjTreeThread::ProjTreeThread(const QString &srcPath, const QString &dstPath, QTreeWidgetItem *parentItem,
                               int fileCnt, QTreeWidgetItem *root, QTreeWidget *self, QObject *parent):
    QThread(parent),_srcPath(srcPath),_dstPath(dstPath),_parentItem(parentItem),
    _fileCnt(fileCnt),_root(root),_self(self),_bStop(false)
{

}



ProjTreeThread::~ProjTreeThread()
{

}

void ProjTreeThread::run()
{
    QTreeWidgetItem* preItem = nullptr; //可以返回最后一个元素
    createProjTree(_srcPath,_dstPath,_parentItem,_fileCnt,_root,_self,preItem);

    //取消导入终止线程
    if(_bStop)
    {
        auto path = dynamic_cast<ProjTreeItem*>(_root)->getPath();
        auto index = _self->indexOfTopLevelItem(_root);
        //移除并删除工程目录
        delete _self->takeTopLevelItem(index);

        QDir dir(path);
        dir.removeRecursively();
        return;
    }

    emit sigFinishProgress(_fileCnt);
}


void ProjTreeThread::slotCanceledProgressThread()
{
    _bStop = true;
}

void ProjTreeThread::createProjTree(const QString &srcPath, const QString &dstPath, QTreeWidgetItem *parentItem,
                                    int &fileCnt, QTreeWidgetItem *root, QTreeWidget *self, QTreeWidgetItem * &preItem)
{
    if(_bStop)
    {
        return;
    }

    //在同一目录下不需要拷贝
    bool needCopy = (srcPath != dstPath);

    QDir srcDir(srcPath);
    srcDir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    srcDir.setSorting(QDir::Name|QDir::DirsFirst);
    QFileInfoList list = srcDir.entryInfoList();
    for(const auto &i:list)
    {
        if(_bStop)
        {
            return;
        }
        if(i.isDir())
        {
            fileCnt++;
            emit sigUpdateProgress(fileCnt);

            QDir dstDir = QDir(dstPath);
            QString subDstPath = dstDir.absoluteFilePath(i.fileName());
            QDir subDstDir = QDir(subDstPath);
            if(!subDstDir.exists())
            {
                bool ok = subDstDir.mkpath(subDstPath);
                if(!ok)
                {
                    continue;
                }
            }

            auto item = new ProjTreeItem(parentItem,i.fileName(),subDstPath,root,TreeItemType::TreeItemDir);
            item->setData(0,Qt::DisplayRole,i.fileName());
            item->setData(0,Qt::DecorationRole,QIcon(":/icon/dir.svg"));
            item->setData(0,Qt::ToolTipRole,subDstPath);

            createProjTree(i.absoluteFilePath(),subDstPath,item,fileCnt,root,self,preItem);
        }
        else
        {
            if(_bStop)
            {
                return;
            }
            const QString& suffix = i.completeSuffix();
            if(suffix != "jpg" && suffix != "jpeg" && suffix != "png")
            {
                continue;
            }
            fileCnt++;

            emit sigUpdateProgress(fileCnt);

            if(needCopy)
            {
                QDir dstDir = QDir(dstPath);
                QString dstFilePath = dstDir.absoluteFilePath(i.fileName());
                if(!QFile::copy(i.filePath(),dstFilePath))
                {
                    continue;
                }
                //加入Proj项目子节点
                auto * item = new ProjTreeItem(parentItem,i.fileName(),dstFilePath,root,TreeItemType::TreeItemPic);
                item->setData(0,Qt::DisplayRole,i.fileName());
                item->setData(0,Qt::DecorationRole,QIcon(":/icon/pic.png"));
                item->setData(0,Qt::ToolTipRole,dstFilePath);

                //形成双向链表结构
                if(preItem)
                {
                    auto * preProjItem = dynamic_cast<ProjTreeItem*>(preItem);
                    preProjItem->setNextItem(item);
                }
                item->setPrevItem(preItem);

                preItem = item;
            }
        }
    }
}

