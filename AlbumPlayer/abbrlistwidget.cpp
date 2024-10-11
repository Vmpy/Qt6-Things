#include "abbrlistwidget.h"
#include "projtreeitem.h"
#include "const.h"
#include "abbrlistwidgetitem.h"
#include <QPainter>

AbbrListWidget::AbbrListWidget(QWidget *parent):QListWidget(parent),_globalNum(0)
{
    this->setViewMode(QListWidget::IconMode);
    this->setIconSize(QSize(ABBRICON_SIZE,ABBRICON_SIZE));
    this->setSpacing(5);
    this->setMovement(QListView::Static);
}

void AbbrListWidget::AddListItem(const QString &path)
{
    QPixmap srcPixmap(path);
    //-4给白线描边留空间
    srcPixmap = srcPixmap.scaled(ABBRICON_SIZE-4,ABBRICON_SIZE-4,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap dstPixmap(QSize(ABBRICON_SIZE,ABBRICON_SIZE));
    auto srcWidth = srcPixmap.width();
    auto srcHeight = srcPixmap.height();
    dstPixmap.fill(QColor(220,220,220,50));
    auto dstWidth = dstPixmap.width();
    auto dstHeight = dstPixmap.height();

    QPainter painter(&dstPixmap);

    auto x = (dstWidth-srcWidth)/2;
    auto y = (dstHeight-srcHeight)/2;
    painter.drawPixmap(x,y,srcPixmap);
    _globalNum++;

    AbbrListWidgetItem *abbrItem = new AbbrListWidgetItem(QIcon(dstPixmap),path,_globalNum,this);
    abbrItem->setSizeHint(QSize(ABBRICON_SIZE,ABBRICON_SIZE));
    this->addItem(abbrItem);
    _setItems[path] = abbrItem;
    if(_globalNum == 1)
    {
        _posOrigin = this->pos();
    }
    painter.end();
}

void AbbrListWidget::slotUpdatePrelist(QTreeWidgetItem *treeItem)
{
    if(!treeItem)
    {
        return;
    }

    auto *proj_item = dynamic_cast<ProjTreeItem*>(treeItem);
    auto path = proj_item->getPath();
    auto iter = _setItems.find(path);
    if(iter != _setItems.end())
    {
        return;
    }

    AddListItem(path);
}

void AbbrListWidget::slotSelectedItem(QTreeWidgetItem *treeItem)
{
    if(!treeItem)
    {
        return;
    }

    auto * projItem = dynamic_cast<ProjTreeItem*>(treeItem);
    auto path = projItem->getPath();
    auto iter = _setItems.find(path);

    if(iter == _setItems.end())
    {
        return;
    }

    auto *listItem = dynamic_cast<AbbrListWidgetItem*>(iter.value());

    int index = listItem->getIndex();
    if(index >= MAX_ABBRPAGEICONS)
    {
        QPoint curPos = this->pos();
        //AbbrList向左移动(index-_lastIndex)单位长
        //qDebug() << "index = " << index << "move x:" << curPos.x()-(index-_lastIndex)*ABBRITEM_SIZE << "y:" << curPos.y();
        this->move(_posOrigin.x()-(index-_lastIndex+1)*ABBRITEM_SIZE,curPos.y());
    }
    else
    {
        this->move(_posOrigin);
        _lastIndex = MAX_ABBRPAGEICONS;
    }
    this->setCurrentItem(listItem);
}
