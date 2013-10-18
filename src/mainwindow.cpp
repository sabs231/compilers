#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cuadruple.h"
#include <QVector>
#include <QDebug>
#include <iostream>

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
    QString code;
    QString tag;
    QStringList list;
    QString res;
    QStringList current;
    QString currentCua;
    QStringList::Iterator it;
    Cuadruple *c;
    QVector<Cuadruple *> cuadruples;
    QVector<Cuadruple *>::Iterator itra;

    code = ui->codeEdit->toPlainText();
    list = code.split("\n");
    for (it = list.begin(); it != list.end(); ++it)
    {
        currentCua = *it;
        if (currentCua != NULL)
        {
            current = currentCua.split(",");
            c = new Cuadruple(id, current.at(0), current.at(1), current.at(2), current.at(3));
            cuadruples.push_back(c);
            id++;
        }
    }

    for (itra = cuadruples.begin(); itra != cuadruples.end(); ++itra)
    {
        if ((*itra)->getFirst() == "PRINT")
        {
            tag = QString((*itra)->getSecond().remove(QChar('"')));
            res.append(tag);
            res.append("\n");
        }
    }
    ui->resultWindow->setText(res.toHtmlEscaped());
    ui->webView->setHtml(res);
}
