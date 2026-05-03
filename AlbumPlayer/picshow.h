#ifndef PICSHOW_H
#define PICSHOW_H

#include <QDialog>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QWheelEvent>

namespace Ui {
class PicShow;
}

class PicShow : public QDialog
{
    Q_OBJECT

public:
    explicit PicShow(QWidget *parent = nullptr);
    ~PicShow();

    void reloadPic();

protected:
    bool event(QEvent* e) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    Ui::PicShow *ui;
    QPropertyAnimation* _animationShowPrev; //属性动画，不透明度变化0-0.8
    QPropertyAnimation* _animationShowNext; //属性动画，不透明度变化0-0.8
    void showPrevNextBtns(bool isVisible);
    bool _bBtnsVisible; //左右箭头是否可见
    QString _selectedPath;  //当前选中图片路径
    QPixmap _pixmap;    //当前选中图片文件
    QPixmap _basePixmap;    //缩放基准图片(适配标签尺寸)
    float _zoom = 1.0f;
    QPointF _viewCenter;    //基准图中映射到标签中心的点
    void updateDisplayPixmap();

public slots:
    void slotSelectedItem(const QString& path); //更新显示的图片槽函数，并更新_selectedPath
    void slotClearSelected();    //清空显示

signals:
    void sigNextBtnClicked();   //-→键点击信号
    void sigPrevBtnClicked();   //←-键点击信号
    void sigZoomChanged(int percent);
};

#endif // PICSHOW_H
