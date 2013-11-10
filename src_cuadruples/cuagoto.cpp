#include "cuagoto.h"
#include <QStringList>

CuaGoto::CuaGoto()
    : Cuadruple()
{
}

CuaGoto::CuaGoto(int i, QString f, QString s, QString t, QString fo)
    : Cuadruple(i, f, s, t, fo)
{
}

CuaGoto::~CuaGoto()
{
}

void CuaGoto::doOperation(QString &res, QMap<QString, QString> &temporals, int &pc)
{
    int instruction;
    QStringList list;
    (void)res;
    (void)temporals;

    list = this->getSecond().split("goto");
    instruction = ((QString)list[1]).toInt();
    pc = instruction;
}
