#include "picshow.h"
#include "ui_picshow.h"
#include <QWheelEvent>
#include <QPainter>

PicShow::PicShow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PicShow),_bBtnsVisible(false)
{
    ui->setupUi(this);
    ui->prevBtn->setIcons(":/icon/left-normal.svg",":/icon/left-hover.svg",":/icon/left-pressed.svg");
    ui->nextBtn->setIcons(":/icon/right-normal.svg",":/icon/right-hover.svg",":/icon/right-pressed.svg");

    //箭头按钮逐渐显示逐渐消失效果：
    QGraphicsOpacityEffect * opacityPrev = new QGraphicsOpacityEffect(this);
    opacityPrev->setOpacity(0);
    ui->prevBtn->setGraphicsEffect(opacityPrev);

    QGraphicsOpacityEffect * opacityNext = new QGraphicsOpacityEffect(this);
    opacityNext->setOpacity(0);
    ui->nextBtn->setGraphicsEffect(opacityNext);

    _animationShowPrev = new QPropertyAnimation(opacityPrev,"opacity",this);
    _animationShowPrev->setEasingCurve(QEasingCurve::OutQuad);
    _animationShowPrev->setDuration(500);
    _animationShowNext = new QPropertyAnimation(opacityNext,"opacity",this);
    _animationShowNext->setEasingCurve(QEasingCurve::OutQuad);
    _animationShowNext->setDuration(500);

    connect(ui->nextBtn,&PicButton::clicked,this,&PicShow::sigNextBtnClicked);
    connect(ui->prevBtn,&PicButton::clicked,this,&PicShow::sigPrevBtnClicked);
}

PicShow::~PicShow()
{
    delete ui;
}

void PicShow::reloadPic()
{
    if(_selectedPath.isEmpty())
    {
        return;
    }
    _pixmap.load(_selectedPath);
    QSize oldBaseSize = _basePixmap.size();
    _basePixmap = _pixmap.scaled(ui->labelPic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if (oldBaseSize.width() > 0 && oldBaseSize.height() > 0)
    {
        _viewCenter.setX(_viewCenter.x() * _basePixmap.width() / oldBaseSize.width());
        _viewCenter.setY(_viewCenter.y() * _basePixmap.height() / oldBaseSize.height());
    }
    updateDisplayPixmap();
}

bool PicShow::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::Enter:
        showPrevNextBtns(true);
        break;
    case QEvent::Leave:
        showPrevNextBtns(false);
        break;
    default:
        break;
    }

    return QDialog::event(e);
}

void PicShow::showPrevNextBtns(bool isVisible)
{
    if(!isVisible && _bBtnsVisible)
    {
        _animationShowPrev->stop();
        _animationShowPrev->setStartValue(0.8);
        _animationShowPrev->setEndValue(0);
        _animationShowPrev->start();

        _animationShowNext->stop();
        _animationShowNext->setStartValue(0.8);
        _animationShowNext->setEndValue(0);
        _animationShowNext->start();

        _bBtnsVisible = false;
    }

    if(isVisible && !_bBtnsVisible)
    {
        _animationShowPrev->stop();
        _animationShowPrev->setStartValue(0);
        _animationShowPrev->setEndValue(0.8);
        _animationShowPrev->start();

        _animationShowNext->stop();
        _animationShowNext->setStartValue(0);
        _animationShowNext->setEndValue(0.8);
        _animationShowNext->start();

        _bBtnsVisible = true;
    }
}

void PicShow::updateDisplayPixmap()
{
    if (_basePixmap.isNull())
        return;

    int lw = ui->labelPic->width();
    int lh = ui->labelPic->height();
    int bw = _basePixmap.width();
    int bh = _basePixmap.height();

    if (lw <= 0 || lh <= 0)
        return;

    QPixmap display(lw, lh);
    display.fill(Qt::transparent);

    QPainter painter(&display);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QRectF targetRect(lw / 2.0f - _viewCenter.x() * _zoom,
                      lh / 2.0f - _viewCenter.y() * _zoom,
                      bw * _zoom,
                      bh * _zoom);

    painter.drawPixmap(targetRect, _basePixmap, _basePixmap.rect());
    painter.end();

    ui->labelPic->setPixmap(display);
}

void PicShow::wheelEvent(QWheelEvent *event)
{
    if (_selectedPath.isEmpty() || _basePixmap.isNull())
    {
        event->ignore();
        return;
    }

    QPoint labelPos = ui->labelPic->mapFrom(this, event->position().toPoint());
    if (!ui->labelPic->rect().contains(labelPos))
    {
        event->ignore();
        return;
    }

    float oldZoom = _zoom;
    float delta = (event->angleDelta().y() > 0) ? 1.15f : (1.0f / 1.15f);
    float newZoom = qBound(0.1f, oldZoom * delta, 5.0f);

    if (qFuzzyCompare(oldZoom, newZoom))
        return;

    int lw = ui->labelPic->width();
    int lh = ui->labelPic->height();
    int bw = _basePixmap.width();
    int bh = _basePixmap.height();
    QPointF labelCenter(lw / 2.0f, lh / 2.0f);

    QPointF mousePos = ui->labelPic->mapFrom(this, event->position().toPoint());

    // Mouse-centered zoom: keep the base-pixmap point under cursor fixed
    _viewCenter += (mousePos - labelCenter) * (1.0f / oldZoom - 1.0f / newZoom);
    _zoom = newZoom;

    // Clamp viewCenter so the image doesn't leave gaps at edges
    float scaledW = bw * _zoom;
    float scaledH = bh * _zoom;

    if (scaledW > lw)
        _viewCenter.setX(qBound(lw / (2.0f * _zoom), _viewCenter.x(),
                                bw - lw / (2.0f * _zoom)));
    else
        _viewCenter.setX(bw / 2.0f);

    if (scaledH > lh)
        _viewCenter.setY(qBound(lh / (2.0f * _zoom), _viewCenter.y(),
                                bh - lh / (2.0f * _zoom)));
    else
        _viewCenter.setY(bh / 2.0f);

    updateDisplayPixmap();
    emit sigZoomChanged(static_cast<int>(_zoom * 100));

    event->accept();
}

//更新所显示的图片槽函数
void PicShow::slotSelectedItem(const QString &path)
{
    _selectedPath = path;
    if(path.isEmpty())
    {
        return;
    }

    _pixmap.load(_selectedPath);
    _basePixmap = _pixmap.scaled(ui->labelPic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    _zoom = 1.0f;
    _viewCenter = QPointF(_basePixmap.width() / 2.0f, _basePixmap.height() / 2.0f);
    updateDisplayPixmap();
    emit sigZoomChanged(100);
}

void PicShow::slotClearSelected()
{
    _selectedPath.clear();
    _pixmap = QPixmap();
    _basePixmap = QPixmap();
    _zoom = 1.0f;
    _viewCenter = QPointF(0, 0);
    ui->labelPic->clear();
    emit sigZoomChanged(100);
}
