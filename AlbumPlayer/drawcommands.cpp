#include "drawcommands.h"
#include <QPainter>

AddItemCommand::AddItemCommand(QGraphicsItem* item, QGraphicsScene* scene, QUndoCommand* parent)
    : QUndoCommand(parent), _item(item), _scene(scene), _ownsItem(true)
{
}

void AddItemCommand::undo()
{
    _scene->removeItem(_item);
}

void AddItemCommand::redo()
{
    _scene->addItem(_item);
}

RemoveItemCommand::RemoveItemCommand(QGraphicsItem* item, QGraphicsScene* scene, QUndoCommand* parent)
    : QUndoCommand(parent), _item(item), _scene(scene), _ownsItem(true)
{
}

void RemoveItemCommand::undo()
{
    _scene->addItem(_item);
}

void RemoveItemCommand::redo()
{
    _scene->removeItem(_item);
}

MosaicCommand::MosaicCommand(const QVector<MosaicBlock>& blocks, QGraphicsScene* scene,
                             QGraphicsPixmapItem* mosaicLayer, QUndoCommand* parent)
    : QUndoCommand(parent), _blocks(blocks), _scene(scene), _mosaicLayer(mosaicLayer)
{
}

void MosaicCommand::undo()
{
    QPixmap pix = _mosaicLayer->pixmap();
    QPainter painter(&pix);
    for (const auto& block : _blocks) {
        painter.drawImage(block.pos, block.originalPixels);
    }
    painter.end();
    _mosaicLayer->setPixmap(pix);
}

void MosaicCommand::redo()
{
    QPixmap pix = _mosaicLayer->pixmap();
    QPainter painter(&pix);
    for (const auto& block : _blocks) {
        QImage srcRect = block.originalPixels;
        // Replace with mean color
        QRect pixelRect(block.pos, QSize(block.blockSize, block.blockSize));
        quint64 r = 0, g = 0, b = 0;
        int cnt = srcRect.width() * srcRect.height();
        for (int y = 0; y < srcRect.height(); ++y) {
            for (int x = 0; x < srcRect.width(); ++x) {
                QRgb c = srcRect.pixel(x, y);
                r += qRed(c);
                g += qGreen(c);
                b += qBlue(c);
            }
        }
        if (cnt > 0) {
            painter.fillRect(pixelRect, QColor(r / cnt, g / cnt, b / cnt));
        }
    }
    painter.end();
    _mosaicLayer->setPixmap(pix);
}
