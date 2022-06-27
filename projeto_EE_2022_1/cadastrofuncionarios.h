#ifndef CADASTROFUNCIONARIOS_H
#define CADASTROFUNCIONARIOS_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class CadastroFuncionarios;
}

class CadastroFuncionarios : public QDialog
{
    Q_OBJECT

public:
    explicit CadastroFuncionarios(QWidget *parent = nullptr);
    ~CadastroFuncionarios();

private slots:
    void on_btnSalvarFuncionario_clicked();

    void on_txtCadastroFuncionario_Salario_editingFinished();

private:
    Ui::CadastroFuncionarios *ui;
};

#endif   //CADASTROFUNCIONARIOS_H
