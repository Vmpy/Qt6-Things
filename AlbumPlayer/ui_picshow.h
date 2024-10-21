/********************************************************************************
** Form generated from reading UI file 'picshow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICSHOW_H
#define UI_PICSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "picbutton.h"

QT_BEGIN_NAMESPACE

class Ui_PicShow
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacerUp;
    QSpacerItem *horizontalSpacerRight;
    QWidget *widgetPrev;
    QVBoxLayout *verticalLayout_3;
    PicButton *prevBtn;
    QSpacerItem *horizontalSpacerLeft;
    QLabel *labelPic;
    QWidget *widgetNext;
    QVBoxLayout *verticalLayout_2;
    PicButton *nextBtn;
    QSpacerItem *verticalSpacerDown;

    void setupUi(QDialog *PicShow)
    {
        if (PicShow->objectName().isEmpty())
            PicShow->setObjectName("PicShow");
        PicShow->resize(830, 651);
        verticalLayout = new QVBoxLayout(PicShow);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        verticalSpacerUp = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(verticalSpacerUp, 0, 2, 1, 1);

        horizontalSpacerRight = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacerRight, 1, 3, 1, 1);

        widgetPrev = new QWidget(PicShow);
        widgetPrev->setObjectName("widgetPrev");
        widgetPrev->setMinimumSize(QSize(60, 60));
        widgetPrev->setMaximumSize(QSize(60, 60));
        verticalLayout_3 = new QVBoxLayout(widgetPrev);
        verticalLayout_3->setObjectName("verticalLayout_3");
        prevBtn = new PicButton(widgetPrev);
        prevBtn->setObjectName("prevBtn");

        verticalLayout_3->addWidget(prevBtn);


        gridLayout->addWidget(widgetPrev, 1, 0, 1, 1);

        horizontalSpacerLeft = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacerLeft, 1, 1, 1, 1);

        labelPic = new QLabel(PicShow);
        labelPic->setObjectName("labelPic");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelPic->sizePolicy().hasHeightForWidth());
        labelPic->setSizePolicy(sizePolicy);
        labelPic->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(labelPic, 1, 2, 1, 1);

        widgetNext = new QWidget(PicShow);
        widgetNext->setObjectName("widgetNext");
        widgetNext->setMinimumSize(QSize(60, 60));
        widgetNext->setMaximumSize(QSize(60, 60));
        verticalLayout_2 = new QVBoxLayout(widgetNext);
        verticalLayout_2->setObjectName("verticalLayout_2");
        nextBtn = new PicButton(widgetNext);
        nextBtn->setObjectName("nextBtn");

        verticalLayout_2->addWidget(nextBtn);


        gridLayout->addWidget(widgetNext, 1, 4, 1, 1);

        verticalSpacerDown = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(verticalSpacerDown, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(PicShow);

        QMetaObject::connectSlotsByName(PicShow);
    } // setupUi

    void retranslateUi(QDialog *PicShow)
    {
        PicShow->setWindowTitle(QCoreApplication::translate("PicShow", "Dialog", nullptr));
        prevBtn->setText(QString());
        labelPic->setText(QString());
        nextBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PicShow: public Ui_PicShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICSHOW_H
