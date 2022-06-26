#include "telaprincipal.h"
#include "ui_telaprincipal.h"
#include <QtSql>
#include <QMessageBox>
#include "cadastrofuncionarios.h"
#include "editarfuncionario.h"
#include <QVector>

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

void TelaPrincipal::limparTableWidget(QTableWidget *limpaTW){

    while(limpaTW->rowCount() > 0){

        //0 = primeira linha
        limpaTW->removeRow(0);

    }

}

void TelaPrincipal::carregarDados(){

    limparTableWidget(ui->tableWidgetFuncionario);

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

            QString valorTexto;
            QString valorTexto2;
            auto formato = QLocale("de_DE");
            double valorSalario = somarSalarios(ui->tableWidgetFuncionario, 3);
            double valorSalario2 = maiorSalario(ui->tableWidgetFuncionario, 3);

            //f = double - casas decimais 2
            valorTexto = formato.toString(valorSalario, 'f', 2);
            valorTexto2 = formato.toString(valorSalario2, 'f', 2);

           ui->lblTotalSalarios->setText("Total dos Salários: R$ " + valorTexto);
           ui->lblMaiorSalario->setText("Maior Salário: R$ " + valorTexto2);
           ui->lblTotalSalarios->setStyleSheet("color: black;"
                                               "background-color: #aaff7f;"
                                               "selection-color: black;"
                                               "selection-background-color: #aaff7f;");
           ui->lblMaiorSalario->setStyleSheet("color: black;"
                                               "background-color: #aaff7f;"
                                               "selection-color: black;"
                                               "selection-background-color: #aaff7f;");

           ui->lblTotalRegistros->setText("Registros encontrados: " + QString::number(linha));

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

void TelaPrincipal::on_txtPesquisarFuncionario_textChanged(const QString &arg1)
{

    QString pesquisa;

    limparTableWidget(ui->tableWidgetFuncionario);

    QString textoPesquisa = ui->txtPesquisarFuncionario->text();

    if(textoPesquisa == ""){

        if(ui->rdCPF->isChecked()){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios order by cpfFuncionario";

        }else if(ui->rdNome->isChecked()){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios order by nomeFuncionario";

        }else{

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios order by departamentoFuncionario";

        }

    }else{

        if(ui->rdCPF->isChecked()){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where cpfFuncionario = "+textoPesquisa+" order by cpfFuncionario";

        }else if(ui->rdNome->isChecked()){

            //digitando parte do nome o like já trás ele
            //%-> começa em qualquer valor e termina em qualquer valor
            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where nomeFuncionario like '%"+textoPesquisa+"%' order by nomeFuncionario";

        }else{

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where departamentoFuncionario like '%"+textoPesquisa+"%' order by departamentoFuncionario";

        }

    }

    int linha = 0;

    QSqlQuery pegaDados;

    pegaDados.prepare(pesquisa);

    if(pegaDados.exec()){

        while(pegaDados.next()){

            //insere a linha de acordo com a variável linha
            ui->tableWidgetFuncionario->insertRow(linha);

            //passa os itens (linha, coluna, item QTableWidgetItem)
            for(int i = 0; i < 8; i++){

                ui->tableWidgetFuncionario->setItem(linha, i, new QTableWidgetItem(pegaDados.value(i).toString()));

            }

            ui->tableWidgetFuncionario->setRowHeight(linha, 40);

            linha++;

            QString valorTexto;
            QString valorTexto2;
            auto formato = QLocale("de_DE");
            double valorSalario = somarSalarios(ui->tableWidgetFuncionario, 3);
            double valorSalario2 = maiorSalario(ui->tableWidgetFuncionario, 3);

            //f = double - casas decimais 2
            valorTexto = formato.toString(valorSalario, 'f', 2);
            valorTexto2 = formato.toString(valorSalario2, 'f', 2);

            ui->lblTotalSalarios->setText("Total dos Salários: R$ " + valorTexto);
            ui->lblMaiorSalario->setText("Maior Salário: R$ " + valorTexto2);

             ui->lblTotalRegistros->setText("Registros encontrados: " + QString::number(linha));

        }

    }else{

        QMessageBox::information(this, "Atenção", "Erro ao encontrar funcionários!");

    }

}

void TelaPrincipal::on_btnCadastrarFuncionario_clicked()
{

    CadastroFuncionarios abreFormularioCadastro;
    abreFormularioCadastro.exec();

    carregarDados();

}

void TelaPrincipal::on_btnExcluirFuncionario_clicked()
{

    //começa da linha selecionada
    int linhaAtual = ui->tableWidgetFuncionario->currentRow();

    QString idSelecionado = ui->tableWidgetFuncionario->item(linhaAtual, 0)->text();

    QSqlQuery bancoDeDados;

    bancoDeDados.prepare("Delete from Funcionarios where idFuncionario = "+idSelecionado);

    if(bancoDeDados.exec()){

        ui->tableWidgetFuncionario->removeRow(linhaAtual);
        QMessageBox::information(this, "Atenção", "Funcionário excluído com sucesso!");

    }else{

        QMessageBox::information(this, "Atenção", "Erro ao excluir o funcionário!");

    }

}

void TelaPrincipal::on_tableWidgetFuncionario_cellDoubleClicked(int row, int column)
{

    int linhaAtual = ui->tableWidgetFuncionario->currentRow();

    int idFuncionario = ui ->tableWidgetFuncionario->item(linhaAtual, 0)->text().toInt();

    editarFuncionario dadosFuncionario(this, idFuncionario);

    dadosFuncionario.exec();

    //-------------------------------------------

    limparTableWidget(ui->tableWidgetFuncionario);

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

            ui->lblTotalRegistros->setText("Registros encontrados: " + QString::number(linha));
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

double TelaPrincipal::somarSalarios(QTableWidget *tabela, int coluna){

    int totalLinhas;
    double total = 0;

    totalLinhas = tabela->rowCount();

    for(int linha = 0; linha < totalLinhas; linha++){

        total += tabela->item(linha, coluna)->text().toDouble();

    }

    return total;

}

double TelaPrincipal::maiorSalario(QTableWidget *tabela, int coluna){

    int totalLinhas;
    QVector<double> salario;

    totalLinhas = tabela->rowCount();

    for(int linha = 0; linha < totalLinhas; linha++){

        salario.push_back(tabela->item(linha, coluna)->text().toDouble());

    }

    double maiorSalario = salario[0];

    for(int i = 1; i < salario.size(); i++){

        if(salario.at(i) > maiorSalario){

            maiorSalario = salario.at(i);
        }

    }

    return maiorSalario;

}
