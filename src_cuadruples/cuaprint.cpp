#include "cuaprint.h"
#include <QDebug>

CuaPrint::CuaPrint()
    : Cuadruple()
{
}

CuaPrint::CuaPrint(int i, QString f, QString s, QString t, QString fo)
    : Cuadruple(i, f, s, t, fo)
{
}

CuaPrint::~CuaPrint()
{
}

void CuaPrint::doOperation(QString &res, QMap<QString, QString> &temporals, int &pc)
{
    int number;
    bool ok;
    QString tempValue;

    number = this->getSecond().toInt(&ok, 10);
    if (ok)
      res.append(tempValue.setNum(number));
    else if (temporals.contains(this->getSecond()))
      res.append(temporals[this->getSecond()]);
    else
      res.append(this->getSecond());
    res.append("\n");
    pc = pc + 1;
}
