/********************************************************************************
** Form generated from reading UI file 'removeprojdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOVEPROJDIALOG_H
#define UI_REMOVEPROJDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RemoveProjDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QCheckBox *checkBoxDeleteFile;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RemoveProjDialog)
    {
        if (RemoveProjDialog->objectName().isEmpty())
            RemoveProjDialog->setObjectName("RemoveProjDialog");
        RemoveProjDialog->resize(400, 300);
        verticalLayout_3 = new QVBoxLayout(RemoveProjDialog);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label = new QLabel(RemoveProjDialog);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("QLabel#label {\n"
"	color: black;\n"
"}"));

        verticalLayout->addWidget(label);

        checkBoxDeleteFile = new QCheckBox(RemoveProjDialog);
        checkBoxDeleteFile->setObjectName("checkBoxDeleteFile");

        verticalLayout->addWidget(checkBoxDeleteFile);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(RemoveProjDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_2->addWidget(buttonBox);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(RemoveProjDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, RemoveProjDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, RemoveProjDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(RemoveProjDialog);
    } // setupUi

    void retranslateUi(QDialog *RemoveProjDialog)
    {
        RemoveProjDialog->setWindowTitle(QCoreApplication::translate("RemoveProjDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("RemoveProjDialog", "     \344\273\216\351\241\271\347\233\256\344\270\255\347\247\273\351\231\244\346\226\207\344\273\266", nullptr));
        checkBoxDeleteFile->setText(QCoreApplication::translate("RemoveProjDialog", "\345\220\214\346\227\266\345\210\240\351\231\244\346\234\254\345\234\260\351\241\271\347\233\256\346\226\207\344\273\266\345\244\271\351\241\271\347\233\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoveProjDialog: public Ui_RemoveProjDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOVEPROJDIALOG_H
