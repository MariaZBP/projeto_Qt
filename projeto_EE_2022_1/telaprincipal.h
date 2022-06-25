#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class TelaPrincipal;
}

class TelaPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit TelaPrincipal(QWidget *parent = nullptr);
    ~TelaPrincipal();

    void carregarDados();

    void limparTableWidget(QTableWidget *limpaTW);

private slots:
    void on_txtPesquisarFuncionario_textChanged(const QString &arg1);

    void on_btnCadastrarFuncionario_clicked();

    void on_btnExcluirFuncionario_clicked();

private:
    Ui::TelaPrincipal *ui;
};

#endif // TELAPRINCIPAL_H
