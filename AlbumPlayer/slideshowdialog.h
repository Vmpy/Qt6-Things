#ifndef SLIDESHOWDIALOG_H
#define SLIDESHOWDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class SlideShowDialog;
}

class SlideShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SlideShowDialog(QWidget *parent = nullptr,QTreeWidgetItem* firstItem = nullptr,
                             QTreeWidgetItem* lastItem = nullptr);
    ~SlideShowDialog();

private:
    Ui::SlideShowDialog *ui;
    QTreeWidgetItem* _firstItem;
    QTreeWidgetItem* _lastItem;
};

#endif // SLIDESHOWDIALOG_H
