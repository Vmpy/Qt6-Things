#ifndef DRAWTOOLBAR_H
#define DRAWTOOLBAR_H

#include <QWidget>
#include <QColor>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QToolButton>
#include <QActionGroup>

class DrawToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit DrawToolBar(QWidget *parent = nullptr);

signals:
    void sigToolChanged(const QString& tool);
    void sigColorChanged(const QColor& color);
    void sigBrushSizeChanged(int size);
    void sigUndo();
    void sigRedo();
    void sigClearAll();
    void sigSave();
    void sigExitDraw();

private:
    void setupUi();
    void setupStyle();
    QWidget* createColorGrid();
    QWidget* createToolButtons();
    QWidget* createBrushSlider();
    QWidget* createOpButtons();

    QList<QPushButton*> _colorBtns;
    QList<QToolButton*> _toolBtns;
    QActionGroup* _toolGroup;
    QSlider* _brushSlider;
    QLabel* _brushLabel;
    QString _currentTool;
    QColor _currentColor;

    static const QList<QColor> kPresetColors;
};

#endif // DRAWTOOLBAR_H
