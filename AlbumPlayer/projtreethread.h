#ifndef PROJTREETHREAD_H
#define PROJTREETHREAD_H

#include <QThread>
#include <QTreeWidgetItem>

class ProjTreeThread : public QThread
{
    Q_OBJECT
public:
    ProjTreeThread(const QString &srcPath,const QString &dstPath,QTreeWidgetItem* parentItem,
                   int fileCnt,QTreeWidgetItem* root,QTreeWidget *self,QObject *parent = nullptr);
    ~ProjTreeThread();

protected:
    void run() override;

private:
    void createProjTree(const QString &srcPath, const QString &dstPath, QTreeWidgetItem *parentItem,
                        int &fileCnt, QTreeWidgetItem *root, QTreeWidget *self, QTreeWidgetItem * &preItem);

    QString _srcPath;
    QString _dstPath;
    QTreeWidgetItem* _parentItem;
    int _fileCnt;
    QTreeWidgetItem* _root;
    QTreeWidget* _self;
    bool _bStop;

public slots:
    void slotCanceledProgressThread();

signals:
    void sigUpdateProgress(int);
    void sigFinishProgress(int);
};

#endif // PROJTREETHREAD_H
