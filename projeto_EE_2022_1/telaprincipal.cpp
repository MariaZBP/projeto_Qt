#include "telaprincipal.h"
#include "ui_telaprincipal.h"
#include <QtSql>
#include <QMessageBox>
#include "cadastrofuncionarios.h"
#include "editarfuncionario.h"
#include <QVector>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

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

    ui->comboBoxColunaFiltro->setStyleSheet("color: black;"
                                               "background-color: #aaff7f;"
                                               "selection-color: black;"
                                               "selection-background-color: #aaff7f;");

    ui->btnCadastrarFuncionario->setStyleSheet(
                "color: black;"
                "background-color: #00ff7f;"
                "border-style: outset;"
                "border-width: 2px;"
                "border-radius: 10px;"
                "border-color: white;"
                "font: bold 16px;");

    ui->btnExcluirFuncionario->setStyleSheet(
                "color: black;"
                "background-color: #00ff7f;"
                "border-style: outset;"
                "border-width: 2px;"
                "border-radius: 10px;"
                "border-color: white;"
                "font: bold 16px;");

    ui->btnExportarExcel->setStyleSheet(
                "color: black;"
                "background-color: #aaffff;"
                "border-style: outset;"
                "border-width: 2px;"
                "border-radius: 10px;"
                "border-color: white;"
                "font: bold 16px;");

    QFont fonte = ui->lblTotalSalarios->font();
    fonte.setPointSize(10);
    fonte.setBold(true);
    ui->lblTotalSalarios->setFont(fonte);
    ui->lblMaiorSalario->setFont(fonte);

    //mudar a cor do texto
    QPalette paleta = ui->lblTotalSalarios->palette();
    paleta.setColor(ui->lblTotalSalarios->foregroundRole(), Qt::blue);
    ui->lblTotalSalarios->setPalette(paleta);
    ui->lblMaiorSalario->setPalette(paleta);

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

    QString colunaFiltro = ui->comboBoxColunaFiltro->currentText();

    QString textoPesquisa = ui->txtPesquisarFuncionario->text();

    if(colunaFiltro == "ID"){

        //digitando parte do nome o like já trás ele
        //%-> começa em qualquer valor e termina em qualquer valor
        pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where idFuncionario like '%"+textoPesquisa+"%'";

    }else if(colunaFiltro == "CPF"){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where cpfFuncionario like '%"+textoPesquisa+"%'";

    }else if(colunaFiltro == "Nome"){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where nomeFuncionario like '%"+textoPesquisa+"%'";

    }else if(colunaFiltro == "Salário"){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where salarioFuncionario like '%"+textoPesquisa+"%'";

    }else if(colunaFiltro == "Departamento"){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where departamentoFuncionario like '%"+textoPesquisa+"%'";

    }else if(colunaFiltro == "Data de Nascimento"){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where dataNascimentoFuncionario like '%"+textoPesquisa+"%'";

    }else if(colunaFiltro == "Telefone"){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where telefoneFuncionario like '%"+textoPesquisa+"%'";

    }else if(colunaFiltro == "Email"){

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where emailFuncionario like '%"+textoPesquisa+"%'";

    }else{

            pesquisa = "Select idFuncionario, cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario From Funcionarios where idFuncionario like '%"+textoPesquisa+"%'";

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

void TelaPrincipal::on_btnExportarExcel_clicked()
{

    //caminha arquivo para salvar
    auto nomeArquivo = QFileDialog::getSaveFileName(this, "Salvar", QDir::rootPath(), "CSV File (*.csv)");

    if(nomeArquivo.isEmpty()){

        //fecha se não estiver selecionado o caminho
        return;

    }

    //QIODevice::WriteOnly = o arquivo está aberto para escrita
    //QIODevice::Text = ao ler e escrever pula sempre para próxima linha
    QFile file(nomeArquivo);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){

        return;

    }

    //a classe QTextStream cria uma interface amigável para leitura e escrita dos dados
    QTextStream arquivoExcel(&file);

    int linha = 0;

    //contagem de linhas e colunas preenchidas
    const int quantidadeLinhas = ui->tableWidgetFuncionario->rowCount();
    const int quantidadeColunas= ui->tableWidgetFuncionario->columnCount();

    for(linha; linha < quantidadeLinhas; linha++){

        //pega as informações
        arquivoExcel << getValueAt(linha, 0);

        for(int coluna = 1; coluna < quantidadeColunas; coluna++){

            //inserindo as informações no excel
            arquivoExcel << "," << getValueAt(linha, coluna);

        }

        arquivoExcel << "\n";

    }

    //limpa
    file.flush();

    //fecha
    file.close();

    QMessageBox::information(this, "Atenção", "Relatório exportado com sucesso!");

}

QString TelaPrincipal::getValueAt(int linha, int coluna){

    if(!ui->tableWidgetFuncionario->item(linha, coluna)){

        //se estiver limpa a tableWidgetFuncionario salva o arquivo em branco
        return "";

    }else{

        //retorna as informações da posição da linha e da coluna
        return  ui->tableWidgetFuncionario->item(linha, coluna)->text();

    }

}
