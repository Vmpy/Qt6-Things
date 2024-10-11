#ifndef MYMEDIAPLAYER_H
#define MYMEDIAPLAYER_H

#include <QObject>
#include <QUrl>
#include <QMediaPlayer>
#include <QList>
#include <QAudioOutput>
#include "const.h"

class MyMediaPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MyMediaPlayer(QObject *parent = nullptr);

    void setPlaylist(const QList<QUrl> &playlist);
    void clearPlaylist();
    QMediaPlayer::PlaybackState getPlayerState();
    void setPlayMode(MyMediaPlayerlistMode mode);
    MyMediaPlayerlistMode getPlayMode();
    void setCurrentIndex(int index);
    void stopPlay();
    void startPlay();
    void pausePlay();
    int getPlaylistSize();
    int getCurrentIndex();
    void setMasterSwitch(bool checked);
    bool getMasterSwitch();

    void stopPlayByHand();
    void stopPlayByBtn(MyMediaStopState btn);

    QString getPlayingName();
    QString getPlayingModeString();

private:
    QMediaPlayer *_player;
    QList<QUrl> _playlist;
    QAudioOutput *_audioOutput;
    int _currentIndex = -1;
    bool _masterSwitch = false;
    bool _stopByHand = false;
    MyMediaPlayerlistMode _playMode = MyMediaPlayerlistMode::CurrentItemInLoop;
    MyMediaStopState _stopByTreeBtn = MyMediaStopState::NormalEnd; // -1上键 0 正常停止 1 下一曲

private slots:
    void slotPlayStateChanged(QMediaPlayer::PlaybackState newState);

signals:
    void sigPlayMusicName(const QString&);  //通知状态栏标签切换曲目名称
    void sigPlayMusicMode(const QString&);  //通知状态栏标签切换播放模式名称
    void sigPlayMusicState(const QString&); //通知状态栏标签切换播放状态名称
    void sigPlayMusicSize(int); //通知状态栏切换曲库数目
};

#endif // MYMEDIAPLAYER_H