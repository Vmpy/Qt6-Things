#include "widget.h"
#include "ui_widget.h"
#include <QStack>
#include <QtMath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("计算器");

    QFont f;
    f = QFont("仿宋",12);
    ui->expressionEdit->setFont(f);
    errorFlag = 0;
    lastAns.clear();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_num1Button_clicked()
{
    expression += "1";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num2Button_clicked()
{
    expression += "2";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num3Button_clicked()
{
    expression += "3";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num4Button_clicked()
{
    expression += "4";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num5Button_clicked()
{
    expression += "5";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num6Button_clicked()
{
    expression += "6";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num7Button_clicked()
{
    expression += "7";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num8Button_clicked()
{
    expression += "8";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num9Button_clicked()
{
    expression += "9";
    ui->expressionEdit->setText(expression);
}


void Widget::on_num0Button_clicked()
{
    expression += "0";
    ui->expressionEdit->setText(expression);
}


void Widget::on_ACButton_clicked()
{
    expression.clear();
    ui->expressionEdit->setText(expression);
}


void Widget::on_divideButton_clicked()
{
    expression += "÷";
    ui->expressionEdit->setText(expression);
}


void Widget::on_multiplyButton_clicked()
{
    expression += "×";
    ui->expressionEdit->setText(expression);
}


void Widget::on_minusButton_clicked()
{
    expression += "-";
    ui->expressionEdit->setText(expression);
}


void Widget::on_plusButton_clicked()
{
    expression += "+";
    ui->expressionEdit->setText(expression);
}


void Widget::on_dotButton_clicked()
{
    expression += ".";
    ui->expressionEdit->setText(expression);
}


void Widget::on_backspaceButton_clicked()
{
    expression.chop(1);
    ui->expressionEdit->setText(expression);
}


void Widget::on_leftButton_clicked()
{
    expression += "(";
    ui->expressionEdit->setText(expression);
}


void Widget::on_rightButton_clicked()
{
    expression += ")";
    ui->expressionEdit->setText(expression);
}


void Widget::on_ansButton_clicked()
{
    expression += "Ans";
    ui->expressionEdit->setText(expression);
}


void Widget::on_piButton_clicked()
{
    expression += "π";
    ui->expressionEdit->setText(expression);
}


void Widget::on_eButton_clicked()
{
    expression += "e";
    ui->expressionEdit->setText(expression);
}


void Widget::on_modButton_clicked()
{
    expression += "mod";
    ui->expressionEdit->setText(expression);
}

//抽出单个计算数字
int Widget::extractNum(QString &expr,int index,int n)
{
    int end = n;
    for(int i = index;i < n;i++)
    {
        if(!expr[i].isDigit() && expr[i] != '.')
        {
            end = i;
            break;
        }
    }
    return end;
}

//查询运算符优先级
int Widget::getPriority(QChar a)
{
    if('+' == a || '-' == a)
    {
        return 1;
    }
    else if('*' == a || '/' == a || '%' == a)
    {
        return 2;
    }
    else if('(' == a)
    {
        return 3;
    }
    else if(')' == a)
    {
        return 3;
    }

    return 0;
}

//查找带符号位的数字,在正负数的符号位前面加个0,转化为全正数加减法
void  Widget::convertToStdExp(QString &expr)
{
    //替换数学常量和运算符号
    expr.replace("π",QString::number(M_PI));
    expr.replace("e",QString::number(M_E));
    expr.replace("×","*");
    expr.replace("÷","/");
    expr.replace("mod","%");
    expr.replace("Ans",lastAns);

    //转化有符号数
    int n = expr.size();
    for(int i = 0;i < n;i++)
    {
        QChar c = expr[i];
        if((c == '-' || c == '+') && (i == 0 || expr[i-1] == '('))
        {
            expr.insert(i,'0');
            n++;
        }
    }

    //测试运算符是否合法
    for(int i = 0;i < n;i++)
    {
        if(expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '%')
        {
            if(!(expr[i-1].isDigit() && expr[i+1].isDigit()))
            {
                if(expr[i-1] == ')' && expr[i+1].isDigit())
                {
                    continue;
                }
                if(expr[i+1] == '(' && expr[i-1].isDigit())
                {
                    continue;
                }
                errorExp();
                return;
            }
        }
    }
}

//计算表达式值，将中缀表达式转化为后缀表达式
//点击等于号
void Widget::on_equalButton_clicked()
{
    QStack<QChar> Stack;
    QString postfixExp; //后缀表达式字符串
    QString infixExp = expression;  //中缀表达式字符串

    if(expression == "")
    {
        return;
    }

    convertToStdExp(infixExp);

    if(errorFlag)
    {
        errorExe();
        return;
    }

    int n = infixExp.size();
    int i = 0;
    while(i < n)
    {
        QChar c = infixExp[i];
        if(c.isDigit())
        {
            int end = extractNum(infixExp,i,n);
            postfixExp += infixExp.sliced(i,end-i) + ' ';
            i = end;
            continue;
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == '%')
        {
            if(Stack.isEmpty())
            {
                Stack.push(c);
            }
            else
            {
                while(!Stack.isEmpty() && getPriority(c) <= getPriority(Stack.top()) )
                {
                    if(Stack.top() == '(')
                    {
                        break;
                    }
                    postfixExp += Stack.pop() + ' ';

                }
                Stack.push(c);
            }
        }
        else if(c == ')')
        {
            while(!Stack.isEmpty())
            {
                if(Stack.top() == '(')
                {
                    Stack.pop();
                    break;
                }
                postfixExp += Stack.pop() + ' ';
            }
        }

        i++;
    }

    while(!Stack.isEmpty())
    {
        postfixExp += Stack.pop();
    }


    double ans = calPostfixExp(postfixExp);

    if(errorFlag)
    {
        errorExe();
        return;
    }
    else
    {
        expression = QString::number(ans);
        lastAns = expression;
        ui->expressionEdit->setText(expression);
    }

}

//计算后缀表达式
//表达式错误在此方法中完成
double Widget::calPostfixExp(QString &expr)
{
    QString Num;
    QStack<double> Stack;
    int i = 0;
    int n = expr.size();
    while(i < n)
    {
        QChar c = expr[i];
        if(c.isDigit())
        {
            int end = extractNum(expr,i,n);
            bool check;
            Num = expr.sliced(i,end-i);
            double TmpNum = Num.toDouble(&check);
            if(check)
            {
                Stack.push(TmpNum);
            }
            else
            {
                errorExp();
                return 0;
            }
            i = end;
            continue;
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        {
            //后缀表达式检错
            if(Stack.empty())
            {
                errorExp();
                return 0;
            }
            double b = Stack.pop();

            if(Stack.empty())
            {
                errorExp();
                return 0;
            }
            double a = Stack.pop();
            if(c == '+')
            {
                Stack.push(a+b);
            }
            else if(c == '-')
            {
                Stack.push(a-b);
            }
            else if(c == '/')
            {
                Stack.push(a/b);
            }
            else if(c == '*')
            {
                Stack.push(a*b);
            }
            else if(c == '%')
            {
                Stack.push(fmod(a,b));
            }
        }
        i++;
    }

    //后缀表达式检错
    if(Stack.size() != 1 || Stack.empty())
    {
        errorExp();
        return 0;
    }
    else
    {
        return Stack.pop();
    }
}

//非法输入提示
void Widget::errorExp(void)
{
    errorFlag = 1;
}

//执行错误输出
void Widget::errorExe(void)
{
    ui->expressionEdit->setText("非法输入，请重新输入");
    expression.clear();
    errorFlag = 0;
}
