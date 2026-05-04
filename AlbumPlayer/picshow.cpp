#include "picshow.h"
#include "ui_picshow.h"
#include <QWheelEvent>
#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include "imginfodialog.h"
#include "drawwidget.h"
#include "drawtoolbar.h"

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

    setContextMenuPolicy(Qt::DefaultContextMenu);

    // 裁剪按钮容器（固定定位，不加入layout，避免影响父窗口布局）
    _cropBtnWidget = new QWidget(this);
    _cropBtnWidget->setVisible(false);
    auto* cropLayout = new QHBoxLayout(_cropBtnWidget);
    cropLayout->setContentsMargins(10, 0, 10, 10);
    _btnCropApply = new QPushButton(tr("裁剪"), _cropBtnWidget);
    _btnCropCancel = new QPushButton(tr("取消"), _cropBtnWidget);
    _btnCropApply->setFixedSize(80, 30);
    _btnCropCancel->setFixedSize(80, 30);
    cropLayout->addStretch();
    cropLayout->addWidget(_btnCropApply);
    cropLayout->addWidget(_btnCropCancel);
    cropLayout->addStretch();

    connect(_btnCropApply, &QPushButton::clicked, this, &PicShow::applyCrop);
    connect(_btnCropCancel, &QPushButton::clicked, this, &PicShow::exitCropMode);

    ui->labelPic->installEventFilter(this);
    ui->labelPic->setMouseTracking(true);
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
    if (!_bDirty)
        _pixmap.load(_selectedPath);
    QSize oldBaseSize = _basePixmap.size();
    _basePixmap = computeBasePixmap();
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

    // 裁剪模式：绘制选区遮罩
    if (_bCropping && _cropRect.isValid()) {
        // 选区外半透明遮罩
        QColor maskColor(0, 0, 0, 120);
        // 上方
        painter.fillRect(QRectF(0, 0, lw, _cropRect.top()), maskColor);
        // 下方
        painter.fillRect(QRectF(0, _cropRect.bottom(), lw, lh - _cropRect.bottom()), maskColor);
        // 左侧
        painter.fillRect(QRectF(0, _cropRect.top(), _cropRect.left(), _cropRect.height()), maskColor);
        // 右侧
        painter.fillRect(QRectF(_cropRect.right(), _cropRect.top(), lw - _cropRect.right(), _cropRect.height()), maskColor);
        // 选区边框
        QPen pen(Qt::white, 2, Qt::DashLine);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(_cropRect);
    }

    painter.end();

    ui->labelPic->setPixmap(display);
}

void PicShow::wheelEvent(QWheelEvent *event)
{
    if (_bCropping)
        return;
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
    if (_bDirty) {
        emit sigImageDirty(_selectedPath, false);
        _bDirty = false;
        _croppedPixmap = QPixmap();
    }
    _bCropping = false;
    _cropRect = QRectF();
    if (_cropBtnWidget)
        _cropBtnWidget->hide();

    // 清理绘图模式
    if (_bDrawing) {
        if (_drawWidget) { _drawWidget->deleteLater(); _drawWidget = nullptr; }
        if (_drawToolBar) { _drawToolBar->deleteLater(); _drawToolBar = nullptr; }
        _bDrawing = false;
        ui->prevBtn->setVisible(true);
        ui->nextBtn->setVisible(true);
        updateDisplayPixmap();  // 恢复 labelPic 显示
    }

    _selectedPath = path;
    if(path.isEmpty())
    {
        return;
    }

    _pixmap.load(_selectedPath);
    _basePixmap = computeBasePixmap();
    _zoom = 1.0f;
    _viewCenter = QPointF(_basePixmap.width() / 2.0f, _basePixmap.height() / 2.0f);
    updateDisplayPixmap();
    emit sigZoomChanged(100);
}

void PicShow::slotClearSelected()
{
    if (_bDirty) {
        emit sigImageDirty(_selectedPath, false);
        _bDirty = false;
        _croppedPixmap = QPixmap();
    }
    _bCropping = false;
    _cropRect = QRectF();
    if (_cropBtnWidget)
        _cropBtnWidget->hide();

    // 清理绘图模式
    if (_bDrawing) {
        if (_drawWidget) { _drawWidget->deleteLater(); _drawWidget = nullptr; }
        if (_drawToolBar) { _drawToolBar->deleteLater(); _drawToolBar = nullptr; }
        _bDrawing = false;
        ui->prevBtn->setVisible(true);
        ui->nextBtn->setVisible(true);
    }

    _selectedPath.clear();
    _pixmap = QPixmap();
    _basePixmap = QPixmap();
    _zoom = 1.0f;
    _viewCenter = QPointF(0, 0);
    ui->labelPic->clear();
    emit sigZoomChanged(100);
}

