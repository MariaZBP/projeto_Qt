#include "editarfuncionario.h"
#include "ui_editarfuncionario.h"

static int idSelecionado;

editarFuncionario::editarFuncionario(QWidget *parent, int alterarFuncionario_ID) :
    QDialog(parent),
    ui(new Ui::editarFuncionario)
{
    ui->setupUi(this);

    QSqlQuery dados;

    idSelecionado = alterarFuncionario_ID;

    QString id = QString::number(alterarFuncionario_ID);

    dados.prepare("SELECT * From Funcionarios where idFuncionario="+id);

    if(dados.exec()){

        dados.first();

        ui->labelEditarFuncionario_ID->setText(dados.value(0).toString());
        ui->labelEditarFuncionario_ID->setStyleSheet("color: black;"
                                                   "background-color: #aaff7f;"
                                                   "selection-color: black;"
                                                   "selection-background-color: #aaff7f;");

        ui->txtEditarFuncionario_CPF->setText(dados.value(1).toString());
        ui->txtEditarFuncionario_Nome->setText(dados.value(2).toString());

        QString valorTexto;
        auto formato = QLocale("de_DE");
        double valorSalario = dados.value(3).toDouble();

        //f = double - casas decimais 2
        valorTexto = formato.toString(valorSalario, 'f', 2);

        ui->txtEditarFuncionario_Salario->setText("R$ " + valorTexto);
        ui->cmbEditarFuncionario_Departamento->setCurrentText(dados.value(4).toString());
        ui->txtEditarFuncionario_DataDeNascimento->setText(dados.value(5).toString());
        ui->txtEditarFuncionario_Telefone->setText(dados.value(6).toString());
        ui->txtEditarFuncionario_Email->setText(dados.value(7).toString());


    }else{

       QMessageBox::critical(this, "Atenção",
                             "Erro ao carregar informações do funcionário!");

    }


}

editarFuncionario::~editarFuncionario()
{
    delete ui;
}

void editarFuncionario::on_txtEditarFuncionario_Salario_editingFinished()
{

    QString valorTexto;

    auto formato = QLocale("de_DE");
    double valorSalario = ui->txtEditarFuncionario_Salario->text().toDouble();

    //f = double - casas decimais 2
    valorTexto = formato.toString(valorSalario, 'f', 2);

    ui->txtEditarFuncionario_Salario->setText("R$ " + valorTexto);

}

void editarFuncionario::on_btnSalvarEdicaoFuncionario_clicked()
{

    QString id = ui->labelEditarFuncionario_ID->text();
    QString cpf = ui->txtEditarFuncionario_CPF->text();
    QString nome = ui->txtEditarFuncionario_Nome->text();

    QString salarioSemVirgula;
    salarioSemVirgula = ui->txtEditarFuncionario_Salario->text();
    //antes = R$ 1.235,10
    //depois = 1235.10
    salarioSemVirgula.replace(0, 3, "");
    salarioSemVirgula.replace(".", "");
    salarioSemVirgula.replace(",", ".");
    QString salario = salarioSemVirgula;

    QString departamento = ui->cmbEditarFuncionario_Departamento->currentText();
    QString dataNascimento = ui->txtEditarFuncionario_DataDeNascimento->text();
    QString telefone = ui->txtEditarFuncionario_Telefone->text();
    QString email = ui->txtEditarFuncionario_Email->text();

    //gravação no BD
    QSqlQuery dados;
    dados.prepare("Update Funcionarios set idFuncionario='"+id+"',"
                                          "cpfFuncionario='"+cpf+"',"
                                          "nomeFuncionario='"+nome+"',"
                                          "salarioFuncionario='"+salario+"',"
                                          "dataNascimentoFuncionario='"+dataNascimento+"',"
                                          "departamentoFuncionario='"+departamento+"',"
                                          "telefoneFuncionario='"+telefone+"',"
                                          "emailFuncionario='"+email+"' where idFuncionario="+QString::number(idSelecionado));

    if(dados.exec()){

        this->close();

    }else{

        QMessageBox::critical(this, "Atenção", "Erro ao salvar as alterações!");

    }

}

void editarFuncionario::on_btnCancelarEdicaoFuncionario_clicked()
{

    close();

}
