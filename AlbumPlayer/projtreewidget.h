#ifndef PROJTREEWIDGET_H
#define PROJTREEWIDGET_H

#include <QTreeWidget>
#include <QAction>
#include <QProgressDialog>
#include <memory>
#include "projtreethread.h"
#include "opentreethread.h"

class SlideShowDialog;

class ProjTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    ProjTreeWidget(QWidget *parent = nullptr);
    void AddProjToTree(const QString &name,const QString &path);

private:
    QSet<QString> _setPath;
    //创建右击菜单项
    QTreeWidgetItem *_rightBtnItem; //当前右键选择的项目
    QTreeWidgetItem *_activeItem;   //设置的活动项目，表现为字体加粗
    QTreeWidgetItem *_selectedItem; //表示选择的照片文件
    QAction *_actImport;
    QAction *_actSetStart;
    QAction *_actCloseProj;
    QAction *_actSlideShow;
    QProgressDialog *_dialogImportProgress;
    QProgressDialog *_dialogOpenProgress;
    std::shared_ptr<ProjTreeThread> _threadImportProj;
    std::shared_ptr<OpenTreeThread> _threadOpenProj;
    std::shared_ptr<SlideShowDialog> _slideShowDlg;

private slots:
    void slotItemPressed(QTreeWidgetItem *item, int column);
    void slotItemDoubleClicked(QTreeWidgetItem *item, int column);
    void slotImport();
    void slotUpdateImportProgress(int w);
    void slotFinishImportProgress(int w);
    void slotCanceledImportProgress();

    void slotSetActive();   //设置活动目录，加粗显示
    void slotCloseProj();   //右键菜单动作“移除文件”
    void slotSildeShow();   //右键设置轮播图，幻灯片

    void slotUpdateOpenProgress(int w);
    void slotFinishOpenProgress(int w);
    void slotCanceledOpenProgress();

public slots:
    void slotOpenProj(const QString& path); //处理菜单动作“打开文件”
    void slotPrevBtnClicked();  //处理←--键点击
    void slotNextBtnClicked();  //处理--→键点击

signals:
    void sigCanceledImportProgressThread();   //右键导入取消进度对话框
    void sigCanceledOpenProgressThread();   //菜单栏打开取消进度对话框
    void sigUpdateSelected(const QString&); //发出双击图片的信号，使PicShow区域显示图片
    void sigClearSelected();    //移除项目时通知PicShow空间清除显示
};

#endif // PROJTREEWIDGET_H
