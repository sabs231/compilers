#ifndef CUAIFNOT_H
#define CUAIFNOT_H

#include "cuadruple.h"

class CuaIfnot : public Cuadruple
{
public:
    CuaIfnot();
    CuaIfnot(int, QString, QString, QString, QString);
    ~CuaIfnot();
    virtual void doOperation(QString &, QMap<QString, QString> &, int &);
};

#endif // CUAIFNOT_H
