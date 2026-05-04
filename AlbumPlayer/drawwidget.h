#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QUndoStack>
#include <QPixmap>
#include <QColor>
#include <QPointF>
#include "drawcommands.h"

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawWidget(QWidget *parent = nullptr);

    void setImage(const QPixmap& basePixmap, const QPixmap& fullPixmap,
                  const QPointF& imgPos, const QSize& viewSize);
    bool isDirty() const;
    QPixmap mergedPixmap();
    void saveToFile(const QString& path);
    float currentZoom() const;

public slots:
    void setCurrentTool(const QString& tool);
    void setCurrentColor(const QColor& color);
    void setBrushSize(int size);
    void undo();
    void redo();
    void clearAll();
    void setZoom(float zoom);

signals:
    void sigDirtyChanged(bool dirty);
    void sigZoomChanged(int percent);

protected:
    bool eventFilter(QObject* obj, QEvent* e) override;

private:
    void setupView();
    QGraphicsItem* findItemAt(const QPointF& scenePos);
    void applyMosaicAt(const QPointF& scenePos);
    void commitMosaicBlocks();
    bool isWithinImage(const QPointF& scenePos) const;

    QGraphicsView* _view;
    QGraphicsScene* _scene;
    QGraphicsPixmapItem* _baseItem;
    QGraphicsPixmapItem* _mosaicItem;
    QUndoStack* _undoStack;

    QPixmap _basePixmap;
    QPixmap _fullPixmap;
    QRectF _imgRect;
    float _zoom = 1.0f;

    QString _currentTool;
    QColor _currentColor;
    int _brushSize;
    bool _bDirty;

    bool _drawing;
    QPointF _startScenePos;
    QGraphicsItem* _tempItem;
    QPainterPath _currentPath;
    QVector<struct MosaicBlock> _pendingMosaicBlocks;
};

#endif // DRAWWIDGET_H
