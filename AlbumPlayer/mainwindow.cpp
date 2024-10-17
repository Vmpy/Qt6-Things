#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QList>
#include <QUrl>
#include "wizard.h"
#include "projtree.h"
#include "projtreewidget.h"
#include "picshow.h"
#include <QLabel>
#include <QTime>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),_mediaPlayer(new MyMediaPlayer(this))
{
    ui->setupUi(this);
    //创建文件菜单栏
    _menuFile = this->menuBar()->addMenu(tr("文件(&F)"));
    //创建项目动作
    _actCreateProj = new QAction(QIcon(":/icon/createproj.png"),tr("创建项目"),this);
    _actCreateProj->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    _menuFile->addAction(_actCreateProj);
    //打开项目动作
    _actOpenProj = new QAction(QIcon(":/icon/openproj.png"),tr("打开项目"),this);
    _actOpenProj->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    _menuFile->addAction(_actOpenProj);

    //创建设置菜单栏
    _menuSettings = this->menuBar()->addMenu(tr("设置(&S)"));
    //设置背景音乐
    _actMusic = new QAction(QIcon(":/icon/add-music.svg"),tr("导入背景音乐文件"),this);
    _actMusic->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
    _menuSettings->addAction(_actMusic);
    //选择是否播放背景音乐
    _actMusicSwitch = new QAction(QIcon(":/icon/switch-off.svg"),tr("播放背景音乐:关"),this);
    _actMusicSwitch->setCheckable(true);
    _actMusicSwitch->setChecked(false);
    _menuSettings->addAction(_actMusicSwitch);

    _playMusicMenu =  _menuSettings->addMenu(tr("播放音乐(&P)"));
    _actMusicPlay = new QAction(QIcon(":/icon/play.svg"),tr("播放"),this);
    _actMusicPause = new QAction(QIcon(":/icon/pause.svg"),tr("暂停"),this);
    _actMusicStop = new QAction(QIcon(":/icon/stop.svg"),tr("停止"),this);
    _actMusicPlayPrev = new QAction(QIcon(":/icon/prev-music.svg"),tr("上一曲"),this);
    _actMusicPlayNext = new QAction(QIcon(":/icon/next-music.svg"),tr("下一曲"),this);
    _actMusicPlayMode = new QAction(QIcon(":/icon/CurrentItemInLoop.svg"),tr("单曲循环"),this);

    _actVolumeDown = new QAction(QIcon(":/icon/volume-down.svg"),tr(""),this);
    _actVolumeUp = new QAction(QIcon(":/icon/volume-up.svg"),tr(""),this);

    _sliderVolume = new QSlider(Qt::Vertical,this);
    _sliderVolume->setInvertedAppearance(true);
    _sliderVolume->setMaximumWidth(200);
    _sliderVolume->setRange(0,100);
    _sliderVolume->setValue(100);

    _sliderDuration = new QSlider(Qt::Vertical,this);
    _sliderDuration->setMaximumWidth(300);
    _sliderDuration->setInvertedAppearance(true);
    _labelDuration = new QLabel(this);
    _labelDuration->setText("0:00");
    _labelDuration->setStyleSheet("QLabel {color:rgb(231,231,231);}");
    _labelPosition = new QLabel(this);
    _labelPosition->setText("0:00");
    _labelPosition->setStyleSheet("QLabel {color:rgb(231,231,231);}");

    connect(_mediaPlayer,&MyMediaPlayer::sigDurationChanged,this,&MainWindow::slotSetDurationSlider);
    connect(_mediaPlayer,&MyMediaPlayer::sigPositionChanged,this,&MainWindow::slotSetPositionSlider);
    connect(_sliderDuration,&QSlider::sliderReleased,[this]{
        int val = this->_sliderDuration->value();
        emit sigPostionChanged(val);
    });

    connect(this,&MainWindow::sigPostionChanged,_mediaPlayer,&MyMediaPlayer::slotSetPosition);
    ui->toolBar->addAction(_actMusic);
    ui->toolBar->addAction(_actMusicSwitch);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(_actMusicPlayPrev);
    ui->toolBar->addAction(_actMusicPlay);
    ui->toolBar->addAction(_actMusicPause);
    ui->toolBar->addAction(_actMusicStop);
    ui->toolBar->addAction(_actMusicPlayNext);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(_actMusicPlayMode);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(_actVolumeDown);
    ui->toolBar->addWidget(_sliderVolume);
    ui->toolBar->addAction(_actVolumeUp);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(_labelPosition);
    ui->toolBar->addWidget(_sliderDuration);
    ui->toolBar->addWidget(_labelDuration);
    ui->toolBar->addSeparator();

    connect(_actMusicPlayPrev,&QAction::triggered,this,&MainWindow::slotPrevMusicClicked);
    connect(_actMusicPlay,&QAction::triggered,this,&MainWindow::slotPlayClicked);
    connect(_actMusicPause,&QAction::triggered,this,&MainWindow::slotPauseClicked);
    connect(_actMusicStop,&QAction::triggered,this,&MainWindow::slotStopClicked);
    connect(_actMusicPlayNext,&QAction::triggered,this,&MainWindow::slotNextMusicClicked);
    connect(_actMusicPlayMode,&QAction::triggered,this,&MainWindow::slotMusicPlayModeClicked);
    connect(_sliderVolume,&QSlider::valueChanged,_mediaPlayer,&MyMediaPlayer::setVolume);
    connect(ui->toolBar,&QToolBar::orientationChanged,this,&MainWindow::slotSetOrientation);

    _playMusicMenu->addAction(_actMusicPlayPrev);
    _playMusicMenu->addAction(_actMusicPlay);
    _playMusicMenu->addAction(_actMusicPause);
    _playMusicMenu->addAction(_actMusicPlayNext);
    _playMusicMenu->addAction(_actMusicStop);

    //添加状态栏信息："当前播放音乐"，"播放模式","播放状态","导入音乐数量"
    _labelPlayingMusic = new QLabel(this);
    _labelPlayingMusic->setText(tr("当前曲目:")+_mediaPlayer->getPlayingName());
    _labelPlayingMusic->setMinimumWidth(150);
    ui->statusbar->addWidget(_labelPlayingMusic);
    connect(_mediaPlayer,&MyMediaPlayer::sigPlayMusicName,this,&MainWindow::slotSetPlayMusicName);
    _labelPlayingMusic->setStyleSheet("QLabel {color:rgb(231,231,231);}");

    _labelPlayingMode = new QLabel(this);
    _labelPlayingMode->setText(tr("播放模式:")+_mediaPlayer->getPlayingModeString());
    _labelPlayingMode->setMinimumWidth(100);
    connect(_mediaPlayer,&MyMediaPlayer::sigPlayMusicMode,this,&MainWindow::slotSetPlayMusicMode);
    ui->statusbar->addWidget(_labelPlayingMode);
    _labelPlayingMode->setStyleSheet("QLabel {color:rgb(231,231,231);}");

    _labelPlayingState = new QLabel(this);
    _labelPlayingState->setText(tr("播放状态:"));
    _labelPlayingState->setMinimumWidth(100);
    connect(_mediaPlayer,&MyMediaPlayer::sigPlayMusicState,this,&MainWindow::slotSetPlayMusicState);
    ui->statusbar->addWidget(_labelPlayingState);
    _labelPlayingState->setStyleSheet("QLabel {color:rgb(231,231,231);}");

    _labelPlaylistSize = new QLabel(this);
    _labelPlaylistSize->setText(tr("导入曲目数:")+QString::number(_mediaPlayer->getPlaylistSize()) + tr("首"));
    //_labelPlaylistSize->setMinimumWidth(100);
    connect(_mediaPlayer,&MyMediaPlayer::sigPlayMusicSize,this,&MainWindow::slotSetPlayMusicSize);
    ui->statusbar->addWidget(_labelPlaylistSize);
    _labelPlaylistSize->setStyleSheet("QLabel {color:rgb(231,231,231);}");

    //连接音乐操作菜单
    connect(_actMusic,&QAction::triggered,this,&MainWindow::slotSetMusic);
    connect(_actMusicSwitch,&QAction::triggered,this,&MainWindow::slotSetMusicSwitch);

    //设置窗口图标
    setWindowIcon(QIcon(":/icon/albumplayer.ico"));

    //连接信号和槽
    connect(_actCreateProj,&QAction::triggered,this,&MainWindow::slotCreateProj);
    connect(_actOpenProj,&QAction::triggered,this,&MainWindow::slotOpenProj);

    _projTree = new ProjTree(this);
    ui->projLayout->addWidget(_projTree);
    QTreeWidget* treeWidget = (dynamic_cast<ProjTree*>(_projTree))->getTreeWidget();
    ProjTreeWidget* projTreeWidget = dynamic_cast<ProjTreeWidget*>(treeWidget);
    connect(this,&MainWindow::sigOpenProj,projTreeWidget,&ProjTreeWidget::slotOpenProj);

    _picShow = new PicShow(this);
    ui->picLayout->addWidget(_picShow);
    PicShow *projPicShow = dynamic_cast<PicShow*>(_picShow);
    connect(projTreeWidget,&ProjTreeWidget::sigUpdateSelected,projPicShow,
            &PicShow::slotSelectedItem);

    connect(projPicShow,&PicShow::sigPrevBtnClicked,projTreeWidget,&ProjTreeWidget::slotPrevBtnClicked);
    connect(projPicShow,&PicShow::sigNextBtnClicked,projTreeWidget,&ProjTreeWidget::slotNextBtnClicked);
    connect(projTreeWidget,&ProjTreeWidget::sigClearSelected,projPicShow,&PicShow::slotClearSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotCreateProj(bool checked)
{
    Q_UNUSED(checked);
    Wizard wizard(this);
    wizard.setWindowTitle(tr("创建项目"));

    //连接信号和槽，把项目配置传回来todo...
    connect(&wizard,&Wizard::sigProjSetting,dynamic_cast<ProjTree*>(_projTree),&ProjTree::slotAddProjToTree);

    wizard.show();
    wizard.exec();
    //断开所有信号和槽todo...
    disconnect(&wizard);
}

void MainWindow::slotOpenProj(bool checked)
{
    Q_UNUSED(checked);

    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setWindowTitle(tr("请选择打开的项目文件夹"));
    fileDialog.setDirectory(QDir::currentPath());
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

    emit sigOpenProj(importPath);
}

void MainWindow::slotSetPlayMusicName(const QString &name)
{
    QString text = tr("当前曲目:") + name;
    _labelPlayingMusic->setText(text);
}

void MainWindow::slotSetPlayMusicMode(const QString &mode)
{
    QString text = tr("播放模式:") + mode;
    _labelPlayingMode->setText(text);
}

void MainWindow::slotSetPlayMusicState(const QString &state)
{
    QString text = tr("播放状态:") + state;
    _labelPlayingState->setText(text);
}

void MainWindow::slotSetPlayMusicSize(int size)
{
    QString text = tr("导入曲目数:") + QString::number(size);
    _labelPlaylistSize->setText(text);
}

void MainWindow::slotMusicPlayModeClicked()
{
    switch(_mediaPlayer->getPlayMode())
    {
    case MyMediaPlayerlistMode::CurrentItemInLoop:
        _mediaPlayer->setPlayMode(MyMediaPlayerlistMode::CurrentItemOnce);
        _actMusicPlayMode->setIcon(QIcon(":/icon/CurrentItemOnce.svg"));
        break;
    case MyMediaPlayerlistMode::CurrentItemOnce:
        _mediaPlayer->setPlayMode(MyMediaPlayerlistMode::Loop);
        _actMusicPlayMode->setIcon(QIcon(":/icon/Loop.svg"));
        break;
    case MyMediaPlayerlistMode::Loop:
        _mediaPlayer->setPlayMode(MyMediaPlayerlistMode::Random);
        _actMusicPlayMode->setIcon(QIcon(":/icon/Random.svg"));
        break;
    case MyMediaPlayerlistMode::Random:
        _mediaPlayer->setPlayMode(MyMediaPlayerlistMode::Sequential);
        _actMusicPlayMode->setIcon(QIcon(":/icon/Sequential.svg"));
        break;
    case MyMediaPlayerlistMode::Sequential:
        _mediaPlayer->setPlayMode(MyMediaPlayerlistMode::CurrentItemInLoop);
        _actMusicPlayMode->setIcon(QIcon(":/icon/CurrentItemInLoop.svg"));
        break;
    default:
        break;
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    PicShow *projPicShow = dynamic_cast<PicShow*>(_picShow);
    projPicShow->reloadPic();
    return QMainWindow::resizeEvent(e);
}

void MainWindow::slotSetMusic(bool checked)
{
    Q_UNUSED(checked)
    QFileDialog fileDlg;
    fileDlg.setFileMode(QFileDialog::ExistingFiles);
    fileDlg.setViewMode(QFileDialog::Detail);
    fileDlg.setDirectory(QDir::currentPath());
    fileDlg.setNameFilter("音乐文件(*.mp3 *.wav)");
    QStringList filenames;
    if(fileDlg.exec())
    {
        filenames = fileDlg.selectedFiles();
    }
    else
    {
        return;
    }
    if(filenames.isEmpty())
    {
        return;
    }
    //todo...QT6实现一个MyPlayer类去实现音乐的播放
    QList<QUrl> playlist;
    _mediaPlayer->clearPlaylist();
    for(const QString &i:filenames)
    {
        playlist.append(QUrl::fromLocalFile(i));
    }
    _mediaPlayer->setPlaylist(playlist);
    if(_mediaPlayer->getPlayerState() != QMediaPlayer::PlayingState)
    {
        _mediaPlayer->setCurrentIndex(0);
    }
    else
    {
        _mediaPlayer->setCurrentIndex(0);
    }

    //设置曲库数量
    slotSetPlayMusicSize(_mediaPlayer->getPlaylistSize());
}

void MainWindow::slotSetMusicSwitch(bool checked)
{
    _mediaPlayer->setMasterSwitch(checked); //设置总开关
    if(checked)
    {
        _actMusicSwitch->setIcon(QIcon(":/icon/switch-on.svg"));
    }
    else
    {
        _actMusicSwitch->setIcon(QIcon(":/icon/switch-off.svg"));
    }
    QString switchString = tr("播放背景音乐:");
    if(checked)
    {
        switchString += tr("开");
    }
    else
    {
        switchString += tr("关");
    }
    _actMusicSwitch->setText(switchString);
    if(_mediaPlayer->getPlaylistSize() == 0)    //当播放器播放列表中元素个数为0时选项无效，此时音乐并未导入
    {
        return;
    }
    if(!checked)
    {
        _mediaPlayer->stopPlay();
        return;
    }
    _mediaPlayer->startPlay();
}

void MainWindow::slotPlayClicked()
{
    if(!_mediaPlayer->getMasterSwitch())
    {
        return;
    }

    _mediaPlayer->startPlay();
}

void MainWindow::slotPauseClicked()
{
    if(!_mediaPlayer->getMasterSwitch())
    {
        return;
    }

    _mediaPlayer->pausePlay();
}

void MainWindow::slotStopClicked()
{
    if(!_mediaPlayer->getMasterSwitch())
    {
        return;
    }

    _mediaPlayer->stopPlayByHand();
}

void MainWindow::slotPrevMusicClicked()
{
    _mediaPlayer->stopPlayByBtn(MyMediaStopState::PrevBtn);
}

void MainWindow::slotNextMusicClicked()
{
    _mediaPlayer->stopPlayByBtn(MyMediaStopState::NextBtn);
}

void MainWindow::slotSetOrientation(Qt::Orientation newOri)
{
    _sliderVolume->setOrientation(newOri);
    _sliderDuration->setOrientation(newOri);
    if(newOri == Qt::Vertical)
    {
        _sliderVolume->setInvertedAppearance(true);
        _sliderDuration->setInvertedAppearance(true);
    }
    else
    {
        _sliderVolume->setInvertedAppearance(false);
        _sliderDuration->setInvertedAppearance(false);
    }
}

void MainWindow::slotSetPositionSlider(qint64 position)
{
    int secsPos = position/1000;

    if(!_sliderDuration->isSliderDown())
    {
        _sliderDuration->setSliderPosition(secsPos);
    }
    int HH,MM,SS;
    QString strPos;

    HH = secsPos/3600;
    MM = (secsPos - (HH*3600))/60;
    SS = (secsPos - (HH*3600) - (MM*60));
    if(HH)
    {
        strPos += QString::number(HH);
        strPos += ":";
    }
    if(MM)
    {
        if(MM < 10)
        {
            strPos += "0";
        }
        strPos += QString::number(MM);
        strPos += ":";
    }
    else
    {
        strPos += "0";
        strPos += ":";
    }
    if(SS)
    {
        if(SS < 10)
        {
            strPos += "0";
        }
        strPos += QString::number(SS);
    }
    else
    {
        strPos += "00";
    }
    if(_labelPosition->text() != strPos)
    {
        _labelPosition->setText(strPos);
    }
}

void MainWindow::slotSetDurationSlider(qint64 duration)
{
    int secsDuration = duration/1000;
    if(_sliderDuration->maximum() != secsDuration)
    {
        _sliderDuration->setRange(0,secsDuration);
        _sliderDuration->setSliderPosition(0);
    }

    int HH,MM,SS;
    QString strDuration;

    HH = secsDuration/3600;
    MM = (secsDuration - (HH*3600))/60;
    SS = (secsDuration - (HH*3600) - (MM*60));
    if(HH)
    {
        strDuration += QString::number(HH);
        strDuration += ":";
    }
    if(MM)
    {
        if(MM < 10)
        {
            strDuration += "0";
        }
        strDuration += QString::number(MM);
        strDuration += ":";
    }
    else
    {
        strDuration += "0";
        strDuration += ":";
    }
    if(SS)
    {
        if(SS < 10)
        {
            strDuration += "0";
        }
        strDuration += QString::number(SS);
    }
    else
    {
        strDuration += "00";
    }
    _labelDuration->setText(strDuration);
}
