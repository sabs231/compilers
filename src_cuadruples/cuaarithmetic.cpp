#include <QDebug>
#include "cuaarithmetic.h"

CuaArithmetic::CuaArithmetic()
    : Cuadruple()
{
}

CuaArithmetic::CuaArithmetic(int i, QString f, QString s, QString t, QString fo)
    : Cuadruple(i, f, s, t, fo)
{
}

CuaArithmetic::~CuaArithmetic()
{
}

void CuaArithmetic::doOperation(QString & res, QMap<QString, QString> &temporals, int &pc)
{
    int operand1;
    int operand2;
    int result;
    bool ok;
    QString tempValue;
    (void) res;

    if (this->getFirst().toStdString() == "+")
    {
        operand1 = this->getSecond().toInt(&ok, 10);
        if (!ok)
            operand1 = ((QString)temporals[this->getSecond()]).toInt();
        operand2 = this->getThird().toInt(&ok, 10);
        if (!ok)
            operand2 = ((QString)temporals[this->getThird()]).toInt();
        result = operand1 + operand2;
        temporals[this->getFourth()] = tempValue.setNum(result);
    }
    else if (this->getFirst().toStdString() == "-")
    {
        operand1 = this->getSecond().toInt(&ok, 10);
        if (!ok)
            operand1 = ((QString)temporals[this->getSecond()]).toInt();
        operand2 = this->getThird().toInt(&ok, 10);
        if (!ok)
            operand2 = ((QString)temporals[this->getThird()]).toInt();
        result = operand1 - operand2;
        temporals[this->getFourth()] = tempValue.setNum(result);
    }
    else if (this->getFirst().toStdString() == "*")
    {
        operand1 = this->getSecond().toInt(&ok, 10);
        if (!ok)
            operand1 = ((QString)temporals[this->getSecond()]).toInt();
        operand2 = this->getThird().toInt(&ok, 10);
        if (!ok)
            operand2 = ((QString)temporals[this->getThird()]).toInt();
        result = operand1 * operand2;
        temporals[this->getFourth()] = tempValue.setNum(result);
    }
    else if (this->getFirst().toStdString() == "/")
    {
        operand1 = this->getSecond().toInt(&ok, 10);
        if (!ok)
            operand1 = ((QString)temporals[this->getSecond()]).toInt();
        operand2 = this->getThird().toInt(&ok, 10);
        if (!ok)
            operand2 = ((QString)temporals[this->getThird()]).toInt();
        result = operand1 / operand2;
        temporals[this->getFourth()] = tempValue.setNum(result);
    }
    else if (this->getFirst().toStdString() == "%")
    {
        operand1 = this->getSecond().toInt(&ok, 10);
        if (!ok)
            operand1 = ((QString)temporals[this->getSecond()]).toInt();
        operand2 = this->getThird().toInt(&ok, 10);
        if (!ok)
            operand2 = ((QString)temporals[this->getThird()]).toInt();
        result = operand1 % operand2;
        temporals[this->getFourth()] = tempValue.setNum(result);
    }
    pc = pc + 1;
}
