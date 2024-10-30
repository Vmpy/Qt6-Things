#include "abbrlistwidgetitem.h"


AbbrListWidgetItem::AbbrListWidgetItem(const QIcon &icon, const QString &path, const int &index,
                                       QListWidget *listview, int type):
    QListWidgetItem(icon,"",listview,type),_index(index),_path(path)
{

}

int AbbrListWidgetItem::getIndex()
{
    return _index;
}

QString AbbrListWidgetItem::getPath()
{
    return _path;
}
