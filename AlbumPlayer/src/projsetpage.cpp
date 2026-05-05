#include "projsetpage.h"
#include "ui_projsetpage.h"
#include <QLineEdit>
#include <QDir>
#include <QFileDialog>

ProjSetPage::ProjSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProjSetPage)
{
    ui->setupUi(this);
    //this->setTitle();
    registerField("projName*",ui->lineEditName);
    registerField("projPath",ui->lineEditPath);

    connect(ui->lineEditName,&QLineEdit::textEdited,this,&ProjSetPage::completeChanged);
    connect(ui->lineEditPath,&QLineEdit::textEdited,this,&ProjSetPage::completeChanged);

    QString CurPath = QDir::currentPath();
    ui->lineEditPath->setText(CurPath);
    ui->lineEditPath->setCursorPosition(ui->lineEditPath->text().size());
    ui->lineEditPath->setClearButtonEnabled(true);
    ui->lineEditName->setClearButtonEnabled(true);
}

ProjSetPage::~ProjSetPage()
{
    delete ui;
}

void ProjSetPage::getProjSetting(QString &Name, QString &Path)
{
    Name = ui->lineEditName->text();
    Path = ui->lineEditPath->text();
}

bool ProjSetPage::isComplete() const
{
    if(ui->lineEditName->text() == "" || ui->lineEditPath->text() == "")
    {
        //ui->tips->setText("请输入项目名和工作目录！");
        return false;
    }

    QDir path(ui->lineEditPath->text());
    if(!path.exists())
    {
        ui->tips->setText("目录不存在！");
        return false;
    }

    QString absFilePath = path.absoluteFilePath(ui->lineEditName->text());
    QDir destDir = QDir(absFilePath);
    if(destDir.exists())
    {
        ui->tips->setText("当前项目已存在！可直接打开！");
        return false;
    }

    ui->tips->setText("");
    return QWizardPage::isComplete();
}

void ProjSetPage::on_buttonBrowse_clicked()
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setWindowTitle(tr("选择导入的文件夹"));
    QDir path = QDir::currentPath();
    fileDialog.setDirectory(path);
    fileDialog.setViewMode(QFileDialog::Detail);

    QStringList fileNameList;
    if(fileDialog.exec())
    {
        fileNameList = fileDialog.selectedFiles();
    }

    if(fileNameList.length() <= 0)
    {
        return;
    }

    ui->lineEditPath->setText(fileNameList.at(0));
}