void PicShow::contextMenuEvent(QContextMenuEvent* e)
{
    if (_selectedPath.isEmpty())
        return;
    QMenu menu(this);
    QAction* actCrop = menu.addAction(tr("裁剪"));
    connect(actCrop, &QAction::triggered, this, &PicShow::enterCropMode);
    QAction* actDraw = menu.addAction(tr("进入绘图模式"));
    connect(actDraw, &QAction::triggered, this, &PicShow::enterDrawMode);
    menu.addSeparator();
    QAction* actInfo = menu.addAction(tr("图片信息"));
    connect(actInfo, &QAction::triggered, this, [this] {
        ImgInfoDialog dlg(_selectedPath, _pixmap, this);
        dlg.exec();
    });
    menu.exec(e->globalPos());
}

bool PicShow::eventFilter(QObject* obj, QEvent* e)
{
    if (_bCropping && obj == ui->labelPic) {
        auto clampPos = [&](const QPointF& pos) -> QPointF {
            QRectF ir = imageRect();
            return QPointF(qBound(ir.left(), pos.x(), ir.right()),
                           qBound(ir.top(), pos.y(), ir.bottom()));
        };
        if (e->type() == QEvent::MouseButtonPress) {
            auto* me = static_cast<QMouseEvent*>(e);
            if (me->button() == Qt::LeftButton) {
                if (!_bSelecting) {
                    // 第一次点击：设定起始点
                    _cropStartPos = clampPos(me->position());
                    _cropEndPos = _cropStartPos;
                    _bSelecting = true;
                } else {
                    // 第二次点击：确认选区
                    _cropEndPos = clampPos(me->position());
                    _cropRect = QRectF(
                        qMin(_cropStartPos.x(), _cropEndPos.x()),
                        qMin(_cropStartPos.y(), _cropEndPos.y()),
                        qAbs(_cropEndPos.x() - _cropStartPos.x()),
                        qAbs(_cropEndPos.y() - _cropStartPos.y())
                        );
                    _bSelecting = false;
                    updateDisplayPixmap();
                }
                return true;
            }
        } else if (e->type() == QEvent::MouseMove && _bSelecting) {
            auto* me = static_cast<QMouseEvent*>(e);
            _cropEndPos = clampPos(me->position());
            _cropRect = QRectF(
                qMin(_cropStartPos.x(), _cropEndPos.x()),
                qMin(_cropStartPos.y(), _cropEndPos.y()),
                qAbs(_cropEndPos.x() - _cropStartPos.x()),
                qAbs(_cropEndPos.y() - _cropStartPos.y())
                );
            updateDisplayPixmap();
            return true;
        }
    }
    return QDialog::eventFilter(obj, e);
}

void PicShow::enterCropMode()
{
    if (_selectedPath.isEmpty() || _basePixmap.isNull())
        return;

    _bCropping = true;
    _cropRect = QRectF();
    _bSelecting = false;
    if (!_bDirty)
        _pixmap.load(_selectedPath);
    _basePixmap = computeBasePixmap();
    _zoom = 1.0f;
    _viewCenter = QPointF(_basePixmap.width() / 2.0f, _basePixmap.height() / 2.0f);
    if (_cropBtnWidget) {
        // 固定定位在底部
        int h = _cropBtnWidget->sizeHint().height();
        _cropBtnWidget->setGeometry(0, height() - h, width(), h);
        _cropBtnWidget->show();
        _cropBtnWidget->raise();
    }
    updateDisplayPixmap();
    emit sigZoomChanged(100);
}

void PicShow::exitCropMode()
{
    _bCropping = false;
    _cropRect = QRectF();
    _bSelecting = false;
    if (_cropBtnWidget)
        _cropBtnWidget->hide();
    _basePixmap = computeBasePixmap();
    _zoom = 1.0f;
    _viewCenter = QPointF(_basePixmap.width() / 2.0f, _basePixmap.height() / 2.0f);
    updateDisplayPixmap();
    emit sigZoomChanged(100);
}

