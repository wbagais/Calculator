#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
double memoryVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; i++){
        QString butName = "button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(ui->add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));

    connect(ui->changeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));

    connect(ui->clear, SIGNAL(released()), this,
            SLOT(ClearButtonPressed()));

    connect(ui->memAdd, SIGNAL(released()), this,
            SLOT(AddToMemory()));

    connect(ui->memClear, SIGNAL(released()), this,
            SLOT(ClearMemory()));

    connect(ui->memAdd, SIGNAL(released()), this,
            SLOT(AddToMemory()));

    connect(ui->memGet, SIGNAL(released()), this,
            SLOT(GetMemory()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->display->setText(butVal);
    } else {
        QString newVal = displayVal+butVal;
        double dblNewVal = newVal.toDouble();
        ui->display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
       divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
     }else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
     }else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
     }
    ui->display->setText("");
}

void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->display->text();
    double dblDisplyVal = displayVal.toDouble();
    if (divTrigger || multTrigger || addTrigger || subTrigger){
        if (divTrigger){
            solution = calcVal / dblDisplyVal;
        }else if (multTrigger){
            solution = calcVal * dblDisplyVal;
        }else if (addTrigger){
            solution = calcVal + dblDisplyVal;
        }else if (subTrigger){
            solution = calcVal - dblDisplyVal;
        }
    }
    ui->display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::ClearButtonPressed(){
    ui->display->setText("0.0");
    calcVal = 0;
}

void Calculator::AddToMemory(){
   QString displayVal = ui->display->text();
   memoryVal = displayVal.toDouble();
}

void Calculator::ClearMemory(){
    memoryVal = 0.0;
}
void Calculator::GetMemory(){
    ui->display->setText(QString::number(memoryVal));
}
