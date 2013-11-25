#ifndef CUALOGIC_H
#define CUALOGIC_H

#include "cuadruple.h"

class CuaLogic : public Cuadruple
{
public:
    CuaLogic();
    CuaLogic(int, QString, QString, QString, QString);
    ~CuaLogic();
    virtual void doOperation(QString &, QMap<QString, QString> &, int &);
};

#endif // CUALOGIC_H
