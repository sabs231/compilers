#ifndef CUAASIGN_H
#define CUAASIGN_H

#include "cuadruple.h"

class CuaAsign : public Cuadruple
{
public:
    CuaAsign();
    CuaAsign(int, QString, QString, QString, QString);
    ~CuaAsign();
    virtual void doOperation(QString &, QMap<QString, QString> &, int &);
};

#endif // CUAASIGN_H
