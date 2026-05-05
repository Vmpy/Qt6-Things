#include "drawtoolbar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QColorDialog>
#include <QGraphicsDropShadowEffect>
#include <QGroupBox>

const QList<QColor> DrawToolBar::kPresetColors = {
    Qt::black,   Qt::white,   Qt::red,     Qt::green,
    Qt::blue,    Qt::yellow,  Qt::cyan,    Qt::magenta,
    QColor(255,128,0), QColor(128,0,255), QColor(0,128,128), QColor(128,128,128)
};

DrawToolBar::DrawToolBar(QWidget *parent)
    : QWidget(parent), _currentTool("pen"), _currentColor(Qt::red)
{
    setFixedWidth(280);
    setupUi();
    setupStyle();
}

void DrawToolBar::setupUi()
{
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(8);

    // Color section
    auto* colorGroup = new QGroupBox(tr("颜色"));
    auto* colorLayout = new QVBoxLayout(colorGroup);
    colorLayout->addWidget(createColorGrid());
    auto* btnMore = new QPushButton(tr("更多颜色..."));
    connect(btnMore, &QPushButton::clicked, [this] {
        QColor c = QColorDialog::getColor(_currentColor, this, tr("选择颜色"));
        if (c.isValid()) {
            _currentColor = c;
            emit sigColorChanged(c);
        }
    });
    colorLayout->addWidget(btnMore);
    mainLayout->addWidget(colorGroup);

    // Tool buttons
    auto* toolGroup = new QGroupBox(tr("工具"));
    toolGroup->setLayout(new QVBoxLayout);
    toolGroup->layout()->addWidget(createToolButtons());
    mainLayout->addWidget(toolGroup);

    // Brush size
    auto* brushGroup = new QGroupBox(tr("笔刷大小"));
    brushGroup->setLayout(new QVBoxLayout);
    brushGroup->layout()->addWidget(createBrushSlider());
    mainLayout->addWidget(brushGroup);

    // Operation buttons
    mainLayout->addWidget(createOpButtons());
    mainLayout->addStretch();
}

QWidget* DrawToolBar::createColorGrid()
{
    auto* grid = new QWidget;
    auto* layout = new QGridLayout(grid);
    layout->setSpacing(4);
    layout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < kPresetColors.size(); ++i) {
        auto* btn = new QPushButton;
        btn->setFixedSize(24, 24);
        btn->setStyleSheet(QString(
            "QPushButton { background-color: %1; border: 2px solid #555; border-radius: 3px; }"
            "QPushButton:hover { border-color: #aaa; }"
        ).arg(kPresetColors[i].name()));
        connect(btn, &QPushButton::clicked, [this, i] {
            _currentColor = kPresetColors[i];
            emit sigColorChanged(_currentColor);
        });
        layout->addWidget(btn, i / 4, i % 4);
        _colorBtns.append(btn);
    }
    return grid;
}

QWidget* DrawToolBar::createToolButtons()
{
    auto* w = new QWidget;
    auto* layout = new QGridLayout(w);
    layout->setSpacing(4);
    layout->setContentsMargins(0, 0, 0, 0);

    _toolGroup = new QActionGroup(this);
    _toolGroup->setExclusive(true);

    struct ToolDef {
        QString id, text;
    };
    QList<ToolDef> tools = {
        {"pen",    tr("画笔")},
        {"rect",   tr("矩形")},
        {"ellipse",tr("椭圆")},
        {"text",   tr("文字")},
        {"mosaic", tr("马赛克")},
        {"eraser", tr("橡皮")},
        {"grab",   tr("抓取")},
        {"watermark", tr("水印")},
    };

    for (int i = 0; i < tools.size(); ++i) {
        auto* btn = new QToolButton;
        btn->setText(tools[i].text);
        btn->setCheckable(true);
        btn->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btn->setMinimumSize(80, 32);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (i == 0) btn->setChecked(true);

        connect(btn, &QToolButton::clicked, [this, btn, id = tools[i].id] {
            for (auto* b : _toolBtns) b->setChecked(b == btn);
            _currentTool = id;
            emit sigToolChanged(id);
        });
        _toolBtns.append(btn);
        layout->addWidget(btn, i / 2, i % 2);
    }
    return w;
}

