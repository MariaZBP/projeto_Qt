#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <telaprincipal.h>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

//Declara como banco de dados global
static QSqlDatabase bancoDados = QSqlDatabase::addDatabase("QSQLITE");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria a conexão com o banco de dados
    bancoDados.setDatabaseName("C:/Users/Ceiça/Documents/Projeto_Qt/projeto_EE_2022_1/Banco de Dados0.db");

    //Verifica se o banco de dados foi conectado
    if(bancoDados.open()){

        ui->statusBar->showMessage("Banco de dados conectado com sucesso!");

    }else{

        ui->statusBar->showMessage("Erro ao conectar com o banco de dados!");

    }

    //Mensagem de aviso para o usuário
    ui->txtNome->setPlaceholderText("Digite seu nome");
    ui->txtSenha->setPlaceholderText("Digite sua senha");

    ui->btnLogin->setStyleSheet(
                "color: white;"
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                "border-style: outset;"
                "border-width: 2px;"
                "border-radius: 10px;"
                "border-color: white;"
                "font: bold 28px;");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLogin_clicked()
{

    QString nomeUsuario = ui->txtNome->text();
    QString senhaUsuario = ui->txtSenha->text();

    if(bancoDados.isOpen()){

        QSqlQuery consultaNoBancoDeDados;

        //exec -> vai me retornar true se conseguir fazer a pesquisa
        if(consultaNoBancoDeDados.exec("SELECT * FROM Login WHERE nome = '"+nomeUsuario+"' and senha = '"+senhaUsuario+"'")){

            int contaRegistrosEncontrados = 0;

            while(consultaNoBancoDeDados.next()){

                contaRegistrosEncontrados++;

            }

            if(contaRegistrosEncontrados == 1){

                this->close();
                TelaPrincipal abrirTelaPrincipal;
                abrirTelaPrincipal.setModal(true);
                abrirTelaPrincipal.exec();

            }else{

                QMessageBox::critical(this, "Atenção!", "Usuário inválido ou senha inválida!");

            }

        }

    }else{

        QMessageBox::critical(this, "Atenção!", "O Banco de Dados não está aberto!");
        return;
    }

}
