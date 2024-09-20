#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_num1Button_clicked();

    void on_num2Button_clicked();

    void on_num3Button_clicked();

    void on_num4Button_clicked();

    void on_num5Button_clicked();

    void on_num6Button_clicked();

    void on_num7Button_clicked();

    void on_num8Button_clicked();

    void on_num9Button_clicked();

    void on_num0Button_clicked();

    void on_ACButton_clicked();

    void on_divideButton_clicked();

    void on_multiplyButton_clicked();

    void on_minusButton_clicked();

    void on_plusButton_clicked();

    void on_dotButton_clicked();

    void on_backspaceButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_equalButton_clicked();

    void on_ansButton_clicked();

    void on_piButton_clicked();

    void on_eButton_clicked();

    void on_modButton_clicked();

private:
    Ui::Widget *ui;
    QString expression;
    QString lastAns;
    int errorFlag;

    int extractNum(QString &expr,int index,int n);
    int getPriority(QChar a);
    double calPostfixExp(QString &expr);
    void errorExp(void);
    void errorExe(void);
    void convertToStdExp(QString &expr);
};

#endif // WIDGET_H