void PicShow::applyCrop()
{
    if (!_cropRect.isValid() || _cropRect.width() < 5 || _cropRect.height() < 5)
        return;

    QRectF cropInBase = basePixmapCropRect();
    QRect baseRect = _basePixmap.rect();
    QRect finalCrop(
        qMax(0, (int)cropInBase.x()),
        qMax(0, (int)cropInBase.y()),
        qMin((int)baseRect.width() - (int)cropInBase.x(), (int)cropInBase.width()),
        qMin((int)baseRect.height() - (int)cropInBase.y(), (int)cropInBase.height())
        );
    finalCrop = finalCrop.intersected(baseRect);

    if (finalCrop.width() < 1 || finalCrop.height() < 1)
        return;

    _croppedPixmap = _basePixmap.copy(finalCrop);
    _pixmap = _croppedPixmap;
    _basePixmap = _croppedPixmap.scaled(ui->labelPic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    _bDirty = true;
    _bCropping = false;
    _cropRect = QRectF();
    _bSelecting = false;
    if (_cropBtnWidget)
        _cropBtnWidget->hide();
    _zoom = 1.0f;
    _viewCenter = QPointF(_basePixmap.width() / 2.0f, _basePixmap.height() / 2.0f);
    updateDisplayPixmap();
    emit sigZoomChanged(100);
    emit sigImageDirty(_selectedPath, true);
}

QPointF PicShow::labelToBasePixmap(const QPointF& labelPos) const
{
    int lw = ui->labelPic->width();
    int lh = ui->labelPic->height();
    float x = (labelPos.x() - lw / 2.0f) / _zoom + _viewCenter.x();
    float y = (labelPos.y() - lh / 2.0f) / _zoom + _viewCenter.y();
    return QPointF(x, y);
}

QRectF PicShow::basePixmapCropRect() const
{
    QPointF topLeft = labelToBasePixmap(_cropRect.topLeft());
    QPointF bottomRight = labelToBasePixmap(_cropRect.bottomRight());
    return QRectF(topLeft, bottomRight);
}

QRectF PicShow::imageRect() const
{
    int lw = ui->labelPic->width();
    int lh = ui->labelPic->height();
    int bw = _basePixmap.width();
    int bh = _basePixmap.height();
    return QRectF(lw / 2.0f - _viewCenter.x() * _zoom,
                  lh / 2.0f - _viewCenter.y() * _zoom,
                  bw * _zoom,
                  bh * _zoom);
}

QPixmap PicShow::computeBasePixmap() const
{
    if (_pixmap.isNull()) return {};
    int lw = ui->labelPic->width();
    int lh = ui->labelPic->height();
    int pw = _pixmap.width();
    int ph = _pixmap.height();
    if (lw <= 0 || lh <= 0 || pw <= 0 || ph <= 0) return {};

    // 图片长宽均小于 label → 100% 原始大小
    if (pw <= lw && ph <= lh)
        return _pixmap;

    // 图片某一维超过 label → 缩放至恰好完整显示
    float scale = (pw > ph) ? (float)lw / pw : (float)lh / ph;
    return _pixmap.scaled((int)(pw * scale), (int)(ph * scale),
                          Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

bool PicShow::isImageDirty() const
{
    return _bDirty;
}

void PicShow::resizeEvent(QResizeEvent* e)
{
    QDialog::resizeEvent(e);
    if (_cropBtnWidget && _bCropping) {
        int h = _cropBtnWidget->sizeHint().height();
        _cropBtnWidget->setGeometry(0, height() - h, width(), h);
    }
    if (_drawWidget) {
        _drawWidget->setGeometry(ui->labelPic->rect());
        QRectF imgR = imageRect();
        _drawWidget->setImage(_basePixmap, _pixmap, imgR.topLeft(), ui->labelPic->size());
    }
    if (_drawToolBar) {
        int tbW = _drawToolBar->width();
        int tbH = qMin(_drawToolBar->sizeHint().height(), height() - 20);
        _drawToolBar->setGeometry(width() - tbW - 10, 10, tbW, tbH);
    }
}

void PicShow::enterDrawMode()
{
    if (_selectedPath.isEmpty() || _bDrawing)
        return;

    _bDrawing = true;

    // 创建绘图画布，覆盖整个 labelPic，透明背景，图片定位在 imageRect 位置
    QRectF imgR = imageRect();
    _drawWidget = new DrawWidget(ui->labelPic);
    _drawWidget->setGeometry(ui->labelPic->rect());
    _drawWidget->setImage(_basePixmap, _pixmap, imgR.topLeft(), ui->labelPic->size());
    _drawWidget->show();
    _drawWidget->raise();

    // 创建浮动工具栏
    _drawToolBar = new DrawToolBar(this);
    int tbW = _drawToolBar->width();
    int tbH = qMin(_drawToolBar->sizeHint().height(), height() - 20);
    _drawToolBar->setGeometry(width() - tbW - 10, 10, tbW, tbH);
    _drawToolBar->show();
    _drawToolBar->raise();

    // 连接工具栏信号
    connect(_drawToolBar, &DrawToolBar::sigToolChanged, _drawWidget, &DrawWidget::setCurrentTool);
    connect(_drawToolBar, &DrawToolBar::sigColorChanged, _drawWidget, &DrawWidget::setCurrentColor);
    connect(_drawToolBar, &DrawToolBar::sigBrushSizeChanged, _drawWidget, &DrawWidget::setBrushSize);
    connect(_drawToolBar, &DrawToolBar::sigUndo, _drawWidget, &DrawWidget::undo);
    connect(_drawToolBar, &DrawToolBar::sigRedo, _drawWidget, &DrawWidget::redo);
    connect(_drawToolBar, &DrawToolBar::sigClearAll, _drawWidget, &DrawWidget::clearAll);
    connect(_drawToolBar, &DrawToolBar::sigSave, this, [this] {
        if (_drawWidget && _drawWidget->isDirty()) {
            QMessageBox::StandardButton btn = QMessageBox::question(
                this, tr("保存绘图"), tr("是否将绘图结果保存到图片？"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if (btn == QMessageBox::Yes) {
                _pixmap = _drawWidget->mergedPixmap();
                _basePixmap = computeBasePixmap();
                _bDirty = true;
                emit sigImageDirty(_selectedPath, true);
                _drawWidget->saveToFile(_selectedPath);
            }
        }
    });
    connect(_drawToolBar, &DrawToolBar::sigExitDraw, this, &PicShow::exitDrawMode);
    connect(_drawWidget, &DrawWidget::sigZoomChanged, this, &PicShow::sigZoomChanged);

    // 隐藏浏览元素并清除 labelPic（避免背景透出原图）
    ui->labelPic->clear();
    ui->prevBtn->setVisible(false);
    ui->nextBtn->setVisible(false);
    if (_cropBtnWidget)
        _cropBtnWidget->hide();

    setFocus();
}

void PicShow::exitDrawMode()
{
    if (!_bDrawing)
        return;

    if (_drawWidget && _drawWidget->isDirty()) {
        QMessageBox::StandardButton btn = QMessageBox::question(
            this, tr("退出绘图"), tr("当前有未保存的绘图内容，是否保存？"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (btn == QMessageBox::Yes) {
            _pixmap = _drawWidget->mergedPixmap();
            _basePixmap = computeBasePixmap();
            _bDirty = true;
            emit sigImageDirty(_selectedPath, true);
            _drawWidget->saveToFile(_selectedPath);
        } else if (btn == QMessageBox::Cancel) {
            return;
        }
    }

    // 销毁绘图相关
    if (_drawWidget) {
        _drawWidget->deleteLater();
        _drawWidget = nullptr;
    }
    if (_drawToolBar) {
        _drawToolBar->deleteLater();
        _drawToolBar = nullptr;
    }

    _bDrawing = false;
    ui->prevBtn->setVisible(true);
    ui->nextBtn->setVisible(true);
    _zoom = 1.0f;
    _viewCenter = QPointF(_basePixmap.width() / 2.0f, _basePixmap.height() / 2.0f);
    updateDisplayPixmap();  // 恢复 labelPic 显示
    emit sigZoomChanged(100);
}

void PicShow::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Escape && _bDrawing) {
        exitDrawMode();
        return;
    }
    QDialog::keyPressEvent(e);
}

void PicShow::saveCroppedImage()
{
    if (!_bDirty || _croppedPixmap.isNull() || _selectedPath.isEmpty())
        return;
    _croppedPixmap.save(_selectedPath);
    _pixmap = _croppedPixmap;
    _bDirty = false;
    emit sigImageDirty(_selectedPath, false);
}
