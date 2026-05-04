#ifndef DRAWCOMMANDS_H
#define DRAWCOMMANDS_H

#include <QUndoCommand>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QVector>
#include <QImage>

class AddItemCommand : public QUndoCommand
{
public:
    AddItemCommand(QGraphicsItem* item, QGraphicsScene* scene, QUndoCommand* parent = nullptr);
    void undo() override;
    void redo() override;
private:
    QGraphicsItem* _item;
    QGraphicsScene* _scene;
    bool _ownsItem;
};

class RemoveItemCommand : public QUndoCommand
{
public:
    RemoveItemCommand(QGraphicsItem* item, QGraphicsScene* scene, QUndoCommand* parent = nullptr);
    void undo() override;
    void redo() override;
private:
    QGraphicsItem* _item;
    QGraphicsScene* _scene;
    bool _ownsItem;
};

struct MosaicBlock {
    QPoint pos;
    QImage originalPixels;
    int blockSize;
};

class MosaicCommand : public QUndoCommand
{
public:
    MosaicCommand(const QVector<MosaicBlock>& blocks, QGraphicsScene* scene,
                  QGraphicsPixmapItem* mosaicLayer, QUndoCommand* parent = nullptr);
    void undo() override;
    void redo() override;
private:
    QVector<MosaicBlock> _blocks;
    QGraphicsScene* _scene;
    QGraphicsPixmapItem* _mosaicLayer;
};

#endif // DRAWCOMMANDS_H
