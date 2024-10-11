#include "projtree.h"
#include "ui_projtree.h"
#include <QFileDialog>

ProjTree::ProjTree(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProjTree)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabel("项目列表");
    ui->treeWidget->header()->hideSection(1);

    this->setMaximumWidth(378);
    this->setMinimumWidth(378);
}

ProjTree::~ProjTree()
{
    delete ui;
}

QTreeWidget *ProjTree::getTreeWidget()
{
    return ui->treeWidget;
}

void ProjTree::slotAddProjToTree(const QString &name, const QString &path)
{
    ui->treeWidget->AddProjToTree(name,path);
}

