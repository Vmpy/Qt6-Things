#include "projtreewidget.h"
#include "projtreeitem.h"
#include "const.h"
#include "removeprojdialog.h"
#include "slideshowdialog.h"
#include "opentreethread.h"
#include <QDir>
#include <QGuiApplication>
#include <QMenu>
#include <QIcon>
#include <QFileDialog>
#include <QProgressDialog>
#include <QHeaderView>
#include <memory>


ProjTreeWidget::ProjTreeWidget(QWidget *parent):
    QTreeWidget(parent),_rightBtnItem(nullptr),_activeItem(nullptr),_selectedItem(nullptr),
    _dialogImportProgress(nullptr),_dialogOpenProgress(nullptr),_threadImportProj(nullptr),_threadOpenProj(nullptr)
{

    connect(this,&ProjTreeWidget::itemPressed,this,&ProjTreeWidget::slotItemPressed);   //右键菜单+
    connect(this,&ProjTreeWidget::itemDoubleClicked,this,&ProjTreeWidget::slotItemDoubleClicked);
    //右键菜单项
    _actImport = new QAction(QIcon(":/icon/import.png"),tr("导入文件"),this);
    _actSetStart = new QAction(QIcon(":/icon/setstart.png"),tr("设置活动项目"),this);
    _actCloseProj = new QAction(QIcon(":/icon/closeproj.png"),tr("关闭项目"),this);
    _actSlideShow = new QAction(QIcon(":/icon/slideshow.png"),tr("幻灯片轮放"),this);

    connect(_actImport,&QAction::triggered,this,&ProjTreeWidget::slotImport);
    connect(_actSetStart,&QAction::triggered,this,&ProjTreeWidget::slotSetActive);
    connect(_actCloseProj,&QAction::triggered,this,&ProjTreeWidget::slotCloseProj);
    connect(_actSlideShow,&QAction::triggered,this,&ProjTreeWidget::slotSildeShow);
}

void ProjTreeWidget::AddProjToTree(const QString &name, const QString &path)
{
    QDir dir = QDir(path);
    QString filePath = dir.absoluteFilePath(name);
    if(_setPath.find(filePath) != _setPath.end())
    {
        return;
    }

    QDir ProjDir = QDir(filePath);

    if(!ProjDir.exists())
    {
        bool enable = ProjDir.mkpath(filePath);
        if(!enable)
        {
            return;
        }
    }

    _setPath.insert(filePath);

    auto item = new ProjTreeItem(this,name,filePath,TreeItemType::TreeItemProj);
    item->setData(0,Qt::DisplayRole,name);
    item->setData(0,Qt::DecorationRole,QIcon(":/icon/proj.png"));
    item->setData(0,Qt::ToolTipRole,filePath);
    this->addTopLevelItem(item);
}

void ProjTreeWidget::slotItemPressed(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    if(QGuiApplication::mouseButtons() == Qt::RightButton)
    {
        QMenu menu;
        int itemtype = item->type();
        if(itemtype ==  TreeItemProj)
        {
            _rightBtnItem = item;
            menu.addAction(_actImport);
            menu.addAction(_actCloseProj);
            menu.addAction(_actSetStart);
            menu.addAction(_actSlideShow);
            menu.exec(QCursor::pos());
        }
    }
}

void ProjTreeWidget::slotItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    if(QGuiApplication::mouseButtons() == Qt::LeftButton)
    {
        auto * doubleClkItem = dynamic_cast<ProjTreeItem*>(item);

        if(!doubleClkItem)
        {
            return;
        }

        int doubleClkType = doubleClkItem->type();
        if(doubleClkType == TreeItemType::TreeItemPic)
        {
            emit sigUpdateSelected(doubleClkItem->getPath());
            _selectedItem = item;
        }
    }
}

void ProjTreeWidget::slotImport()
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setWindowTitle(tr("选择导入文件目录"));

    QString path = "";
    if(!_rightBtnItem)
    {
        return;
    }

    path = dynamic_cast<ProjTreeItem*>(_rightBtnItem)->getPath();
    fileDialog.setDirectory(path);
    fileDialog.setViewMode(QFileDialog::Detail);

    QStringList filenames;
    if(fileDialog.exec())
    {
        filenames = fileDialog.selectedFiles();
    }

    if(filenames.size() <= 0)
    {
        return;
    }

    QString importPath = filenames.at(0);
    int fileCnt = 0;

    _dialogImportProgress = new QProgressDialog();

    _threadImportProj = std::make_shared<ProjTreeThread>(std::ref(importPath),std::ref(path),_rightBtnItem,fileCnt,_rightBtnItem,this,nullptr);

    connect(_threadImportProj.get(),&ProjTreeThread::sigUpdateProgress,this,&ProjTreeWidget::slotUpdateImportProgress);
    connect(_threadImportProj.get(),&ProjTreeThread::sigFinishProgress,this,&ProjTreeWidget::slotFinishImportProgress);
    connect(_dialogImportProgress,&QProgressDialog::canceled,this,&ProjTreeWidget::slotCanceledImportProgress);
    connect(this,&ProjTreeWidget::sigCanceledImportProgressThread,_threadImportProj.get(),&ProjTreeThread::slotCanceledProgressThread);

    _threadImportProj->start();
    _dialogImportProgress->setFixedWidth(PROGRESS_WIDTH);
    _dialogImportProgress->setRange(0,PROGRESS_WIDTH);
    _dialogImportProgress->exec();
}

void ProjTreeWidget::slotUpdateImportProgress(int w)
{
    if(!_dialogImportProgress)
    {
        return;
    }
    _dialogImportProgress->setValue(w % PROGRESS_MAX);
}

