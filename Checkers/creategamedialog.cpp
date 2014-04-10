#include <QPushButton>

#include "creategamedialog.h"
#include "ui_creategamedialog.h"
#include "consts.h"


CreateGameDialog::CreateGameDialog(const QString & dialogTitle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGameDialog)
{
    ui->setupUi(this);

    regExpIPValidator = new QRegExpValidator(QRegExp(IP_REG_EXP), ui->addressIPLineEdit);
    ui->addressIPLineEdit->setValidator(regExpIPValidator);
    ui->addressIPLineEdit->setText(PREFFERED_IP_ADDRESS);

    portValidator = new QIntValidator(MINIMAL_PORT_NUMBER, MAXIMAL_PORT_NUMBER, ui->portValue);
    ui->portValue->setValidator(portValidator);
    ui->portValue->setText(QString::number(PREFFERED_PORT_NUMBER));

    this->setWindowTitle(dialogTitle);
}

CreateGameDialog::~CreateGameDialog()
{
    delete ui;
}

int CreateGameDialog::getServerPort()
{
    bool t;
    return ui->portValue->text().toInt(&t, 10);
}

QHostAddress CreateGameDialog::getServerAddress()
{
    QHostAddress serverAddress;
    serverAddress.setAddress(ui->addressIPLineEdit->text());
    return serverAddress;
}


