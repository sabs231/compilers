#ifndef CUAINDEX_H
#define CUAINDEX_H

#include "cuadruple.h"

class CuaIndex : public Cuadruple
{
public:
    CuaIndex();
    CuaIndex(int, QString, QString, QString, QString);
    ~CuaIndex();
    virtual void doOperation(QString &, QMap<QString, QString> &, int &);
};

#endif // CUAINDEX_H
