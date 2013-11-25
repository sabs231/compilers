#ifndef CUAPRINT_H
#define CUAPRINT_H

#include "cuadruple.h"

class CuaPrint : public Cuadruple
{
public:
    CuaPrint();
    CuaPrint(int, QString, QString, QString, QString);
    ~CuaPrint();
    virtual void doOperation(QString &, QMap<QString, QString> &, int &);
};

#endif // CUAPRINT_H
