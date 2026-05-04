#include "drawwidget.h"
#include "drawcommands.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QInputDialog>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>

DrawWidget::DrawWidget(QWidget *parent)
    : QWidget(parent), _currentTool("pen"), _currentColor(Qt::red), _brushSize(3),
      _bDirty(false), _drawing(false), _tempItem(nullptr)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAutoFillBackground(false);
    setupView();
}

void DrawWidget::setupView()
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    _scene = new QGraphicsScene(this);
    _view = new QGraphicsView(_scene);
    _view->setRenderHint(QPainter::Antialiasing);
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setFrameShape(QFrame::NoFrame);
    _view->setFrameStyle(QFrame::NoFrame);
    _view->setLineWidth(0);
    _view->setDragMode(QGraphicsView::NoDrag);
    _view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    _view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    _view->viewport()->installEventFilter(this);
    _view->viewport()->setMouseTracking(true);
    _view->setBackgroundBrush(Qt::transparent);
    _view->setStyleSheet("QGraphicsView { background: transparent; border: 0px; }");
    _view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    _view->setCacheMode(QGraphicsView::CacheNone);
    _view->setRenderHint(QPainter::SmoothPixmapTransform, true);
    _view->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);

    _scene->setBackgroundBrush(Qt::transparent);

    _baseItem = new QGraphicsPixmapItem;
    _baseItem->setZValue(0);
    _scene->addItem(_baseItem);

    _mosaicItem = new QGraphicsPixmapItem;
    _mosaicItem->setZValue(0.5);
    _scene->addItem(_mosaicItem);

    _undoStack = new QUndoStack(this);
    _undoStack->setUndoLimit(20);

    layout->addWidget(_view);
}

void DrawWidget::setImage(const QPixmap& basePixmap, const QPixmap& fullPixmap,
                           const QPointF& imgPos, const QSize& viewSize)
{
    _basePixmap = basePixmap;
    _fullPixmap = fullPixmap;
    _imgRect = QRectF(imgPos, _basePixmap.size());

    // Scene = viewSize (labelPic 大小), 1:1 映射
    _scene->setSceneRect(0, 0, viewSize.width(), viewSize.height());
    _view->setSceneRect(_scene->sceneRect());

    // 基准图放在 scene 中图片应在的位置
    _baseItem->setPixmap(_basePixmap);
    _baseItem->setPos(imgPos);
    _baseItem->setCacheMode(QGraphicsItem::NoCache);
    _baseItem->setTransformationMode(Qt::SmoothTransformation);

    // 马赛克层覆盖整个 view
    QPixmap mPix(viewSize);
    mPix.fill(Qt::transparent);
    _mosaicItem->setPixmap(mPix);
    _mosaicItem->setPos(0, 0);

    // 默认 1:1 视图
    _zoom = 1.0f;
    _view->setTransform(QTransform::fromScale(_zoom, _zoom));
    _scene->update();
    _view->viewport()->update();
}

float DrawWidget::currentZoom() const
{
    return _zoom;
}

void DrawWidget::setZoom(float zoom)
{
    _zoom = zoom;
    _view->setTransform(QTransform::fromScale(_zoom, _zoom));
    _scene->update();
    _view->viewport()->update();
}

bool DrawWidget::isDirty() const
{
    return _bDirty;
}

QPixmap DrawWidget::mergedPixmap()
{
    // 先在 basePixmap 分辨率渲染场景中图片区域的绘图
    QPixmap rendered(_basePixmap.size());
    rendered.fill(Qt::transparent);
    QPainter pr(&rendered);
    _scene->render(&pr, QRectF(0, 0, _basePixmap.width(), _basePixmap.height()), _imgRect);
    pr.end();

    // 将绘图叠加到全分辨率原图上
    QPixmap result(_fullPixmap.size());
    result.fill(Qt::transparent);
    QPainter p(&result);
    p.drawPixmap(0, 0, _fullPixmap);
    p.drawPixmap(0, 0, _fullPixmap.width(), _fullPixmap.height(), rendered);
    p.end();

    return result;
}

void DrawWidget::saveToFile(const QString& path)
{
    mergedPixmap().save(path);
}

void DrawWidget::setCurrentTool(const QString& tool)
{
    _currentTool = tool;
    if (_tempItem) {
        _scene->removeItem(_tempItem);
        delete _tempItem;
        _tempItem = nullptr;
    }
    _drawing = false;
    Qt::CursorShape cs = (_currentTool == "text") ? Qt::IBeamCursor :
                         (_currentTool == "mosaic" || _currentTool == "eraser") ?
                         Qt::CrossCursor : Qt::ArrowCursor;
    _view->viewport()->setCursor(cs);
}

void DrawWidget::setCurrentColor(const QColor& color)
{
    _currentColor = color;
}

void DrawWidget::setBrushSize(int size)
{
    _brushSize = size;
}

void DrawWidget::undo()
{
    _undoStack->undo();
}

void DrawWidget::redo()
{
    _undoStack->redo();
}

