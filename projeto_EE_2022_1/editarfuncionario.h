#ifndef EDITARFUNCIONARIO_H
#define EDITARFUNCIONARIO_H

#include <QDialog>

namespace Ui {
class editarFuncionario;
}

class editarFuncionario : public QDialog
{
    Q_OBJECT

public:

    //inserindo o construtor como novo parâmetro do tipo int para poder alterar os dados do funcionário
    explicit editarFuncionario(QWidget *parent = nullptr, int alterarFuncionario_ID = 0);
    ~editarFuncionario();

private:
    Ui::editarFuncionario *ui;
};

#endif // EDITARFUNCIONARIO_H
