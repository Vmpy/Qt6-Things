#include "mymediaplayer.h"
#include <QRandomGenerator>

MyMediaPlayer::MyMediaPlayer(QObject *parent):
    QObject(parent),_player(new QMediaPlayer(this)),_audioOutput(new QAudioOutput(this)),_volume(100)
{
    connect(_player,&QMediaPlayer::playbackStateChanged,this,
            &MyMediaPlayer::slotPlayStateChanged);
    connect(_player,&QMediaPlayer::durationChanged,this,&MyMediaPlayer::sigDurationChanged);
    connect(_player,&QMediaPlayer::positionChanged,this,&MyMediaPlayer::sigPositionChanged);

    _player->setAudioOutput(_audioOutput);
    _audioOutput->setVolume(1.0f);
}

void MyMediaPlayer::setPlaylist(const QList<QUrl> &playlist)
{
    _playlist.clear();
    _playlist = playlist;
}

void MyMediaPlayer::clearPlaylist()
{
    _playlist.clear();
}

QMediaPlayer::PlaybackState MyMediaPlayer::getPlayerState()
{
    return _player->playbackState();
}

void MyMediaPlayer::setPlayMode(MyMediaPlayerlistMode mode)
{
    _playMode = mode;
    emit sigPlayMusicMode(getPlayingModeString());
}

MyMediaPlayerlistMode MyMediaPlayer::getPlayMode()
{
    return _playMode;
}

void MyMediaPlayer::setCurrentIndex(int index)
{
    _player->stop();
    _currentIndex = index;
}

//停止播放
void MyMediaPlayer::stopPlay()
{
    if(!_player->isPlaying())
    {
        return;
    }

    if(_player->playbackState() == QMediaPlayer::PausedState)
    {
        return;
    }
    _player->stop();
    setCurrentIndex(0);
    emit sigPlayMusicState("停止播放");
}

void MyMediaPlayer::startPlay()
{
    _stopByHand = false;    //手动停止标志位失效：播放，开始时
    if(_player->isPlaying())
    {
        return;
    }
    //检测是否是暂停状态
    if(_player->playbackState() != QMediaPlayer::PausedState)
    {
        if(_currentIndex < 0)
        {
            return;
        }
        //qDebug() << "当前播放" << _playlist.at(_currentIndex);
        _player->setSource(_playlist.at(_currentIndex));
    }
    emit sigPlayMusicName(getPlayingName());
    _player->play();
    emit sigPlayMusicState(tr("正在播放"));
}

void MyMediaPlayer::pausePlay()
{
    _stopByHand = false;    //手动停止标志位失效：播放，开始时
    if(!_player->isPlaying())
    {
        return;
    }
    _player->pause();
    emit sigPlayMusicState("暂停播放");
}

int MyMediaPlayer::getPlaylistSize()
{
    return _playlist.size();
}

int MyMediaPlayer::getCurrentIndex()
{
    return _currentIndex;
}

void MyMediaPlayer::setMasterSwitch(bool checked)
{
    //1:开启音乐播放功能; 2.关闭音乐播放功能
    _masterSwitch = checked;
    _stopByHand = checked;
}

bool MyMediaPlayer::getMasterSwitch()
{
    return _masterSwitch;
}

void MyMediaPlayer::setVolume(int vol)
{
    float volf = vol*0.01f;
    _audioOutput->setVolume(volf);
    _volume = vol;
    emit sigVolumeTextChanged(_volume);
}

int MyMediaPlayer::getVolume()
{
    return _volume;
}

//在QAction“停止播放”点击之后，停止播放且设置_stopByHand = true;防止playlist进入处理自然停止继续播放槽函数
void MyMediaPlayer::stopPlayByHand()
{
    _stopByHand = true;
    _player->stop();
    setCurrentIndex(0);
    emit sigPlayMusicState("停止播放");
}

void MyMediaPlayer::stopPlayByBtn(MyMediaStopState btn)
{
    _stopByTreeBtn = btn;
    _player->stop();
    _stopByTreeBtn = MyMediaStopState::NormalEnd;
}

QString MyMediaPlayer::getPlayingName()
{
    if(_currentIndex < 0)
    {
        return QString();
    }
    QUrl curUrl = _playlist.at(_currentIndex);
    return QString::number(_currentIndex+1) + ". " + curUrl.fileName();
}

