#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QDialog>
#include <QTableWidget>
#include <QtSql>
#include <QMessageBox>
#include "cadastrofuncionarios.h"
#include "editarfuncionario.h"
#include <QVector>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>


namespace Ui {
class TelaPrincipal;
}

class TelaPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit TelaPrincipal(QWidget *parent = nullptr);
    ~TelaPrincipal();

    void carregarDadosFuncionarios();

    void carregarDadosClientes();

    void limparTableWidget(QTableWidget *limpaTW);

    double somarSalarios(QTableWidget *tabela, int coluna);

    double maiorSalario(QTableWidget *tabela, int coluna);

private slots:
    void on_txtPesquisarFuncionario_textChanged(const QString &arg1);

    void on_btnCadastrarFuncionario_clicked();

    void on_btnExcluirFuncionario_clicked();

    void on_tableWidgetFuncionario_cellDoubleClicked(int row, int column);

    void on_btnExportarExcel_clicked();

private:
    Ui::TelaPrincipal *ui;

    QString getValueAt(int linha, int coluna);
};

#endif //TELAPRINCIPAL_H
