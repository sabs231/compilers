#include "cuaasign.h"

CuaAsign::CuaAsign()
    : Cuadruple()
{
}

CuaAsign::CuaAsign(int i, QString f, QString s, QString t, QString fo)
    : Cuadruple(i, f, s, t, fo)
{
}

CuaAsign::~CuaAsign()
{
}

void CuaAsign::doOperation(QString &res, QMap<QString, QString> &temporals, int &pc)
{
    QString tempValue;
    int asignee;
    bool ok;

    asignee = this->getThird().toInt(&ok, 10);
    if (ok)
    {
        temporals[this->getSecond()] = tempValue.setNum(asignee);
        temporals[this->getFourth()] = tempValue.setNum(asignee);
    }
    else
    {
        if (temporals.contains(this->getThird()))
        {
            temporals[this->getSecond()] = temporals[this->getThird()];
            temporals[this->getFourth()] = temporals[this->getThird()];
        }
        else
        {
            temporals[this->getSecond()] = this->getThird();
            temporals[this->getFourth()] = this->getThird();
        }
    }
    pc = pc + 1;
}
