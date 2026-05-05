#include "removeprojdialog.h"
#include "ui_removeprojdialog.h"

RemoveProjDialog::RemoveProjDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveProjDialog)
{
    ui->setupUi(this);
}

RemoveProjDialog::~RemoveProjDialog()
{
    delete ui;
}

bool RemoveProjDialog::isRemove()
{
    return ui->checkBoxDeleteFile->isChecked();
}
