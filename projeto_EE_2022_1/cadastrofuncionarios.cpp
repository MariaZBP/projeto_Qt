#include "cadastrofuncionarios.h"
#include "ui_cadastrofuncionarios.h"
#include <QtSql>
#include <QMessageBox>

CadastroFuncionarios::CadastroFuncionarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CadastroFuncionarios)
{
    ui->setupUi(this);

    //inserindo máscaras nos campos
    ui->txtCadastroFuncionario_CPF->setInputMask("000.000.000-00");
    ui->txtCadastroFuncionario_Telefone->setInputMask("(99) 99999-9999");
    ui->txtCadastroFuncionario_DataDeNascimento->setInputMask("99/99/9999");

    ui->txtCadastroFuncionario_Nome->setPlaceholderText("Digite o nome do funcionário");
    ui->txtCadastroFuncionario_Email->setPlaceholderText("Digite o e-mail do funcionário");

}

CadastroFuncionarios::~CadastroFuncionarios()
{
    delete ui;
}

void CadastroFuncionarios::on_btnSalvarFuncionario_clicked()
{

    QString salarioSemVirgula;

    QString cpf = ui->txtCadastroFuncionario_CPF->text();
    QString nome = ui->txtCadastroFuncionario_Nome->text();

    salarioSemVirgula = ui->txtCadastroFuncionario_Salario->text();

    //antes = 1.235,10
    //depois = 1235.10
    salarioSemVirgula.replace(0, 3, "");
    salarioSemVirgula.replace(".", "");
    salarioSemVirgula.replace(",", ".");

    QString salario = salarioSemVirgula;
    QString departamento = ui->cmbCadastroFuncionario_Departamento->currentText();
    QString dataNascimento = ui->txtCadastroFuncionario_DataDeNascimento->text();
    QString telefone = ui->txtCadastroFuncionario_Telefone->text();
    QString email = ui->txtCadastroFuncionario_Email->text();

    //estrutura para gravar no Banco de Dados
    QSqlQuery dados;
    dados.prepare("Insert into Funcionarios (cpfFuncionario, nomeFuncionario, salarioFuncionario, departamentoFuncionario, "
                  "dataNascimentoFuncionario, telefoneFuncionario, emailFuncionario) values ('"+cpf+"', '"+nome+"','"+salario+"', '"+departamento+"', '"+dataNascimento+"', '"+telefone+"', '"+email+"')");

    if(dados.exec()){

        QMessageBox::information(this, "Aviso",
                                 "Registro salvo com sucesso!");

        this->close();

    }else{

        QMessageBox::information(this, "Atenção",
                                 "Não foi possível salvar as informações no Banco de Dados!");

    }

}

void CadastroFuncionarios::on_txtCadastroFuncionario_Salario_editingFinished()
{

    QString valorTexto;

    auto formato = QLocale("de_DE");
    double valorSalario = ui->txtCadastroFuncionario_Salario->text().toDouble();

    //f = double - casas decimais 2
    valorTexto = formato.toString(valorSalario, 'f', 2);

    ui->txtCadastroFuncionario_Salario->setText("R$ " + valorTexto);

}
