#ifndef OPENTREETHREAD_H
#define OPENTREETHREAD_H

#include <QThread>
#include <QTreeWidget>

class OpenTreeThread : public QThread
{
    Q_OBJECT
public:
    explicit OpenTreeThread(const QString& srcPath,int& fileCnt,QTreeWidget *self,QObject *parent = nullptr);
    void openProjTree(const QString& srcPath,int& fileCnt,QTreeWidget *self);

private:
    QString _srcPath;
    QTreeWidget *_self;
    QTreeWidgetItem *_root;
    int _fileCnt;
    bool _bStop;

protected:
    void run(void) override;

private:
    void recursiveProjTree(const QString& srcPath,int &fileCnt,QTreeWidget *self,QTreeWidgetItem *parent,
                           QTreeWidgetItem *root,QTreeWidgetItem* &preItem);

public slots:
    void slotCanceledProgressThread();

signals:
    void sigUpdateProgress(int);
    void sigFinishProgress(int);
};

#endif // OPENTREETHREAD_H
