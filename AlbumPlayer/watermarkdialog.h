#ifndef WATERMARKDIALOG_H
#define WATERMARKDIALOG_H

#include <QDialog>
#include <QFont>
#include <QColor>

class QLineEdit;
class QSpinBox;
class QSlider;
class QCheckBox;
class QLabel;
class QPushButton;

struct WatermarkConfig {
    QString text = QStringLiteral("水印");
    QFont font;
    int fontSize = 48;
    int opacity = 50;       // 0-100
    bool shadowEnabled = true;
    int shadowOffsetX = 2;
    int shadowOffsetY = 2;
    int shadowBlur = 5;
    QColor shadowColor = Qt::black;
    int shadowOpacity = 80; // 0-100
};

class WatermarkDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WatermarkDialog(QWidget* parent = nullptr);
    WatermarkConfig config() const;

private:
    void setupUi();
    void updateFontLabel();

    QLineEdit* _textEdit;
    QLabel* _fontLabel;
    QFont _font;
    QSpinBox* _fontSizeSpin;
    QSlider* _opacitySlider;
    QLabel* _opacityLabel;
    QCheckBox* _shadowCheck;
    QSpinBox* _shadowOffsetX;
    QSpinBox* _shadowOffsetY;
    QSpinBox* _shadowBlur;
    QPushButton* _shadowColorBtn;
    QColor _shadowColor;
    QSlider* _shadowOpacitySlider;
    QLabel* _shadowOpacityLabel;
};

#endif // WATERMARKDIALOG_H
