#include "watermarkdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QFontDialog>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QPainter>

WatermarkDialog::WatermarkDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("水印设置"));
    setMinimumWidth(420);
    setupUi();
}

void WatermarkDialog::setupUi()
{
    auto* mainLayout = new QVBoxLayout(this);

    // --- Preview ---
    auto* previewLabel = new QLabel;
    previewLabel->setFixedHeight(80);
    previewLabel->setAlignment(Qt::AlignCenter);
    previewLabel->setStyleSheet("QLabel { background: #2b2b2b; border: 1px solid #555; border-radius: 4px; }");
    mainLayout->addWidget(previewLabel);

    // --- Basic settings ---
    auto* formLayout = new QFormLayout;
    formLayout->setLabelAlignment(Qt::AlignRight);

    _textEdit = new QLineEdit(QStringLiteral("水印"));
    formLayout->addRow(tr("文字内容:"), _textEdit);

    auto* fontRow = new QHBoxLayout;
    _fontLabel = new QLabel;
    _font = QFont(QStringLiteral("Microsoft YaHei"), 48);
    updateFontLabel();
    auto* fontBtn = new QPushButton(tr("选择字体..."));
    connect(fontBtn, &QPushButton::clicked, [this] {
        bool ok;
        QFont f = QFontDialog::getFont(&ok, _font, this, tr("选择水印字体"));
        if (ok) {
            _font = f;
            updateFontLabel();
        }
    });
    fontRow->addWidget(_fontLabel, 1);
    fontRow->addWidget(fontBtn);
    formLayout->addRow(tr("字体:"), fontRow);

    _fontSizeSpin = new QSpinBox;
    _fontSizeSpin->setRange(8, 500);
    _fontSizeSpin->setValue(48);
    _fontSizeSpin->setSuffix(" px");
    formLayout->addRow(tr("字号:"), _fontSizeSpin);

    _opacitySlider = new QSlider(Qt::Horizontal);
    _opacitySlider->setRange(5, 100);
    _opacitySlider->setValue(50);
    _opacityLabel = new QLabel("50%");
    _opacityLabel->setFixedWidth(40);
    auto* opacityRow = new QHBoxLayout;
    opacityRow->addWidget(_opacitySlider);
    opacityRow->addWidget(_opacityLabel);
    formLayout->addRow(tr("不透明度:"), opacityRow);

    mainLayout->addLayout(formLayout);

    // --- Shadow group ---
    auto* shadowGroup = new QGroupBox(tr("阴影"));
    auto* shadowLayout = new QFormLayout;
    shadowLayout->setLabelAlignment(Qt::AlignRight);

    _shadowCheck = new QCheckBox(tr("启用阴影"));
    _shadowCheck->setChecked(true);
    shadowLayout->addRow(QString(), _shadowCheck);

    _shadowOffsetX = new QSpinBox;
    _shadowOffsetX->setRange(-20, 20);
    _shadowOffsetX->setValue(2);
    shadowLayout->addRow(tr("水平偏移:"), _shadowOffsetX);

    _shadowOffsetY = new QSpinBox;
    _shadowOffsetY->setRange(-20, 20);
    _shadowOffsetY->setValue(2);
    shadowLayout->addRow(tr("垂直偏移:"), _shadowOffsetY);

    _shadowBlur = new QSpinBox;
    _shadowBlur->setRange(0, 30);
    _shadowBlur->setValue(5);
    shadowLayout->addRow(tr("模糊半径:"), _shadowBlur);

    _shadowColor = Qt::black;
    _shadowColorBtn = new QPushButton;
    _shadowColorBtn->setFixedSize(30, 20);
    _shadowColorBtn->setStyleSheet(
        QString("QPushButton { background-color: %1; border: 1px solid #666; }").arg(_shadowColor.name()));
    connect(_shadowColorBtn, &QPushButton::clicked, [this] {
        QColor c = QColorDialog::getColor(_shadowColor, this, tr("选择阴影颜色"));
        if (c.isValid()) {
            _shadowColor = c;
            _shadowColorBtn->setStyleSheet(
                QString("QPushButton { background-color: %1; border: 1px solid #666; }").arg(_shadowColor.name()));
        }
    });
    shadowLayout->addRow(tr("阴影颜色:"), _shadowColorBtn);

    _shadowOpacitySlider = new QSlider(Qt::Horizontal);
    _shadowOpacitySlider->setRange(10, 100);
    _shadowOpacitySlider->setValue(80);
    _shadowOpacityLabel = new QLabel("80%");
    _shadowOpacityLabel->setFixedWidth(40);
    auto* shadowOpacityRow = new QHBoxLayout;
    shadowOpacityRow->addWidget(_shadowOpacitySlider);
    shadowOpacityRow->addWidget(_shadowOpacityLabel);
    shadowLayout->addRow(tr("阴影不透明度:"), shadowOpacityRow);

    shadowGroup->setLayout(shadowLayout);
    mainLayout->addWidget(shadowGroup);

    // --- Buttons ---
    auto* btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(btnBox);

    // --- Update preview in real-time ---
    auto updatePreview = [this, previewLabel] {
        WatermarkConfig cfg = config();
        QPixmap pix(previewLabel->width(), previewLabel->height());
        pix.fill(Qt::transparent);
        QPainter p(&pix);
        QFont f = cfg.font;
        f.setPixelSize(cfg.fontSize);
        p.setFont(f);

        // Shadow
        if (cfg.shadowEnabled) {
            QColor sc = cfg.shadowColor;
            sc.setAlpha(cfg.shadowOpacity * 255 / 100);
            QPen shadowPen(sc);
            shadowPen.setWidth(cfg.shadowBlur);
            p.setPen(shadowPen);
            p.drawText(QRectF(0, 0, pix.width(), pix.height()).adjusted(
                           cfg.shadowOffsetX, cfg.shadowOffsetY,
                           cfg.shadowOffsetX, cfg.shadowOffsetY),
                       Qt::AlignCenter, cfg.text);
        }

        // Main text
        QColor tc(255, 255, 255, cfg.opacity * 255 / 100);
        p.setPen(tc);
        p.drawText(pix.rect(), Qt::AlignCenter, cfg.text);
        p.end();
        previewLabel->setPixmap(pix);
    };

    connect(_textEdit, &QLineEdit::textChanged, updatePreview);
    connect(_fontSizeSpin, QOverload<int>::of(&QSpinBox::valueChanged), updatePreview);
    connect(_opacitySlider, &QSlider::valueChanged, [this, updatePreview](int v) {
        _opacityLabel->setText(QString::number(v) + "%");
        updatePreview();
    });
    connect(_shadowCheck, &QCheckBox::toggled, updatePreview);
    connect(_shadowOffsetX, QOverload<int>::of(&QSpinBox::valueChanged), updatePreview);
    connect(_shadowOffsetY, QOverload<int>::of(&QSpinBox::valueChanged), updatePreview);
    connect(_shadowBlur, QOverload<int>::of(&QSpinBox::valueChanged), updatePreview);
    connect(_shadowOpacitySlider, &QSlider::valueChanged, [this, updatePreview](int v) {
        _shadowOpacityLabel->setText(QString::number(v) + "%");
        updatePreview();
    });
    // Re-render when shadow color changes (button click above handles style, updatePreview used externally)
    // We hook into shadowColorBtn click by wrapping it above; let's add a dedicated update
    // The preview already reads config() which has live _shadowColor, so just trigger it:
    // Actually, the button click above updates _shadowColor and button style, but doesn't trigger preview.
    // We need to add a trigger. Let's modify the shadow color button click to also updatePreview.
    // Re-read: the button click sets _shadowColor and style, no preview update. Need to add that.
    // We'll fix this by connecting the shadow color button to also fire updatePreview.
    // But the button is already connected. Let's use a different approach: disconnect and reconnect.
    // Actually, the simplest is: the preview is already connected for all controls. For shadow color,
    // we need another approach since QPushButton::clicked doesn't carry a value.
    // We'll add a separate call.

    // Reconnect shadow color button to include preview update
    _shadowColorBtn->disconnect();
    connect(_shadowColorBtn, &QPushButton::clicked, [this, updatePreview] {
        QColor c = QColorDialog::getColor(_shadowColor, this, tr("选择阴影颜色"));
        if (c.isValid()) {
            _shadowColor = c;
            _shadowColorBtn->setStyleSheet(
                QString("QPushButton { background-color: %1; border: 1px solid #666; }").arg(_shadowColor.name()));
            updatePreview();
        }
    });

    // Trigger initial preview after dialog is shown
    connect(this, &QDialog::accepted, []{}); // no-op, keep accept working
    QMetaObject::invokeMethod(this, [this, previewLabel, updatePreview] {
        // Force a size before first preview
        if (previewLabel->width() <= 0) previewLabel->setFixedWidth(width() - 20);
        updatePreview();
    }, Qt::QueuedConnection);
}

void WatermarkDialog::updateFontLabel()
{
    _fontLabel->setText(QString("%1 %2pt").arg(_font.family()).arg(_font.pointSize()));
}

WatermarkConfig WatermarkDialog::config() const
{
    WatermarkConfig cfg;
    cfg.text = _textEdit->text();
    cfg.font = _font;
    cfg.fontSize = _fontSizeSpin->value();
    cfg.opacity = _opacitySlider->value();
    cfg.shadowEnabled = _shadowCheck->isChecked();
    cfg.shadowOffsetX = _shadowOffsetX->value();
    cfg.shadowOffsetY = _shadowOffsetY->value();
    cfg.shadowBlur = _shadowBlur->value();
    cfg.shadowColor = _shadowColor;
    cfg.shadowOpacity = _shadowOpacitySlider->value();
    return cfg;
}
