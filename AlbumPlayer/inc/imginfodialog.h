#ifndef IMGINFODIALOG_H
#define IMGINFODIALOG_H

#include <QDialog>
#include <QPixmap>

class ImgInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImgInfoDialog(const QString& path, const QPixmap& pixmap, QWidget *parent = nullptr);
};

#endif // IMGINFODIALOG_H
