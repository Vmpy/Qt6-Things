#include "picanimationwidget.h"
#include <QTimer>
#include <QPainter>
#include <QGuiApplication>
#include "projtreeitem.h"
#include "abbrlistwidgetitem.h"

PicAnimationWidget::PicAnimationWidget(QWidget *parent)
    : QWidget(parent),_factor(0.0),_curItem(nullptr),_bStart(false)
{
    _timer = new QTimer();
    _timer->stop();
    connect(_timer,&QTimer::timeout,this,&PicAnimationWidget::slotTimeout);
}

void PicAnimationWidget::setPixmap(QTreeWidgetItem *item)
{
    if(!item)
    {
        return;
    }
    ProjTreeItem *treeItem = dynamic_cast<ProjTreeItem*>(item);
    auto path = treeItem->getPath();
    _pixmap1.load(path);
    _curItem = treeItem;

    if(_mapItems.find(path) == _mapItems.end())
    {
        _mapItems[path] = treeItem;

        emit sigUpdatePrelist(item);
    }

    emit sigSelectedItem(item);

    auto *nextItem = treeItem->getNextItem();

    if(!nextItem)
    {
        return;
    }
    auto nextPath = nextItem->getPath();
    _pixmap2.load(nextPath);
    if(_mapItems.find(nextPath) == _mapItems.end())
    {
        _mapItems[nextPath] = nextItem;
        emit sigUpdatePrelist(nextItem);
    }
}

void PicAnimationWidget::startAnimation()
{
    _timer->start(30);
    _factor = 0.0f;
    _bStart = true;
    emit sigStart();
}

void PicAnimationWidget::stopAnimation()
{
    _timer->stop();
    _factor = 0.0f; //主图不透明度为1,透明度为0,完全显示
    _bStart = false;
    emit sigStop();
}

void PicAnimationWidget::paintEvent(QPaintEvent *e)
{
    if(_pixmap1.isNull())
    {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    QRect rect = this->geometry();
    int w = rect.width();
    int h = rect.height();
    _pixmap1 = _pixmap1.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    int alpha = 255*(1.0f-_factor); //不透明度根据透明因子决定,_factor为0时不透明，为1时完全透明，做出黑色渐隐遮罩
    QPixmap alphaPixmap(_pixmap1.size());
    alphaPixmap.fill(Qt::transparent);

    QPainter p1(&alphaPixmap);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0,0,_pixmap1);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p1.fillRect(_pixmap1.rect(),QColor(0,0,0,alpha));
    p1.end();

    int x = (w - _pixmap1.width())/2;
    int y = (h - _pixmap1.height())/2;
    painter.drawPixmap(x,y,alphaPixmap);

    if(_pixmap2.isNull())
    {
        return;
    }

    _pixmap2 = _pixmap2.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    alpha = 255*(_factor);
    QPixmap alphaPixmap2(_pixmap2.size());
    alphaPixmap2.fill(Qt::transparent);

    QPainter p2(&alphaPixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_Source);
    p2.drawPixmap(0,0,_pixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p2.fillRect(_pixmap2.rect(),QColor(0,0,0,alpha));
    p2.end();
    x = (w - _pixmap2.width())/2;
    y = (h - _pixmap2.height())/2;
    painter.drawPixmap(x,y,alphaPixmap2);

    painter.end();
    return QWidget::paintEvent(e);
}

//双缓冲加载指定图片
void PicAnimationWidget::UpdatePixmapShow(QTreeWidgetItem * item)
{
    if(!item)
    {
        return;
    }
    ProjTreeItem *treeItem = dynamic_cast<ProjTreeItem*>(item);
    auto path = treeItem->getPath();
    _pixmap1.load(path);
    _curItem = treeItem;
    ProjTreeItem *nextItem = treeItem->getNextItem();
    if(!nextItem)
    {
        return;
    }
    auto nextPath = nextItem->getPath();
    _pixmap2.load(nextPath);
}

void PicAnimationWidget::slotUpdateClickedItem(QListWidgetItem *item)
{
    if(QGuiApplication::mouseButtons() != Qt::LeftButton)
    {
        return;
    }

    stopAnimation();
    auto * abbrItem = dynamic_cast<AbbrListWidgetItem*>(item);
    auto path = abbrItem->getPath();
    if(path.isEmpty())
    {
        return;
    }

    auto iter = _mapItems.find(path);
    if(iter == _mapItems.end()) //找不到元素
    {
        return;
    }
    UpdatePixmapShow(iter.value());
    update();
}

void PicAnimationWidget::slotStartOrStopSlide()
{
    if(_bStart)
    {
        stopAnimation();

    }
    else
    {
        startAnimation();
    }
    update();
}

void PicAnimationWidget::slotTimeout()
{
    if(!_curItem)
    {
        stopAnimation();
        update();
        return;
    }

    _factor += 0.01f;
    if(_factor >= 1.0f)
    {
        _factor = 0.0f;
        auto *curProjItem = dynamic_cast<ProjTreeItem*>(_curItem);
        auto *nextProjItem = curProjItem->getNextItem();
        if(!nextProjItem)
        {
            stopAnimation();
            update();
            return;
        }
        setPixmap(nextProjItem);
        update();
        return;
    }
    update();
}

void PicAnimationWidget::slideNext()
{
    stopAnimation();
    if(!_curItem)
    {
        return;
    }

    auto * curProjItem = dynamic_cast<ProjTreeItem*>(_curItem);
    auto * nextProjItem = curProjItem->getNextItem();

    if(!nextProjItem)
    {
        return;
    }
    setPixmap(nextProjItem);
    update();
}

void PicAnimationWidget::slidePrev()
{
    stopAnimation();
    if(!_curItem)
    {
        return;
    }

    auto * curProjItem = dynamic_cast<ProjTreeItem*>(_curItem);
    auto * prevProjItem = curProjItem->getPrevItem();

    if(!prevProjItem)
    {
        return;
    }
    setPixmap(prevProjItem);
    update();
}
