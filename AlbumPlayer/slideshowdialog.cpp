#include "slideshowdialog.h"
#include "ui_slideshowdialog.h"

SlideShowDialog::SlideShowDialog(QWidget *parent, QTreeWidgetItem *firstItem, QTreeWidgetItem *lastItem)
    :QDialog(parent),ui(new Ui::SlideShowDialog),_firstItem(firstItem),_lastItem(lastItem)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    connect(ui->closeBtn,&PicButton::clicked,this,&SlideShowDialog::close);

    ui->slideprevBtn->setIcons(":/icon/left-normal.svg",
                               ":/icon/left-hover.svg",
                               ":/icon/left-pressed.svg");
    ui->slidenextBtn->setIcons(":/icon/right-normal.svg",
                               ":/icon/right-hover.svg",
                               ":/icon/right-pressed.svg");
    ui->closeBtn->setIcons(":/icon/close-show-normal.svg",
                           ":/icon/close-show-hover.svg",
                           ":/icon/close-show-pressed.svg");
    ui->playBtn->setIcons(":/icon/play-normal.svg",
                          ":/icon/play-hover.svg",
                          ":/icon/play-pressed.svg",
                          ":/icon/pause-normal.svg",
                          ":/icon/pause-hover.svg",
                          ":/icon/pause-pressed.svg");

    auto * prelistWidget = dynamic_cast<AbbrListWidget*>(ui->prelistWidget);

    connect(ui->picAnimation,&PicAnimationWidget::sigUpdatePrelist,prelistWidget,
            &AbbrListWidget::slotUpdatePrelist);
    connect(ui->picAnimation,&PicAnimationWidget::sigSelectedItem,prelistWidget,
            &AbbrListWidget::slotSelectedItem);
    connect(ui->slidenextBtn,&PicButton::clicked,ui->picAnimation,&PicAnimationWidget::slideNext);
    connect(ui->slideprevBtn,&PicButton::clicked,ui->picAnimation,&PicAnimationWidget::slidePrev);
    connect(prelistWidget,&AbbrListWidget::itemPressed,ui->picAnimation,
            &PicAnimationWidget::slotUpdateClickedItem);
    connect(ui->playBtn,&PicStateButton::clicked,ui->picAnimation,
            &PicAnimationWidget::slotStartOrStopSlide);
    connect(ui->picAnimation,&PicAnimationWidget::sigStart,ui->playBtn,&PicStateButton::slotStart);
    connect(ui->picAnimation,&PicAnimationWidget::sigStop,ui->playBtn,&PicStateButton::slotStop);
    ui->picAnimation->setPixmap(firstItem);
    ui->picAnimation->startAnimation();
}

SlideShowDialog::~SlideShowDialog()
{
    delete ui;
}
