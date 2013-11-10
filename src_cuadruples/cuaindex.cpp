#include "cuaindex.h"

CuaIndex::CuaIndex()
    : Cuadruple()
{
}

CuaIndex::CuaIndex(int i, QString f, QString s, QString t, QString fo)
    : Cuadruple(i, f, s, t, fo)
{
}

CuaIndex::~CuaIndex()
{
}

void CuaIndex::doOperation(QString &res, QMap<QString, QString> &temporals, int &pc)
{
    QString variable;
    QString indexValue;
    QString tempValue;
    int index;
    int value;
    bool ok;
    (void)res;

    index = this->getThird().toInt(&ok, 10);
    if (ok)
      indexValue.setNum(index);
    else
      indexValue = temporals[this->getThird()];
    variable = this->getSecond() + "[" + indexValue + "]";
    if (temporals.contains(variable))
    {
      value = temporals[variable].toInt(&ok, 10);
      if (ok)
        temporals[this->getFourth()] = tempValue.setNum(value);
      else
        temporals[this->getFourth()] = temporals[variable];
    }
    pc = pc + 1;
}
