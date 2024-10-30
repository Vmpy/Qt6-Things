#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void updatePrice(void);

private slots:
    void on_herbNameLineEdit_textChanged(const QString &arg1);

    void on_herbTableView_doubleClicked(const QModelIndex &index);

    void showPrice(void);

    void on_deleteButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int fixed_column;
    QFile *priceList;
    QStringList *FileContent;
    QStringList *HeaderList;
    QStringList *orderHeaderList;
    QStandardItemModel *priceListModel;
    QStandardItemModel *orderListModel;
    QItemSelectionModel *orderSelectionModel;
    void initPriceList(void);
};
#endif // MAINWINDOW_H
