#include "picshow.h"
#include "ui_picshow.h"

PicShow::PicShow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PicShow),_bBtnsVisible(false)
{
    ui->setupUi(this);
    ui->prevBtn->setIcons(":/icon/left-normal.svg",":/icon/left-hover.svg",":/icon/left-pressed.svg");
    ui->nextBtn->setIcons(":/icon/right-normal.svg",":/icon/right-hover.svg",":/icon/right-pressed.svg");

    //箭头按钮逐渐显示逐渐消失效果：
    QGraphicsOpacityEffect * opacityPrev = new QGraphicsOpacityEffect(this);
    opacityPrev->setOpacity(0);
    ui->prevBtn->setGraphicsEffect(opacityPrev);

    QGraphicsOpacityEffect * opacityNext = new QGraphicsOpacityEffect(this);
    opacityNext->setOpacity(0);
    ui->nextBtn->setGraphicsEffect(opacityNext);

    _animationShowPrev = new QPropertyAnimation(opacityPrev,"opacity",this);
    _animationShowPrev->setEasingCurve(QEasingCurve::OutQuad);
    _animationShowPrev->setDuration(500);
    _animationShowNext = new QPropertyAnimation(opacityNext,"opacity",this);
    _animationShowNext->setEasingCurve(QEasingCurve::OutQuad);
    _animationShowNext->setDuration(500);

    connect(ui->nextBtn,&PicButton::clicked,this,&PicShow::sigNextBtnClicked);
    connect(ui->prevBtn,&PicButton::clicked,this,&PicShow::sigPrevBtnClicked);
}

PicShow::~PicShow()
{
    delete ui;
}

void PicShow::reloadPic()
{
    if(_selectedPath.isEmpty())
    {
        return;
    }
    _pixmap.load(_selectedPath);
    _pixmap = _pixmap.scaled(ui->labelPic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->labelPic->setPixmap(_pixmap);
}

bool PicShow::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::Enter:
        showPrevNextBtns(true);
        break;
    case QEvent::Leave:
        showPrevNextBtns(false);
        break;
    default:
        break;
    }

    return QDialog::event(e);
}

void PicShow::showPrevNextBtns(bool isVisible)
{
    if(!isVisible && _bBtnsVisible)
    {
        _animationShowPrev->stop();
        _animationShowPrev->setStartValue(0.8);
        _animationShowPrev->setEndValue(0);
        _animationShowPrev->start();

        _animationShowNext->stop();
        _animationShowNext->setStartValue(0.8);
        _animationShowNext->setEndValue(0);
        _animationShowNext->start();

        _bBtnsVisible = false;
    }

    if(isVisible && !_bBtnsVisible)
    {
        _animationShowPrev->stop();
        _animationShowPrev->setStartValue(0);
        _animationShowPrev->setEndValue(0.8);
        _animationShowPrev->start();

        _animationShowNext->stop();
        _animationShowNext->setStartValue(0);
        _animationShowNext->setEndValue(0.8);
        _animationShowNext->start();

        _bBtnsVisible = true;
    }
}

//更新所显示的图片槽函数
void PicShow::slotSelectedItem(const QString &path)
{
    _selectedPath = path;
    if(path.isEmpty())
    {
        return;
    }

    _pixmap.load(_selectedPath);
    _pixmap = _pixmap.scaled(ui->labelPic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->labelPic->setPixmap(_pixmap);
}

void PicShow::slotClearSelected()
{
    _selectedPath = nullptr;
    _pixmap = QPixmap();
    ui->labelPic->clear();
}
