#ifndef PICANIMATIONWIDGET_H
#define PICANIMATIONWIDGET_H
#include <QWidget>
#include <QTreeWidgetItem>
#include <QListWidgetItem>

class PicAnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PicAnimationWidget(QWidget *parent = nullptr);
    void setPixmap(QTreeWidgetItem* item);  //设置显示主Widget图片(发送信号)，并且也会设置缩略图(发送信号)
    void startAnimation();
    void stopAnimation();
    void slideNext();
    void slidePrev();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    float _factor;
    QTimer* _timer;
    QPixmap _pixmap1;
    QPixmap _pixmap2;
    QTreeWidgetItem* _curItem;
    QMap<QString,QTreeWidgetItem*> _mapItems;
    bool _bStart;
    void UpdatePixmapShow(QTreeWidgetItem*);

public slots:
    void slotUpdateClickedItem(QListWidgetItem *item);
    void slotStartOrStopSlide();

private slots:
    void slotTimeout();

signals:
    void sigUpdatePrelist(QTreeWidgetItem* item);
    void sigSelectedItem(QTreeWidgetItem* item);
    void sigStart();
    void sigStop();
};

#endif // PICANIMATIONWIDGET_H
