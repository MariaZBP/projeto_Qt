#include "telaprincipal.h"
#include "ui_telaprincipal.h"

TelaPrincipal::TelaPrincipal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaPrincipal)
{
    ui->setupUi(this);
}

TelaPrincipal::~TelaPrincipal()
{
    delete ui;
}
