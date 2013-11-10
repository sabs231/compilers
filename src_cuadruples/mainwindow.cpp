#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cuadruple.h"
#include "cuaprint.h"
#include "cuaarithmetic.h"
#include "cualogic.h"
#include "cuaend.h"
#include "cuaasign.h"
#include "cuagoto.h"
#include "cuaifnot.h"
#include "cuaindex.h"
#include <QVector>
#include <QDebug>
#include <QMap>
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_compileButton_clicked()
{
    int id = 1;
    int programCounter = 1;
    QString code;
    QStringList list;
    QString res;
    QStringList current;
    QString currentCua;
    std::string actualStr;
    QStringList::Iterator it;
    Cuadruple *c;
    QMap<QString, QString> temporals;
    QMap<int, Cuadruple *> cuadruples;

    code = ui->codeEdit->toPlainText();
    list = code.split("\n");
    for (it = list.begin(); it != list.end(); ++it)
    {
        currentCua = *it;
        if (currentCua != NULL)
        {
            current = currentCua.split(",");
            const_cast<QString &>(current.at(0)).remove('(');
            actualStr = current.at(0).toStdString();
            if (actualStr == "+" || actualStr == "-" || actualStr == "*" || actualStr == "/" || actualStr == "%")
            {
              c = new CuaArithmetic(id, current.at(0), current.at(1), current.at(2), current.at(3));
              cuadruples.insert(id, c);
              id++;
            }
            else if (actualStr == "PRINT")
            {
              const_cast<QString &>(current.at(1)).remove(QChar('"'));
              c = new CuaPrint(id, current.at(0), current.at(1), current.at(2), current.at(3));
              cuadruples.insert(id, c);
              id++;
            }
            else if (actualStr == "==" || actualStr == "<" || actualStr == ">")
            {
                c = new CuaLogic(id, current.at(0), current.at(1), current.at(2), current.at(3));
                cuadruples.insert(id, c);
                id++;
            }
            else if (actualStr == "END")
            {
                c = new CuaEnd(id, current.at(0), current.at(1), current.at(2), current.at(3));
                cuadruples.insert(id, c);
                id++;
            }
            else if (actualStr == "=")
            {
                const_cast<QString &>(current.at(2)).remove(QChar('"'));
                c = new CuaAsign(id, current.at(0), current.at(1), current.at(2), current.at(3));
                cuadruples.insert(id, c);
                id++;
            }
            else if (actualStr == "[]")
            {
                c = new CuaIndex(id, current.at(0), current.at(1), current.at(2), current.at(3));
                cuadruples.insert(id, c);
                id++;
            }
            else if (actualStr == "IFN")
            {
                c = new CuaIfnot(id, current.at(0), current.at(1), current.at(2), current.at(3));
                cuadruples.insert(id, c);
                id++;
            }
            else if (actualStr == "GOTO")
            {
                c = new CuaGoto(id, current.at(0), current.at(1), current.at(2), current.at(3));
                cuadruples.insert(id, c);
                id++;
            }
        }
    }
    qDebug() << "cuadruples size: " << cuadruples.size();
    while (cuadruples[programCounter]->getFirst().toStdString() != "END")
    {
      if (cuadruples[programCounter])
      {
        cuadruples[programCounter]->toString();
        cuadruples[programCounter]->doOperation(res, temporals, programCounter);
      }
      else
        qDebug() << "Nul value :/";
    }
    for (auto e : temporals.keys())
    {
        qDebug() << e << "==>" << temporals.value(e);
    }
    qDebug() << "res: " << res;
    ui->resultWindow->setText(res.toHtmlEscaped());
    ui->webView->setHtml(res);
}
