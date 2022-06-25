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

        int linha = 0;
        ui->tableWidgetFuncionario->setColumnCount(8);

        while(pegaDados.next()){

            ui->tableWidgetFuncionario->insertRow(linha);

            for(int i = 0; i < 8; i++){

                ui->tableWidgetFuncionario->setItem(linha, i, new QTableWidgetItem(pegaDados.value(i).toString()));

            }

            ui->tableWidgetFuncionario->setRowHeight(linha, 40);

            linha++;
        }

        //coloca os títulos na tabela
        QStringList titulos = {"ID", "CPF", "Nome", "Salário", "Departamento", "Data Nascimento", "Telefone", "E-mail"};

        ui->tableWidgetFuncionario->setHorizontalHeaderLabels(titulos);

        //oculta os números das linhas que ficaram a esquerda
        ui->tableWidgetFuncionario->verticalHeader()->setVisible(false);

        //ajusta a largura das colunas
        ui->tableWidgetFuncionario->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
        ui->tableWidgetFuncionario->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);

        //desabilita a edição dos dados direto na tablewidgetFuncionario
        ui->tableWidgetFuncionario->setEditTriggers(QAbstractItemView::NoEditTriggers);

        //seleciona a linha inteira da tablewidgetFuncionario
        ui->tableWidgetFuncionario->setSelectionBehavior(QAbstractItemView::SelectRows);

        //mudar a cor dos títulos da tabela
        ui->tableWidgetFuncionario->setStyleSheet("QHeaderView::section {color: white; background-color: #55aa7f}");


    }else{

        QMessageBox::information(this, "Atenção", "Erro ao carregar os funcionários!");
    }

}
