/********************************************************************************
** Form generated from reading UI file 'projtree.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJTREE_H
#define UI_PROJTREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include "projtreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_ProjTree
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    ProjTreeWidget *treeWidget;

    void setupUi(QDialog *ProjTree)
    {
        if (ProjTree->objectName().isEmpty())
            ProjTree->setObjectName("ProjTree");
        ProjTree->resize(400, 300);
        ProjTree->setStyleSheet(QString::fromUtf8("QTreeView::branch:has-children:!has-siblings:closed,\n"
"QTreeView::branch:has-children:closed:has-siblings {\n"
"    border-image: none;\n"
"    image: url(:/icon/plus.svg);\n"
"}\n"
"\n"
"QTreeView::branch:open:has-children:!has-siblings,\n"
"QTreeView::branch:open:has-children:has-siblings {\n"
"    border-image: none;\n"
"    image: url(:/icon/minus.svg);\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(ProjTree);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        treeWidget = new ProjTreeWidget(ProjTree);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setColumnCount(1);
        treeWidget->header()->setVisible(true);

        verticalLayout->addWidget(treeWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ProjTree);

        QMetaObject::connectSlotsByName(ProjTree);
    } // setupUi

    void retranslateUi(QDialog *ProjTree)
    {
        ProjTree->setWindowTitle(QCoreApplication::translate("ProjTree", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjTree: public Ui_ProjTree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJTREE_H
