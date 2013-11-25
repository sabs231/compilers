#include <QDebug>
#include "cualogic.h"

CuaLogic::CuaLogic()
    : Cuadruple()
{
}

CuaLogic::CuaLogic(int i, QString f, QString s, QString t, QString fo)
  : Cuadruple(i, f, s, t, fo)
{
}

CuaLogic::~CuaLogic()
{
}

void CuaLogic::doOperation(QString &res, QMap<QString, QString> &temporals, int &pc)
{
  int operand1;
  int operand2;
  bool result;
  bool ok;
  (void) res;

  if (this->getFirst().toStdString() == "==")
  {
    operand1 = this->getSecond().toInt(&ok, 10);
    if (!ok)
      operand1 = ((QString)temporals[this->getSecond()]).toInt();
    operand2 = this->getThird().toInt(&ok, 10);
    if (!ok)
      operand2 = ((QString)temporals[this->getThird()]).toInt();
    result = operand1 == operand2;
    if (result)
      temporals[this->getFourth()] = QString("true");
    else
      temporals[this->getFourth()] = QString("false");
  }
  else if (this->getFirst().toStdString() == "<")
  {
    operand1 = this->getSecond().toInt(&ok, 10);
    if (!ok)
      operand1 = ((QString)temporals[this->getSecond()]).toInt();
    operand2 = this->getThird().toInt(&ok, 10);
    if (!ok)
      operand2 = ((QString)temporals[this->getThird()]).toInt();
    result = operand1 < operand2;
    if (result)
      temporals[this->getFourth()] = QString("true");
    else
      temporals[this->getFourth()] = QString("false");
  }
  else if (this->getFirst().toStdString() == ">")
  {
    operand1 = this->getSecond().toInt(&ok, 10);
    if (!ok)
      operand1 = ((QString)temporals[this->getSecond()]).toInt();
    operand2 = this->getThird().toInt(&ok, 10);
    if (!ok)
      operand2 = ((QString)temporals[this->getThird()]).toInt();
    result = operand1 > operand2;
    if (result)
      temporals[this->getFourth()] = QString("true");
    else
      temporals[this->getFourth()] = QString("false");
  }
  pc = pc + 1;
}
