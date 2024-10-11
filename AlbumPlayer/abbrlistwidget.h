#ifndef ABBRLISTWIDGET_H
#define ABBRLISTWIDGET_H

#include <QListWidget>
#include "const.h"
#include <QTreeWidgetItem>

class AbbrListWidget : public QListWidget
{
    Q_OBJECT
public:
    AbbrListWidget(QWidget *parent = nullptr);
    void AddListItem(const QString& path);
    int _globalNum = 0;
    int _lastIndex = MAX_ABBRPAGEICONS;

private:
    QMap<QString,QListWidgetItem*> _setItems;
    QPoint _posOrigin;

public slots:
    void slotUpdatePrelist(QTreeWidgetItem *item);
    void slotSelectedItem(QTreeWidgetItem *item);

};

#endif // ABBRLISTWIDGET_H
