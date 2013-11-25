#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_compileButton_clicked();

    void on_fileSelectButton_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_fileView_clicked(const QModelIndex &index);

    void on_treeView_activated(const QModelIndex &index);

    void on_fileSelect_clicked();

    void on_cuaGenButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel  *fileModel;
    QFileSystemModel  *dirModel;
    QString           filePath;
};

#endif // MAINWINDOW_H
