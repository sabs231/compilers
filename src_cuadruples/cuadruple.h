#ifndef CUADRUPLE_H
#define CUADRUPLE_H

#include <string>
#include <QString>
#include <QMap>

class Cuadruple
{
protected:
    int     id;
    QString first;
    QString second;
    QString third;
    QString fourth;

public:
    Cuadruple();
    Cuadruple(int, QString, QString, QString, QString);
    ~Cuadruple();
    QString & getFirst();
    QString & getSecond();
    QString & getThird();
    QString & getFourth();
    void setFirst(QString);
    void setSecond(QString);
    void setThird(QString);
    void setFourth(QString);
    void toString() const;
    virtual void doOperation(QString &, QMap<QString, QString> &, int &) = 0;
};

#endif // CUADRUPLE_H
