#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QUrl>
#include <QList>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include "mymediaplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *_projTree;
    QWidget *_picShow;
    QLabel *_labelPlayingMusic;
    QLabel *_labelPlayingMode;
    QLabel *_labelPlaylistSize;
    QLabel *_labelPlayingState;
    MyMediaPlayer *_mediaPlayer;

    QMenu *_menuFile;
    QAction *_actCreateProj;
    QAction *_actOpenProj;
    QMenu *_menuSettings;
    QAction *_actMusic;
    QAction *_actMusicSwitch;
    QMenu *_playMusicMenu;
    QAction *_actMusicPlay;
    QAction *_actMusicPause;
    QAction *_actMusicStop;
    QAction *_actMusicPlayPrev;
    QAction *_actMusicPlayNext;
    QAction *_actMusicPlayMode;
    QPushButton *_btnVolumeDown;
    QPushButton *_btnVolumeUp;
    QSlider *_sliderVolume;
    QLabel *_labelVolume;
    QSlider *_sliderDuration;
    QLabel *_labelPosition;
    QLabel *_labelDuration;

private slots:
    void slotCreateProj(bool);
    void slotOpenProj(bool);
    void slotSetPlayMusicName(const QString& name);
    void slotSetPlayMusicMode(const QString& mode);
    void slotSetPlayMusicState(const QString& state);
    void slotSetPlayMusicSize(int size);
    void slotMusicPlayModeClicked();

public slots:
    void slotSetMusic(bool);
    void slotSetMusicSwitch(bool checked);

    void slotPlayClicked();
    void slotPauseClicked();
    void slotStopClicked();
    void slotPrevMusicClicked();
    void slotNextMusicClicked();

    void slotSetOrientation(Qt::Orientation newOrientation);
    void slotSetPositionSlider(qint64 position);
    void slotSetDurationSlider(qint64 duration);

    void slotVolumeTextChanged(int);


protected:
    void resizeEvent(QResizeEvent *e) override;

signals:
    void sigOpenProj(const QString&);
    void sigPostionChanged(int);
};
#endif // MAINWINDOW_H
