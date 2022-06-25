#include "telaprincipal.h"
#include "ui_telaprincipal.h"

#include <QtSql>
#include <QMessageBox>

TelaPrincipal::TelaPrincipal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaPrincipal)
{
    ui->setupUi(this);

    ui->txtPesquisarFuncionario->setPlaceholderText("Digite algo para pesquisar");

    ui->txtPesquisarFuncionario->setStyleSheet("color: black;"
                                               "background-color: #aaff7f;"
                                               "selection-color: black;"
                                               "selection-background-color: #aaff7f;");

    ui->btnCadastrarFuncionario->setStyleSheet(
                "colr: white;"
                "background-color: #00ff7f;"
                "border-style: outset;"
                "border-width: 2px;"
                "border-radius: 10px;"
                "border-color: white;"
                "font: bold 14px;");

    ui->btnExcluirFuncionario->setStyleSheet(
                "colr: white;"
                "background-color: #00ff7f;"
                "border-style: outset;"
                "border-width: 2px;"
                "border-radius: 10px;"
                "border-color: white;"
                "font: bold 14px;");

    //marcando e desmarcando rb
    ui->rdNome->setChecked(true);
    ui->rdCPF->setChecked(false);
    ui->rdDepartamento->setChecked(false);

    carregarDados();

}

TelaPrincipal::~TelaPrincipal()
{
    delete ui;
}

void TelaPrincipal::carregarDados(){

    QSqlQuery pegaDados;
    pegaDados.prepare("Select * from Funcionarios");

    if(pegaDados.exec()){


    }else{

        QMessageBox::information(this, "Atenção", "Erro ao carregar os funcionários!");
    }

}
