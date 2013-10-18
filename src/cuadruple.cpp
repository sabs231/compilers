#include <iostream>
#include "cuadruple.h"

Cuadruple::Cuadruple()
{
    this->id = 0;
    this->first = "";
    this->second = "";
    this->third = "";
    this->fourth = "";
}

Cuadruple::Cuadruple(int i, QString f, QString s, QString t, QString fo)
{
    this->id = i;
    this->first = f.remove('(');
    this->second = s;
    this->third = t;
    this->fourth = fo.remove(')');
}

Cuadruple::~Cuadruple()
{
}

QString & Cuadruple::getFirst()
{
    return (this->first);
}

QString & Cuadruple::getSecond()
{
    return (this->second);
}

QString & Cuadruple::getThird()
{
    return (this->third);
}

QString & Cuadruple::getFourth()
{
    return (this->fourth);
}

void Cuadruple::setFirst(QString str)
{
    this->first = str;
}

void Cuadruple::setSecond(QString str)
{
    this->second = str;
}

void Cuadruple::setThird(QString str)
{
    this->third = str;
}

void Cuadruple::setFourth(QString str)
{
    this->fourth = str;
}

QString Cuadruple::toString() const
{
    return QString("(" + this->first + "," + this->second + "," + this->third + "," + this->fourth + ")");
}
