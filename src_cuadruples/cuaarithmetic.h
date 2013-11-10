#ifndef CUAARITHMETIC_H
#define CUAARITHMETIC_H

#include "cuadruple.h"

class CuaArithmetic : public Cuadruple
{
public:
    CuaArithmetic();
    CuaArithmetic(int, QString, QString, QString, QString);
    ~CuaArithmetic();
    virtual void doOperation(QString &, QMap<QString, QString> &, int &); //here we divide if is + or - or * etc
};

#endif // CUAARITHMETIC_H
