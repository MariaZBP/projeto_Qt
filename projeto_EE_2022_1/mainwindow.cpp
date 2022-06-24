#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <telaprincipal.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("Projeto Final - Técnicas de Programação EE-2022.1"
                               " // Aluna: Maria da Conceição Z. B. Patrício Mat.: 20212610013");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLogin_clicked()
{

    TelaPrincipal abrirTelaPrincipal;
    abrirTelaPrincipal.setModal(true);
    abrirTelaPrincipal.exec();

}
