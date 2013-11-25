#ifndef CUAGOTO_H
#define CUAGOTO_H

#include "cuadruple.h"

class CuaGoto : public Cuadruple
{
public:
    CuaGoto();
    CuaGoto(int, QString, QString, QString, QString);
    ~CuaGoto();
    virtual void doOperation(QString &, QMap<QString, QString> &, int &);
};

#endif // CUAGOTO_H
