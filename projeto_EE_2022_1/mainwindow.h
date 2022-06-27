#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <telaprincipal.h>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::MainWindow *ui;
};

#endif  //MAINWINDOW_H
