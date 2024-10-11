#ifndef PROJTREE_H
#define PROJTREE_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class ProjTree;
}

class ProjTree : public QDialog
{
    Q_OBJECT

public:
    explicit ProjTree(QWidget *parent = nullptr);
    ~ProjTree();
    QTreeWidget* getTreeWidget(void);

private:
    Ui::ProjTree *ui;

public slots:
    void slotAddProjToTree(const QString &name,const QString &path);
};

#endif // PROJTREE_H
