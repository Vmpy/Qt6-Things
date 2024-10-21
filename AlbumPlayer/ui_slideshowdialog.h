/********************************************************************************
** Form generated from reading UI file 'slideshowdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDESHOWDIALOG_H
#define UI_SLIDESHOWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <abbrlistwidget.h>
#include <picanimationwidget.h>
#include <picstatebutton.h>
#include "picbutton.h"

QT_BEGIN_NAMESPACE

class Ui_SlideShowDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widgetSlideShow;
    QGridLayout *gridLayout;
    QWidget *sildenextWidget;
    QHBoxLayout *horizontalLayout_4;
    PicButton *slidenextBtn;
    QWidget *slideprevWidget;
    QHBoxLayout *horizontalLayout_3;
    PicButton *slideprevBtn;
    PicAnimationWidget *picAnimation;
    QHBoxLayout *horizontalLayout_2;
    PicStateButton *playBtn;
    PicButton *closeBtn;
    QWidget *widgetPreview;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    AbbrListWidget *prelistWidget;

    void setupUi(QDialog *SlideShowDialog)
    {
        if (SlideShowDialog->objectName().isEmpty())
            SlideShowDialog->setObjectName("SlideShowDialog");
        SlideShowDialog->resize(764, 648);
        verticalLayout = new QVBoxLayout(SlideShowDialog);
        verticalLayout->setObjectName("verticalLayout");
        widgetSlideShow = new QWidget(SlideShowDialog);
        widgetSlideShow->setObjectName("widgetSlideShow");
        gridLayout = new QGridLayout(widgetSlideShow);
        gridLayout->setObjectName("gridLayout");
        sildenextWidget = new QWidget(widgetSlideShow);
        sildenextWidget->setObjectName("sildenextWidget");
        sildenextWidget->setMinimumSize(QSize(80, 0));
        sildenextWidget->setMaximumSize(QSize(80, 16777215));
        horizontalLayout_4 = new QHBoxLayout(sildenextWidget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        slidenextBtn = new PicButton(sildenextWidget);
        slidenextBtn->setObjectName("slidenextBtn");

        horizontalLayout_4->addWidget(slidenextBtn);


        gridLayout->addWidget(sildenextWidget, 1, 2, 1, 1);

        slideprevWidget = new QWidget(widgetSlideShow);
        slideprevWidget->setObjectName("slideprevWidget");
        slideprevWidget->setMinimumSize(QSize(80, 0));
        slideprevWidget->setMaximumSize(QSize(80, 16777215));
        horizontalLayout_3 = new QHBoxLayout(slideprevWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        slideprevBtn = new PicButton(slideprevWidget);
        slideprevBtn->setObjectName("slideprevBtn");

        horizontalLayout_3->addWidget(slideprevBtn);


        gridLayout->addWidget(slideprevWidget, 1, 0, 1, 1);

        picAnimation = new PicAnimationWidget(widgetSlideShow);
        picAnimation->setObjectName("picAnimation");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(picAnimation->sizePolicy().hasHeightForWidth());
        picAnimation->setSizePolicy(sizePolicy);

        gridLayout->addWidget(picAnimation, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        playBtn = new PicStateButton(widgetSlideShow);
        playBtn->setObjectName("playBtn");

        horizontalLayout_2->addWidget(playBtn);

        closeBtn = new PicButton(widgetSlideShow);
        closeBtn->setObjectName("closeBtn");

        horizontalLayout_2->addWidget(closeBtn);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);


        verticalLayout->addWidget(widgetSlideShow);

        widgetPreview = new QWidget(SlideShowDialog);
        widgetPreview->setObjectName("widgetPreview");
        horizontalLayout = new QHBoxLayout(widgetPreview);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(widgetPreview);
        widget->setObjectName("widget");
        widget->setEnabled(true);
        widget->setMinimumSize(QSize(0, 120));
        widget->setMaximumSize(QSize(16777215, 120));
        prelistWidget = new AbbrListWidget(widget);
        prelistWidget->setObjectName("prelistWidget");
        prelistWidget->setGeometry(QRect(14, 10, 16777211, 110));
        prelistWidget->setMinimumSize(QSize(0, 110));
        prelistWidget->setMaximumSize(QSize(16777215, 110));
        prelistWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        prelistWidget->setFlow(QListView::Flow::LeftToRight);
        prelistWidget->setViewMode(QListView::ViewMode::IconMode);

        horizontalLayout->addWidget(widget);


        verticalLayout->addWidget(widgetPreview);

        verticalLayout->setStretch(0, 7);
        verticalLayout->setStretch(1, 1);

        retranslateUi(SlideShowDialog);

        QMetaObject::connectSlotsByName(SlideShowDialog);
    } // setupUi

    void retranslateUi(QDialog *SlideShowDialog)
    {
        SlideShowDialog->setWindowTitle(QCoreApplication::translate("SlideShowDialog", "Dialog", nullptr));
        slidenextBtn->setText(QString());
        slideprevBtn->setText(QString());
        playBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SlideShowDialog: public Ui_SlideShowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDESHOWDIALOG_H
