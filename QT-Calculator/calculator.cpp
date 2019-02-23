#include "calculator.h"
#include "ui_calculator.h"

//{ using those static bool variable to take control the operation
// and printing result
static double cal_input1 = 0.0;
static double cal_input2 = 0.0;
static bool add = false;
static bool minus = false;
static bool division = false;
static bool multi = false;
static bool srt = false;
static bool dot = false;
static bool equal = false;
static bool afterDot = false;
static bool zero = false;
static bool afterUniary = false;
//}

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
        //number 1-9
        connect(ui->button0, SIGNAL(clicked()), this, SLOT(setButton0()));
        connect(ui->button1, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        connect(ui->button2, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        connect(ui->button3, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        connect(ui->button4, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        connect(ui->button5, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        connect(ui->button6, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        connect(ui->button7, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        connect(ui->button8, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        connect(ui->button9, SIGNAL(clicked()), this, SLOT(setNumPressed()));
        // dot button
        connect(ui->buttonDot, SIGNAL(clicked()), this, SLOT(setDot()));

        //function
        connect(ui->buttonEqual, SIGNAL(clicked()), this, SLOT(setResult()));
        connect(ui->buttonDel, SIGNAL(clicked()), this, SLOT(setDelete()));
        connect(ui->buttonClear, SIGNAL(clicked()), this, SLOT(setClear()));

        //uniary
        connect(ui->buttonPlus, SIGNAL(clicked()), this, SLOT(setOperationText()));
        connect(ui->buttonMinus, SIGNAL(clicked()), this, SLOT(setOperationText()));
        connect(ui->buttonMulti, SIGNAL(clicked()), this, SLOT(setOperationText()));
        connect(ui->buttonDiv, SIGNAL(clicked()), this, SLOT(setOperationText()));
        connect(ui->buttonSrt, SIGNAL(clicked()), this, SLOT(setOperationText()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::setOperationText()
{
    QPushButton *button = (QPushButton*)sender();

    // if equal set as true than after showing result
    // if user push any number button in calculator will start again from beginig
    if (equal == true)
    {
        // set all inLine fileds to empty and set equal to false
        //
        ui->input1->setText("");
        ui->input2->setText("");
        ui->result->setText("");
        ui->op->setText("");
        equal = false;
    }

    else
    {
        // value store the pressed butto
        QString value = button->text();

        QChar c = value.at(0);
        QString n = c.toLatin1();

        // displayVal store the value from input #1
        QString displayVal = ui->input1->text();
        cal_input1 = displayVal.toDouble();

        QString displayVal_2 = ui->input2->text();

        // if there's nothing inside input #1 then
        // calculator doesn't allow any uninary operation to go input#2
        if (displayVal.isEmpty())
        {
            add = false;
            minus = false;
            division = false;
            multi = false;
            srt = false;
            dot = false;
            afterDot = false;
            afterUniary = false;

            ui->op->setText("");

            // it allows to enter negative number at input #1
            if (QString::compare(value, "-", Qt::CaseInsensitive) == 0)
            {
                ui->input1->setText("-" + ui->input1->text());
            }
        }

        // if there are some valus inside input #1 then
        else
        {
            // fills operation with uninary value
            ui->op->setText(QString(button->text()));

            if (displayVal == "-")
            {
                add = false;
                minus = false;
                division = false;
                multi = false;
                srt = false;
                dot = false;
                afterUniary = false;

                ui->input1->setText("");
                ui->op->setText("");
            }
            else
            {
                // seeting all flags true expect afterDot
                if (QString::compare(value, "+", Qt::CaseInsensitive) == 0)
                {
                    add = true;
                    afterDot = false;
                    afterUniary = true;
                }
                else if (QString::compare(value, "-", Qt::CaseInsensitive) == 0)
                {
                    minus = true;
                    afterDot = false;
                    afterUniary = true;
                }
                else if (QString::compare(value, "/", Qt::CaseInsensitive) == 0)
                {
                    afterDot = false;
                    division = true;
                    afterUniary = true;
                }
                else if (QString::compare(value, "x", Qt::CaseInsensitive) == 0)
                {
                    multi = true;
                    afterDot = false;
                    afterUniary = true;
                }
                else if (QString::compare(value, "*", Qt::CaseInsensitive) == 0)
                {
                    multi = true;
                    afterDot = false;
                    afterUniary = true;
                }
                else
                {
                    srt = true;
                    afterDot = false;
                    afterUniary = true;
                }
            }
        }
    }
    // after user hit operation button
    // user can enter number number at input #2
    // but user nothing happened when hit user uninary button on input2
    if (afterUniary == false)
    {
        ui->input2->setText("");
    }
    else
    {
        QString value_2 = ui->input2->text();
        ui->input2->setText(value_2);
    }

}
void Calculator::setNumPressed()
{
    QPushButton *button = (QPushButton*)sender();

    QString value = button->text();

    // if equal set as true than after showing result
    // if user push any number button, calculator will start again from beginig
    if (equal == true)
    {
        // set all inLine fileds to empty and set equal to false
        ui->input1->setText("");
        ui->input2->setText("");
        ui->result->setText("");
        ui->op->setText("");
        equal = false;
    }

    if (add || minus || division || multi) // true // set values for input #2
    {

        QString num_2;
        double inputNumber_2;

        inputNumber_2 = (ui->input2->text() + button->text()).toDouble();
        num_2 = QString::number(inputNumber_2, 'g', 15);

        ui->input2->setText(num_2);
        QString value = button->text();
        // allow user to enter decimel number
        if (QString::compare(value, ".", Qt::CaseInsensitive) == 0)
        {
            dot = true;
            ui->input2->setText(ui->input2->text() + "."); // now
        }
    }

    else // set values for input #1
    {
        if (srt == false)
        {
            double inputNumber;
            inputNumber = (ui->input1->text() + button->text()).toDouble();

            QString num;
            num = QString::number(inputNumber, 'g', 15);

            ui->input1->setText(num);

            QString value = button->text();
            // allow user to enter decimel number
            if (QString::compare(value, ".", Qt::CaseInsensitive) == 0)
            {
                dot = true;
                ui->input1->setText(ui->input1->text() + ".");
            }
        }
    }
}

void Calculator::setResult()
{
    equal = true;
    double result = 0.0;

    // getting value from input#2
    QString displayVal_input2 = ui->input2->text();
    cal_input2 = displayVal_input2.toDouble();

    // doing calculation
    if (add == true)
    {
        result = cal_input1 + cal_input2;
        ui->result->setText(QString::number(result, 'g', 10));
    }
    else if (minus == true)
    {
        result = cal_input1 - cal_input2;
        ui->result->setText(QString::number(result, 'g', 10));
    }
    else if (multi == true)
    {
        result = cal_input1 * cal_input2;
        ui->result->setText(QString::number(result, 'g', 10));
    }
    else if (division == true)
    {
        result = (cal_input1 / cal_input2);
        ui->result->setText(QString::number(result, 'g', 10));
    }
    else if (srt == true)
    {
        cal_input2 = 0.0;
        result = sqrt(cal_input1);
        ui->result->setText(QString::number(result, 'g', 10));
    }
    // after showing result set equal all the variable to false
    // so that user can start from beginig
    if (equal == true)
    {
        add = false;
        minus = false;
        division = false;
        multi = false;
        srt = false;
        dot = false;
        afterDot = false;
        afterUniary = false;
    }
}

void Calculator::setClear()
{
    // clear all the values from calculator
    add = false;
    minus = false;
    division = false;
    multi = false;
    srt = false;
    dot = false;
    equal = false;
    afterDot = false;
    afterUniary = false;

    ui->input1->setText("");
    ui->input2->setText("");
    ui->result->setText("");
    ui->op->setText("");
}

void Calculator::setDelete()
{
    // if calculator doesn't show any result then
    if (equal == false)
    {
        // it allows to del one number each from input #2
        if (add || minus || division || multi || srt)//true
        {
            // chop the right most element
            QString push = ui->input2->text();
            push.chop(1);
            // if there are no number left at screen, then set input #1 values to 0
            if (push.isEmpty())
            {
                push = "";
                ui->input2->setText(push);
            }
            else
                ui->input2->setText(push);
        }

        else
        {
            // chop right most element
            QString push = ui->input1->text();
            push.chop(1);

            // if there are no number left at screen, then set input #1 values to 0
            if (push.isEmpty())
            {
                ui->input1->setText(push);
            }
            else
                ui->input1->setText(push);
        }
    }
}

void Calculator::setDot()
{
    // if dot Num is pressed,
    if (afterDot == false)
    {
        // calling setNumPressed function and make afterDot is true
        // so that user will unable to enter another dot in same inLineEdit
        Calculator::setNumPressed();
        afterDot = true;
    }
}

void Calculator::setButton0()
{
    QPushButton *button = (QPushButton*)sender();
    QString value = button->text();

    // concatinating 0 with inLineEdit after pressed Button 0
    if (add || minus || division || multi) // true
    {
        QString num2 = ui->input2->text();
        ui->input2->setText(num2 + "0");
    }
    else if (srt == false) // set values for input #1
    {
        QString num1 = ui->input1->text();
        ui->input1->setText(num1 + "0");
    }
}



