#ifndef ABBRLISTWIDGETITEM_H
#define ABBRLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QObject>
#include <QWidget>
#include <QIcon>

class AbbrListWidgetItem : public QListWidgetItem
{
public:
    AbbrListWidgetItem(const QIcon &icon,const QString& path,const int& index,
                       QListWidget *listview = nullptr, int type = Type);
    int getIndex();
    QString getPath();
private:
    int _index;
    QString _path;
};

#endif // ABBRLISTWIDGETITEM_H
