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
#include "Analex.hh"
#include "Anasin.hh"
#include "CuadrupleGenerator.hh"
#include <QVector>
#include <QDebug>
#include <QMap>
#include <iostream>
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString   rootPath = "~/";

    ui->setupUi(this);
    dirModel = new QFileSystemModel(this);
    fileModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dirModel->setRootPath(rootPath);
    fileModel->setRootPath(rootPath);
    ui->treeView->setModel(dirModel);
    ui->fileView->setModel(fileModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_compileButton_clicked()
{
    int id = 1;
    int programCounter = 1;
    bool isEnd = false;
    QString code;
    QStringList list;
    QString res;
    QStringList current;
    QString currentCua;
    std::string actualStr;
    QStringList::iterator it;
    Cuadruple *c;
    QMap<QString, QString> temporals;
    QMap<int, Cuadruple *> cuadruples;
    QMessageBox msgbox;
    QMap<int, Cuadruple *>::iterator itr;

    code = ui->codeEdit->toPlainText();
    qDebug() << code;
    if (code == "")
    {
        msgbox.setText("You have to write some code");
        msgbox.exec();
        return ;
    }
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
    if (cuadruples.size() == 0)
    {
        msgbox.setText("There are not quadruples");
        msgbox.exec();
        return ;
    }
    for (itr = cuadruples.begin(); itr != cuadruples.end(); ++itr)
    {
      if (itr.value()->getFirst() == "END")
        isEnd = true;
    }
    if (!isEnd)
    {
        msgbox.setText("There is no END cuadruple");
        msgbox.exec();
        return;
    }
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
    qDebug() << "res: " << res;
    ui->resultWindow->appendPlainText(res);
    ui->webView->setHtml(res);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
   QString sPath;

   sPath = dirModel->fileInfo(index).absoluteFilePath();
   ui->fileView->setRootIndex(fileModel->setRootPath(sPath));
}

void MainWindow::on_fileView_clicked(const QModelIndex &index)
{
    this->filePath = fileModel->fileInfo(index).absoluteFilePath();
    ui->pathText->setText(this->filePath);
}

void MainWindow::on_treeView_activated(const QModelIndex &index)
{
}

void MainWindow::on_fileSelect_clicked()
{
}

void MainWindow::on_fileSelectButton_clicked()
{
}

void MainWindow::on_cuaGenButton_clicked()
{
    LexemeTable                       *tab = new LexemeTable();
    Analex                            analex(tab);
    Anasin                            anasin(tab);
    CuadrupleGenerator                cuadrupleGenerator(tab);
    QMessageBox                       msgBox;
    QString                           cuadrupleText;
    std::list<std::string>::iterator  it;

    if (this->filePath.isNull())
    {
        msgBox.setText("There is no file to compile");
        msgBox.exec();
        return ;
    }
    analex.run(this->filePath.toStdString().c_str());
    tab->writeToFile();
    if (anasin.run(tab))
    {
        cuadrupleGenerator.run(tab);
        cuadrupleGenerator.printCuadruples();
        for (it = cuadrupleGenerator.getCuadruples()->begin(); it != cuadrupleGenerator.getCuadruples()->end(); ++it)
        {
          cuadrupleText.append(it->c_str());
          cuadrupleText.append("\n");
        }
        this->ui->codeEdit->setText(cuadrupleText);
    }
    else
    {
        msgBox.setText("The code is incorrect check the log for details");
        msgBox.exec();
        return ;
    }
}
