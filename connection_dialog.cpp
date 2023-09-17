#include "connection_dialog.h"
#include "ui_connection_dialog.h"
#include "database.h"

#include <QString>

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    ui->PasswordLine->setEchoMode(QLineEdit::Password);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

/*!
Производит подключение к базе данных. Если подключение
прошло успешно, то окно закрывается.
*/
void ConnectionDialog::on_Connect_clicked()
{
    Database* connection = Database::getInstance();
    QString host = this->ui->HostLine->text();
    int port = this->ui->PortLine->text().toInt();
    QString user = this->ui->UserLine->text();
    QString user_password = this->ui->PasswordLine->text();
    QString database = this->ui->DatabaseLine->text();
    connection->ConnectToDatabase(database, user, user_password, host, port);
    if (connection->IsConnectionAlive()) {
        this->close();
    }
}