void ProjTreeWidget::slotFinishImportProgress(int w)
{
    Q_UNUSED(w)
    if(!_dialogImportProgress)
    {
        return;
    }
    _dialogImportProgress->setValue(PROGRESS_MAX);
    _dialogImportProgress->deleteLater();
}


void ProjTreeWidget::slotCanceledImportProgress()
{
    emit sigCanceledImportProgressThread();
    delete _dialogImportProgress;
    _dialogImportProgress = nullptr;
}


void ProjTreeWidget::slotUpdateOpenProgress(int w)
{
    if(!_dialogOpenProgress)
    {
        return;
    }
    _dialogOpenProgress->setValue(w % PROGRESS_MAX);
}

void ProjTreeWidget::slotFinishOpenProgress(int w)
{
    Q_UNUSED(w)
    if(!_dialogOpenProgress)
    {
        return;
    }
    _dialogOpenProgress->setValue(PROGRESS_MAX);
    _dialogOpenProgress->deleteLater();
}

void ProjTreeWidget::slotCanceledOpenProgress()
{
    emit sigCanceledOpenProgressThread();
    delete _dialogOpenProgress;
    _dialogOpenProgress = nullptr;
}

void ProjTreeWidget::slotSetActive()
{
    if(!_rightBtnItem)
    {
        return;
    }

    QFont activeFont;
    activeFont.setBold(false);

    if(_activeItem)
    {
        _activeItem->setFont(0,activeFont); //先取消上一个active项目的字体加粗
    }

    _activeItem = _rightBtnItem;
    activeFont.setBold(true);
    if(_activeItem)
    {
        _activeItem->setFont(0,activeFont);
    }
}

void ProjTreeWidget::slotCloseProj()
{
    RemoveProjDialog removeDialog;
    auto result = removeDialog.exec();

    if(result != QDialog::Accepted)
    {
        return;
    }

    bool bRemove = removeDialog.isRemove();
    auto indexRightBtnItemToDel = this->indexOfTopLevelItem(_rightBtnItem);
    auto * projTreeItemToDel = dynamic_cast<ProjTreeItem*>(_rightBtnItem);
    auto * selectedTreeItem = dynamic_cast<ProjTreeItem*>(_selectedItem);

    auto deletePath = projTreeItemToDel->getPath();
    _setPath.remove(deletePath);
    if(bRemove) //删除AlbumPlayer创建的文件,选择删除的话
    {
        QDir DelDir(deletePath);
        DelDir.removeRecursively();
    }
    if(projTreeItemToDel == _activeItem)
    {
        _activeItem = nullptr;
    }
    if(selectedTreeItem)    //可能没有图片文件被选中是nullptr，比如没有查看文件就关闭项目,nullptr->getRoot()会异常
    {
        if(projTreeItemToDel == selectedTreeItem->getRoot())
        {
            _selectedItem = nullptr;
            emit sigClearSelected();
        }
    }

    delete this->takeTopLevelItem(indexRightBtnItemToDel);
    _rightBtnItem = nullptr;
}

void ProjTreeWidget::slotSildeShow()
{
    if(!_rightBtnItem)
    {
        return;
    }
    auto * rightProjItem = dynamic_cast<ProjTreeItem*>(_rightBtnItem);
    auto * firstChildItem = rightProjItem->getFirstPicChild();
    auto * lastChildItem = rightProjItem->getLastPicChild();

    if(!firstChildItem || !lastChildItem)
    {
        return;
    }

    _slideShowDlg = std::make_shared<SlideShowDialog>(this,firstChildItem,lastChildItem);
    _slideShowDlg->setModal(true);
    _slideShowDlg->showMaximized();
}

//打开项目处理的槽函数
void ProjTreeWidget::slotOpenProj(const QString &path)
{
    if(_setPath.find(path) != _setPath.end())
    {
        return;
    }

    _setPath.insert(path);

    int fileCnt = 0;
    //QDir projDir(path);
    //QString projName = projDir.dirName();

    _dialogOpenProgress = new QProgressDialog();
    _threadOpenProj = std::make_shared<OpenTreeThread>(path,fileCnt,this,nullptr);

    connect(_threadOpenProj.get(),&OpenTreeThread::sigUpdateProgress,this,&ProjTreeWidget::slotUpdateOpenProgress);
    connect(_threadOpenProj.get(),&OpenTreeThread::sigFinishProgress,this,&ProjTreeWidget::slotFinishOpenProgress);
    connect(_dialogOpenProgress,&QProgressDialog::canceled,this,&ProjTreeWidget::slotCanceledOpenProgress);
    connect(this,&ProjTreeWidget::sigCanceledOpenProgressThread,_threadOpenProj.get(),&OpenTreeThread::slotCanceledProgressThread);
    _threadOpenProj->start();

    _dialogOpenProgress->setFixedWidth(PROGRESS_WIDTH);
    _dialogOpenProgress->setRange(0,PROGRESS_WIDTH);
    _dialogOpenProgress->exec();
}

void ProjTreeWidget::slotPrevBtnClicked()
{
    if(!_selectedItem)
    {
        return;
    }

    auto* curItem = dynamic_cast<ProjTreeItem*>(_selectedItem);
    auto* prevItem = curItem->getPrevItem();
    if(prevItem)
    {
        _selectedItem = prevItem;
        emit sigUpdateSelected(prevItem->getPath());
        this->setCurrentItem(_selectedItem);
    }
}

void ProjTreeWidget::slotNextBtnClicked()
{
    if(!_selectedItem)
    {
        return;
    }

    auto* curItem = dynamic_cast<ProjTreeItem*>(_selectedItem);
    auto* nextItem = curItem->getNextItem();
    if(nextItem)
    {
        _selectedItem = nextItem;
        emit sigUpdateSelected(nextItem->getPath());
        this->setCurrentItem(_selectedItem);
    }
}