void DrawWidget::clearAll()
{
    QList<QGraphicsItem*> items = _scene->items();
    for (auto* item : items) {
        if (item == _baseItem || item == _mosaicItem) continue;
        _scene->removeItem(item);
        delete item;
    }
    QPixmap mPix(_scene->sceneRect().size().toSize());
    mPix.fill(Qt::transparent);
    _mosaicItem->setPixmap(mPix);
    _undoStack->clear();
    if (_bDirty) {
        _bDirty = false;
        emit sigDirtyChanged(false);
    }
}

bool DrawWidget::isWithinImage(const QPointF& scenePos) const
{
    return _imgRect.contains(scenePos);
}

QGraphicsItem* DrawWidget::findItemAt(const QPointF& scenePos)
{
    QList<QGraphicsItem*> items = _scene->items(scenePos, Qt::IntersectsItemShape,
                                                  Qt::DescendingOrder);
    for (auto* item : items) {
        if (item != _baseItem && item != _mosaicItem)
            return item;
    }
    return nullptr;
}

void DrawWidget::applyMosaicAt(const QPointF& scenePos)
{
    if (!isWithinImage(scenePos)) return;

    // 将 scene 坐标转为 basePixmap 本地坐标
    QPointF local = scenePos - _imgRect.topLeft();
    const int BS = qMax(4, _brushSize * 3);
    int x = ((int)local.x() / BS) * BS;
    int y = ((int)local.y() / BS) * BS;
    QRect blockRect(x, y, BS, BS);
    blockRect = blockRect.intersected(_basePixmap.rect());
    if (blockRect.isEmpty()) return;

    // Scene 坐标的方块位置
    QPoint sceneBlockPos((int)_imgRect.x() + blockRect.x(),
                         (int)_imgRect.y() + blockRect.y());

    MosaicBlock mb;
    mb.pos = sceneBlockPos;
    mb.blockSize = BS;
    mb.originalPixels = _basePixmap.copy(blockRect).toImage();

    for (const auto& b : _pendingMosaicBlocks) {
        if (b.pos == mb.pos) return;
    }
    _pendingMosaicBlocks.append(mb);

    QImage srcImg = _basePixmap.copy(blockRect).toImage();
    quint64 r = 0, g = 0, b = 0;
    int cnt = srcImg.width() * srcImg.height();
    for (int py = 0; py < srcImg.height(); ++py)
        for (int px = 0; px < srcImg.width(); ++px) {
            QRgb c = srcImg.pixel(px, py);
            r += qRed(c); g += qGreen(c); b += qBlue(c);
        }
    QColor meanColor(r / cnt, g / cnt, b / cnt);

    QPixmap mPix = _mosaicItem->pixmap();
    QPainter mp(&mPix);
    mp.fillRect(QRect(sceneBlockPos, QSize(BS, BS)), meanColor);
    mp.end();
    _mosaicItem->setPixmap(mPix);
}

void DrawWidget::commitMosaicBlocks()
{
    if (_pendingMosaicBlocks.isEmpty()) return;
    _undoStack->push(new MosaicCommand(_pendingMosaicBlocks, _scene, _mosaicItem));
    _pendingMosaicBlocks.clear();
    _bDirty = true;
    emit sigDirtyChanged(true);
}