QWidget* DrawToolBar::createBrushSlider()
{
    auto* w = new QWidget;
    auto* layout = new QHBoxLayout(w);
    layout->setContentsMargins(0, 0, 0, 0);

    _brushSlider = new QSlider(Qt::Horizontal);
    _brushSlider->setRange(1, 30);
    _brushSlider->setValue(3);
    _brushLabel = new QLabel("3 px");
    _brushLabel->setFixedWidth(40);
    _brushLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(_brushSlider, &QSlider::valueChanged, [this](int v) {
        _brushLabel->setText(QString::number(v) + " px");
        emit sigBrushSizeChanged(v);
    });

    layout->addWidget(new QLabel(tr("粗细:")));
    layout->addWidget(_brushSlider);
    layout->addWidget(_brushLabel);
    return w;
}

QWidget* DrawToolBar::createOpButtons()
{
    auto* w = new QWidget;
    auto* layout = new QGridLayout(w);
    layout->setSpacing(4);
    layout->setContentsMargins(0, 0, 0, 0);

    auto makeBtn = [&](const QString& text, auto slot) {
        auto* btn = new QPushButton(text);
        connect(btn, &QPushButton::clicked, slot);
        return btn;
    };

    layout->addWidget(makeBtn(tr("撤销"), [this] { emit sigUndo(); }), 0, 0);
    layout->addWidget(makeBtn(tr("重做"), [this] { emit sigRedo(); }), 0, 1);
    layout->addWidget(makeBtn(tr("清空"), [this] { emit sigClearAll(); }), 1, 0);
    layout->addWidget(makeBtn(tr("保存"), [this] { emit sigSave(); }), 1, 1);

    auto* exitBtn = new QPushButton(tr("退出绘图模式"));
    exitBtn->setStyleSheet("QPushButton { background-color: #8B0000; color: white; }"
                           "QPushButton:hover { background-color: #A52A2A; }");
    connect(exitBtn, &QPushButton::clicked, [this] { emit sigExitDraw(); });
    layout->addWidget(exitBtn, 2, 0, 1, 2);

    return w;
}

void DrawToolBar::setupStyle()
{
    setStyleSheet(R"(
        DrawToolBar {
            background-color: rgb(47,48,47);
            border: 1px solid #555;
            border-radius: 6px;
        }
        QGroupBox {
            color: rgb(231,231,231);
            border: 1px solid #555;
            border-radius: 4px;
            margin-top: 8px;
            padding-top: 14px;
            font-weight: bold;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 4px;
        }
        QPushButton {
            background-color: rgb(60,60,60);
            color: rgb(231,231,231);
            border: 1px solid #666;
            border-radius: 3px;
            padding: 4px 8px;
            min-height: 24px;
        }
        QPushButton:hover {
            background-color: rgb(80,80,80);
            border-color: #999;
        }
        QPushButton:pressed {
            background-color: rgb(39,96,154);
        }
        QToolButton {
            background-color: rgb(60,60,60);
            color: rgb(231,231,231);
            border: 1px solid #666;
            border-radius: 3px;
            padding: 4px 8px;
        }
        QToolButton:hover {
            background-color: rgb(80,80,80);
            border-color: #999;
        }
        QToolButton:checked {
            background-color: rgb(39,96,154);
            border-color: #7AB8FF;
        }
        QSlider::groove:horizontal {
            height: 6px;
            background: #555;
            border-radius: 3px;
        }
        QSlider::handle:horizontal {
            background: #ccc;
            width: 12px;
            margin: -3px 0;
            border-radius: 6px;
        }
        QSlider::sub-page:horizontal {
            background: rgb(39,96,154);
            border-radius: 3px;
        }
        QLabel {
            color: rgb(231,231,231);
        }
    )");

    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 180));
    shadow->setOffset(0, 4);
    setGraphicsEffect(shadow);
}
