#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    priceListModel = new QStandardItemModel;
    orderListModel = new QStandardItemModel;

    ui->herbTableView->setModel(priceListModel);
    ui->orderTableView->setModel(orderListModel);

    orderSelectionModel = ui->orderTableView->selectionModel();

    //UI可视化设计中指定edittrigger
    HeaderList = new QStringList;
    orderHeaderList = new QStringList;

    priceList = new QFile("priceList.txt");
    if(!priceList->exists())
    {
        QMessageBox::warning(this,"警告","找不到价目表，请手动添加");
        this->close();
    }
    else
    {
        initPriceList();
    }

    connect(this,&MainWindow::updatePrice,this,&MainWindow::showPrice);
    connect(orderListModel,&QStandardItemModel::dataChanged,this,&MainWindow::showPrice);

    emit ui->herbNameLineEdit->textChanged("");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPriceList()
{
    FileContent = new QStringList;
    if(priceList->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream astream(priceList);
        QString aline;
        while(!astream.atEnd())
        {
            aline = astream.readLine();
            FileContent->append(aline);
        }
    }
    priceList->close();

    QString Header = FileContent->at(0);

    *HeaderList = Header.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
    fixed_column = HeaderList->size();
    *orderHeaderList = *HeaderList;

    orderHeaderList->append("数量");

    priceListModel->setHorizontalHeaderLabels(*HeaderList);
    orderListModel->setHorizontalHeaderLabels(*orderHeaderList);
    ui->orderTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->herbTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_herbNameLineEdit_textChanged(const QString &str)
{
    int RowCnt = FileContent->size();
    int displayRowCnt = 0;
    QStringList herbItem;
    QStandardItem *aItem;
    QString mstr = str.toLower();
    priceListModel->clear();
    priceListModel->setHorizontalHeaderLabels(*HeaderList);
    ui->herbTableView->resizeColumnsToContents();

    if(str.isEmpty())
    {
        for(int i = 1;i < RowCnt;i++)
        {
            herbItem = FileContent->at(i).split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
            for(int j = 0;j < fixed_column;j++)
            {
                aItem = new QStandardItem(herbItem[j]);

                priceListModel->setItem(displayRowCnt,j,aItem);
                priceListModel->setData(priceListModel->index(displayRowCnt,j),Qt::AlignCenter,Qt::TextAlignmentRole);
            }
            displayRowCnt++;
        }
        return;
    }

    for(int i = 1;i < RowCnt;i++)
    {
        herbItem = FileContent->at(i).split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);

        if(0 == herbItem[0].indexOf(mstr) || 0 == herbItem[1].indexOf(mstr))
        {
            for(int j = 0;j < fixed_column;j++)
            {
                aItem = new QStandardItem(herbItem[j]);

                priceListModel->setItem(displayRowCnt,j,aItem);
                priceListModel->setData(priceListModel->index(displayRowCnt,j),Qt::AlignCenter,Qt::TextAlignmentRole);
            }
            displayRowCnt++;
        }
    }
}


void MainWindow::on_herbTableView_doubleClicked(const QModelIndex &index)
{
    int srcRow = index.row();
    int destRow = orderListModel->rowCount();

    for(int i = 0;i < fixed_column;i++)
    {
        QStandardItem *aItem = new QStandardItem(priceListModel->data(priceListModel->index(srcRow,i)).toString());
        orderListModel->setItem(destRow,i,aItem);
        orderListModel->setData(orderListModel->index(destRow,i),Qt::AlignCenter,Qt::TextAlignmentRole);
    }

    QStandardItem *aItem = new QStandardItem("输入数量");
    orderListModel->setItem(destRow,fixed_column,aItem);
    orderListModel->setData(orderListModel->index(destRow,fixed_column),Qt::AlignCenter,Qt::TextAlignmentRole);
    orderListModel->setHorizontalHeaderLabels(*orderHeaderList);

    emit updatePrice();
}

void MainWindow::showPrice()
{
    double sum = 0;
    int Rows = orderListModel->rowCount();
    for(int i = 0;i < Rows;i++)
    {
        bool num_ok;
        bool price_ok;
        double num = orderListModel->data(orderListModel->index(i,3)).toDouble(&num_ok);
        double price = orderListModel->data(orderListModel->index(i,2)).toDouble(&price_ok);

        if(num_ok && price_ok)
        {
            sum += num*price;
        }
    }

    QString strPrice = QString::number(sum,'f',2);
    strPrice += " 元";
    ui->priceEdit->setText(strPrice);
}


void MainWindow::on_deleteButton_clicked()
{
    if (!orderSelectionModel->hasSelection())
    {
        return;
    }
    QModelIndexList toDelList = orderSelectionModel->selectedIndexes();
    int n = toDelList.size();

    for(int i = 0;i < n;i++)
    {
        orderListModel->removeRow(toDelList[i].row());
    }
    emit updatePrice();
}


void MainWindow::on_pushButton_clicked()
{
    orderListModel->clear();
    orderListModel->setHorizontalHeaderLabels(*orderHeaderList);
    emit updatePrice();
}