bool DrawWidget::eventFilter(QObject* obj, QEvent* e)
{
    if (obj != _view->viewport())
        return QWidget::eventFilter(obj, e);

    // 滚轮缩放
    if (e->type() == QEvent::Wheel) {
        auto* we = static_cast<QWheelEvent*>(e);
        float delta = we->angleDelta().y() > 0 ? 1.15f : 1.0f / 1.15f;
        _zoom = qBound(0.1f, _zoom * delta, 10.0f);
        _view->setTransform(QTransform::fromScale(_zoom, _zoom));
        _scene->update();
        _view->viewport()->update();
        emit sigZoomChanged((int)(_zoom * 100));
        return true;
    }

    if (e->type() != QEvent::MouseButtonPress &&
        e->type() != QEvent::MouseMove &&
        e->type() != QEvent::MouseButtonRelease)
        return QWidget::eventFilter(obj, e);

    auto* me = static_cast<QMouseEvent*>(e);
    QPointF sp = _view->mapToScene(me->pos());
    float z = currentZoom();

    if (e->type() == QEvent::MouseButtonPress && me->button() == Qt::LeftButton) {
        if (!isWithinImage(sp)) return true;
        _drawing = true;
        _startScenePos = sp;

        if (_currentTool == "pen") {
            _currentPath = QPainterPath();
            _currentPath.moveTo(sp);
            QPen pen(_currentColor, _brushSize / z, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            _tempItem = _scene->addPath(_currentPath, pen);
            _tempItem->setZValue(1);
        } else if (_currentTool == "rect") {
            QPen pen(_currentColor, _brushSize / z);
            _tempItem = _scene->addRect(QRectF(sp, QSizeF(0,0)), pen);
            _tempItem->setZValue(1);
        } else if (_currentTool == "ellipse") {
            QPen pen(_currentColor, _brushSize / z);
            _tempItem = _scene->addEllipse(QRectF(sp, QSizeF(0,0)), pen);
            _tempItem->setZValue(1);
        } else if (_currentTool == "text") {
            bool ok;
            QString txt = QInputDialog::getText(this, tr("输入文字"), tr("文字内容:"),
                                                 QLineEdit::Normal, "", &ok);
            if (ok && !txt.isEmpty()) {
                auto* textItem = _scene->addText(txt);
                textItem->setDefaultTextColor(_currentColor);
                textItem->setPos(sp);
                textItem->setZValue(1);
                QFont f = textItem->font();
                f.setPixelSize((int)(_brushSize * 4 / z));
                textItem->setFont(f);
                _undoStack->push(new AddItemCommand(textItem, _scene));
                _bDirty = true;
                emit sigDirtyChanged(true);
            }
            _drawing = false;
        } else if (_currentTool == "mosaic") {
            applyMosaicAt(sp);
        } else if (_currentTool == "eraser") {
            auto* item = findItemAt(sp);
            if (item) {
                _undoStack->push(new RemoveItemCommand(item, _scene));
                _bDirty = true;
                emit sigDirtyChanged(true);
            }
            QPixmap mPix = _mosaicItem->pixmap();
            QPainter mp(&mPix);
            mp.setCompositionMode(QPainter::CompositionMode_Clear);
            mp.setPen(Qt::NoPen);
            mp.setBrush(Qt::transparent);
            float r = _brushSize / z;
            mp.drawEllipse(sp, r, r);
            mp.end();
            _mosaicItem->setPixmap(mPix);
        }
        return true;
    }

    if (e->type() == QEvent::MouseMove && _drawing) {
        QPointF clampedSp = sp;
        if (!isWithinImage(sp)) {
            clampedSp.setX(qBound(_imgRect.left(), sp.x(), _imgRect.right()));
            clampedSp.setY(qBound(_imgRect.top(), sp.y(), _imgRect.bottom()));
        }

        if (_currentTool == "pen") {
            _currentPath.lineTo(clampedSp);
            auto* pathItem = dynamic_cast<QGraphicsPathItem*>(_tempItem);
            if (pathItem) pathItem->setPath(_currentPath);
        } else if (_currentTool == "rect") {
            auto* rectItem = dynamic_cast<QGraphicsRectItem*>(_tempItem);
            if (rectItem) rectItem->setRect(QRectF(_startScenePos, clampedSp).normalized());
        } else if (_currentTool == "ellipse") {
            auto* ellItem = dynamic_cast<QGraphicsEllipseItem*>(_tempItem);
            if (ellItem) ellItem->setRect(QRectF(_startScenePos, clampedSp).normalized());
        } else if (_currentTool == "mosaic") {
            applyMosaicAt(sp);
        } else if (_currentTool == "eraser") {
            if (isWithinImage(sp)) {
                auto* item = findItemAt(sp);
                if (item) {
                    _undoStack->push(new RemoveItemCommand(item, _scene));
                    _bDirty = true;
                    emit sigDirtyChanged(true);
                }
                QPixmap mPix = _mosaicItem->pixmap();
                QPainter mp(&mPix);
                mp.setCompositionMode(QPainter::CompositionMode_Clear);
                mp.setPen(Qt::NoPen);
                mp.setBrush(Qt::transparent);
                float r = _brushSize / z;
                mp.drawEllipse(sp, r, r);
                mp.end();
                _mosaicItem->setPixmap(mPix);
            }
        }
        return true;
    }

    if (e->type() == QEvent::MouseButtonRelease && me->button() == Qt::LeftButton && _drawing) {
        _drawing = false;

        if (_currentTool == "pen") {
            auto* pathItem = dynamic_cast<QGraphicsPathItem*>(_tempItem);
            if (pathItem && !_currentPath.isEmpty()) {
                _undoStack->push(new AddItemCommand(pathItem, _scene));
                _bDirty = true;
                emit sigDirtyChanged(true);
            } else if (pathItem) {
                _scene->removeItem(pathItem);
                delete pathItem;
            }
        } else if (_currentTool == "rect") {
            auto* rectItem = dynamic_cast<QGraphicsRectItem*>(_tempItem);
            QRectF r = rectItem ? rectItem->rect() : QRectF();
            if (rectItem && r.width() > 2 && r.height() > 2) {
                _undoStack->push(new AddItemCommand(rectItem, _scene));
                _bDirty = true;
                emit sigDirtyChanged(true);
            } else if (rectItem) {
                _scene->removeItem(rectItem);
                delete rectItem;
            }
        } else if (_currentTool == "ellipse") {
            auto* ellItem = dynamic_cast<QGraphicsEllipseItem*>(_tempItem);
            QRectF r = ellItem ? ellItem->rect() : QRectF();
            if (ellItem && r.width() > 2 && r.height() > 2) {
                _undoStack->push(new AddItemCommand(ellItem, _scene));
                _bDirty = true;
                emit sigDirtyChanged(true);
            } else if (ellItem) {
                _scene->removeItem(ellItem);
                delete ellItem;
            }
        } else if (_currentTool == "mosaic") {
            commitMosaicBlocks();
        }

        _tempItem = nullptr;
        _currentPath = QPainterPath();
        return true;
    }

    return QWidget::eventFilter(obj, e);
}
