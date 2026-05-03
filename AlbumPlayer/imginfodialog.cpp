#include "imginfodialog.h"
#include <QFormLayout>
#include <QLabel>
#include <QFileInfo>
#include <QDateTime>
#include <QDialogButtonBox>
#include <QVBoxLayout>

static QString formatFileSize(qint64 bytes)
{
    if (bytes < 1024)
        return QString::number(bytes) + " B";
    if (bytes < 1024 * 1024)
        return QString::number(bytes / 1024.0, 'f', 1) + " KB";
    if (bytes < 1024 * 1024 * 1024)
        return QString::number(bytes / (1024.0 * 1024.0), 'f', 1) + " MB";
    return QString::number(bytes / (1024.0 * 1024.0 * 1024.0), 'f', 2) + " GB";
}

ImgInfoDialog::ImgInfoDialog(const QString& path, const QPixmap& pixmap, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("图片信息"));
    setMinimumWidth(380);

    QFileInfo fi(path);

    auto* mainLayout = new QVBoxLayout(this);
    auto* formLayout = new QFormLayout();

    formLayout->addRow(tr("文件名:"), new QLabel(fi.fileName()));
    formLayout->addRow(tr("路径:"), new QLabel(fi.absolutePath()));
    formLayout->addRow(tr("尺寸:"),
        new QLabel(QString("%1 × %2 px").arg(pixmap.width()).arg(pixmap.height())));
    formLayout->addRow(tr("文件大小:"), new QLabel(formatFileSize(fi.size())));
    formLayout->addRow(tr("格式:"), new QLabel(fi.suffix().toUpper()));
    formLayout->addRow(tr("修改日期:"),
        new QLabel(fi.lastModified().toString("yyyy-MM-dd hh:mm:ss")));

    mainLayout->addLayout(formLayout);

    auto* btnBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    mainLayout->addWidget(btnBox);
}
