#ifndef CUAEND_H
#define CUAEND_H

#include "cuadruple.h"

class CuaEnd : public Cuadruple
{
public:
    CuaEnd();
    CuaEnd(int, QString, QString, QString, QString);
    ~CuaEnd();
    virtual void doOperation(QString &, QMap<QString, QString> &, int &);
};

#endif // CUAEND_H
