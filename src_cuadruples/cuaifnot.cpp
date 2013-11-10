#include "cuaifnot.h"
#include <QDebug>
#include <QStringList>

CuaIfnot::CuaIfnot()
    : Cuadruple()
{
}

CuaIfnot::CuaIfnot(int i, QString f, QString s, QString t, QString fo)
    : Cuadruple(i, f, s, t, fo)
{
}

CuaIfnot::~CuaIfnot()
{
}

void CuaIfnot::doOperation(QString &res, QMap<QString, QString> &temporals, int &pc)
{
    QString value;
    QStringList list;
    int instruction;
    (void)res;

    value = temporals[this->getSecond()];
    if (value == QString("false"))
    {
      list = this->getThird().split("goto");
      instruction = ((QString)list[1]).toInt();
      pc = instruction;
    }
    else
      pc = pc + 1;
}
