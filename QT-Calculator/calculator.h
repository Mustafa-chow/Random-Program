#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::Calculator *ui;

public slots:
    void setOperationText();
    void setNumPressed();
    void setResult();
    void setClear();
    void setDelete();
    void setDot();
    void setButton0();
};

#endif // CALCULATOR_H
