/********************************************************************************
** Form generated from reading UI file 'projsetpage.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJSETPAGE_H
#define UI_PROJSETPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_ProjSetPage
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QLabel *labelPath;
    QLineEdit *lineEditPath;
    QPushButton *buttonBrowse;
    QLabel *tips;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWizardPage *ProjSetPage)
    {
        if (ProjSetPage->objectName().isEmpty())
            ProjSetPage->setObjectName("ProjSetPage");
        ProjSetPage->resize(703, 521);
        verticalLayout = new QVBoxLayout(ProjSetPage);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        labelName = new QLabel(ProjSetPage);
        labelName->setObjectName("labelName");

        gridLayout->addWidget(labelName, 0, 0, 1, 1);

        lineEditName = new QLineEdit(ProjSetPage);
        lineEditName->setObjectName("lineEditName");

        gridLayout->addWidget(lineEditName, 0, 1, 1, 1);

        labelPath = new QLabel(ProjSetPage);
        labelPath->setObjectName("labelPath");

        gridLayout->addWidget(labelPath, 1, 0, 1, 1);

        lineEditPath = new QLineEdit(ProjSetPage);
        lineEditPath->setObjectName("lineEditPath");

        gridLayout->addWidget(lineEditPath, 1, 1, 1, 1);

        buttonBrowse = new QPushButton(ProjSetPage);
        buttonBrowse->setObjectName("buttonBrowse");

        gridLayout->addWidget(buttonBrowse, 1, 2, 1, 1);

        tips = new QLabel(ProjSetPage);
        tips->setObjectName("tips");

        gridLayout->addWidget(tips, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        gridLayout->setColumnStretch(1, 20);
        gridLayout->setColumnStretch(2, 1);

        verticalLayout->addLayout(gridLayout);


        retranslateUi(ProjSetPage);

        QMetaObject::connectSlotsByName(ProjSetPage);
    } // setupUi

    void retranslateUi(QWizardPage *ProjSetPage)
    {
        ProjSetPage->setWindowTitle(QCoreApplication::translate("ProjSetPage", "WizardPage", nullptr));
        ProjSetPage->setTitle(QCoreApplication::translate("ProjSetPage", "\350\256\276\347\275\256\351\241\271\347\233\256\351\205\215\347\275\256", nullptr));
        labelName->setText(QCoreApplication::translate("ProjSetPage", "\345\220\215\347\247\260\357\274\232", nullptr));
        labelPath->setText(QCoreApplication::translate("ProjSetPage", "\350\267\257\345\276\204\357\274\232", nullptr));
        buttonBrowse->setText(QCoreApplication::translate("ProjSetPage", "\346\265\217\350\247\210", nullptr));
        tips->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProjSetPage: public Ui_ProjSetPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJSETPAGE_H