//返回播放模式名称字符串的形式
QString MyMediaPlayer::getPlayingModeString()
{
    switch(_playMode)
    {
    case MyMediaPlayerlistMode::CurrentItemInLoop:
        return  tr("单曲循环");
        break;
    case MyMediaPlayerlistMode::CurrentItemOnce:
        return  tr("单曲单次播放");
        break;
    case MyMediaPlayerlistMode::Loop:
        return  tr("列表循环");
        break;
    case MyMediaPlayerlistMode::Random:
        return  tr("列表随机播放");
        break;
    case MyMediaPlayerlistMode::Sequential:
        return  tr("列表顺序播放");
        break;
    default:
        break;
    }
    return tr("未设置");
}

//播放停止
void MyMediaPlayer::slotPlayStateChanged(QMediaPlayer::PlaybackState newState)
{
    if(_playlist.isEmpty())
    {
        return;
    }
    if(!_masterSwitch)  //总开关设置关闭时不处理StoppedState,因为此时用户在MainWindow中设置不播放音乐
    {
        return;
    }
    if(_stopByHand) //手动点击了停止
    {
        return;
    }

    if(newState == QMediaPlayer::StoppedState) //当前播放完毕
    {
        switch(_playMode)
        {
        case MyMediaPlayerlistMode::CurrentItemInLoop:
            if(_stopByTreeBtn == MyMediaStopState::PrevBtn){
                _currentIndex--;
                if(_currentIndex < 0)
                {
                    _currentIndex = _playlist.size()-1;
                }
            }
            else if(_stopByTreeBtn == MyMediaStopState::NextBtn)
            {
                _currentIndex++;
                if(_currentIndex >= _playlist.size())
                {
                    _currentIndex = 0;
                }
            }
            startPlay();
            break;
        case MyMediaPlayerlistMode::CurrentItemOnce:
            if(_stopByTreeBtn == MyMediaStopState::PrevBtn){
                _currentIndex--;
                if(_currentIndex < 0)
                {
                    _currentIndex = _playlist.size()-1;
                }
                startPlay();
            }
            else if(_stopByTreeBtn == MyMediaStopState::NextBtn)
            {
                _currentIndex++;
                if(_currentIndex >= _playlist.size())
                {
                    _currentIndex = 0;
                }
                startPlay();
            }
            break;
        case MyMediaPlayerlistMode::Loop:
            if(_stopByTreeBtn == MyMediaStopState::PrevBtn){
                _currentIndex--;
                if(_currentIndex < 0)
                {
                    _currentIndex = _playlist.size()-1;
                }
            }
            else
            {
                _currentIndex++;
                if(_currentIndex >= _playlist.size())
                {
                    _currentIndex = 0;
                }
            }
            startPlay();
            break;
        case MyMediaPlayerlistMode::Random:
            _currentIndex = QRandomGenerator::global()->bounded(0,_playlist.size()-1);
            startPlay();
            break;
        case MyMediaPlayerlistMode::Sequential:
            if(_stopByTreeBtn == MyMediaStopState::PrevBtn){
                _currentIndex--;
                if(_currentIndex < 0)
                {
                    _currentIndex = _playlist.size()-1;
                }
            }
            else if(_stopByTreeBtn == MyMediaStopState::NextBtn)
            {
                _currentIndex++;
                if(_currentIndex >= _playlist.size())
                {
                    _currentIndex = 0;
                }
            }
            startPlay();
            break;
        default:
            break;
        }
    }
}

void MyMediaPlayer::slotPositionChanged(qint64 pos)
{
    qint64 position = pos*1000;
    _player->setPosition(position);
}

void MyMediaPlayer::slotSetPosition(int pos)
{
    qint64 msPos = pos*1000;
    _player->setPosition(msPos);
}

void MyMediaPlayer::slotVolumeUpTriggered()
{
    int newVol = _volume+1;
    if(newVol > 100)
    {
        newVol = 100;
    }
    setVolume(newVol);
    emit sigSliderVolumeChanged(newVol);
}

void MyMediaPlayer::slotVolumeDownTriggered()
{
    int newVol = _volume-1;
    if(newVol < 0 )
    {
        newVol = 0;
    }
    setVolume(newVol);
    emit sigSliderVolumeChanged(newVol);
}
