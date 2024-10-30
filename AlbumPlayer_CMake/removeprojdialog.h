#ifndef REMOVEPROJDIALOG_H
#define REMOVEPROJDIALOG_H

#include <QDialog>

namespace Ui {
class RemoveProjDialog;
}

class RemoveProjDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveProjDialog(QWidget *parent = nullptr);
    ~RemoveProjDialog();
    bool isRemove(void);

private:
    Ui::RemoveProjDialog *ui;
};

#endif // REMOVEPROJDIALOG_H
