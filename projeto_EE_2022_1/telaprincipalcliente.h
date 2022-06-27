#ifndef TELAPRINCIPALCLIENTE_H
#define TELAPRINCIPALCLIENTE_H

#include "telaprincipal.h"

namespace Ui {
class TelaPrincipalCliente;
}

class TelaPrincipalCliente : public TelaPrincipal
{
    Q_OBJECT

public:
    explicit TelaPrincipalCliente(QWidget *parent = nullptr);
    ~TelaPrincipalCliente();

private:
    Ui::TelaPrincipalCliente *ui;
};

#endif // TELAPRINCIPALCLIENTE_H
