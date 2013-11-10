#include <QDebug>
#include "cuaend.h"

CuaEnd::CuaEnd()
    : Cuadruple()
{
}

CuaEnd::CuaEnd(int i, QString f, QString s, QString t, QString fo)
    : Cuadruple(i, f, s, t, fo)
{
}

CuaEnd::~CuaEnd()
{
}

void CuaEnd::doOperation(QString &res, QMap<QString, QString> &temporals, int &pc)
{
    (void)res;
    (void)temporals;
    (void)pc;
    qDebug() << "This is the end!";
}
