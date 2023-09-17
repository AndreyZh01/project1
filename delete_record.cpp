#include "delete_record.h"
#include "ui_delete_record.h"
#include "database.h"\

#include <QSqlQuery>
#include <QSqlError>

DeleteRecord::DeleteRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteRecord)
{
    ui->setupUi(this);
}

DeleteRecord::~DeleteRecord()
{
    delete ui;
}

/*!
Вызывается после нажатия кнопки в окне удаления записей.
Удаляет запись в таблице banks, взяв данные из полей ввода
*/
void DeleteRecord::on_BankRemoveButton_clicked() {
    Database* connection = Database::getInstance();
    int bank_id = this->ui->BankIdLine->text().toInt();
    if (bank_id == 0) {
        QMessageBox::warning(0, failure, wrong_data_type);
        return;
    }
    QSqlQuery query = connection->RemoveBankRecord(bank_id);
    if (!query.lastError().text().isEmpty()) {
        QMessageBox::warning(0, failure, query.lastError().text());
    }
    else {
        QMessageBox::information(0, success, record_succesfully_removed);
    }
}

/*!
Вызывается после нажатия кнопки в окне удаления записей.
Удаляет запись в таблице branches, взяв данные из полей ввода
*/
void DeleteRecord::on_BranchRemoveButton_clicked() {
    Database* connection = Database::getInstance();
    int branch = this->ui->BranchLine->text().toInt();
    if (branch == 0) {
        QMessageBox::warning(0, failure, wrong_data_type);
        return;
    }
    QSqlQuery query = connection->RemoveBranchRecord(branch);
    if (!query.lastError().text().isEmpty()) {
        QMessageBox::warning(0, failure, query.lastError().text());
    }
    else {
        QMessageBox::information(0, success, record_succesfully_removed);
    }
}

/*!
Вызывается после нажатия кнопки в окне удаления записей.
Удаляет запись в таблице contact_info, взяв данные из полей ввода
*/
void DeleteRecord::on_ContactInfoButton_clicked() {
    Database* connection = Database::getInstance();
    int contact_info = this->ui->ContactInfoLine->text().toInt();
    if (contact_info == 0) {
        QMessageBox::warning(0, failure, wrong_data_type);
        return;
    }
    QSqlQuery query = connection->RemoveContactInfoRecord(contact_info);
    if (!query.lastError().text().isEmpty()) {
        QMessageBox::warning(0, failure, query.lastError().text());
    }
    else {
        QMessageBox::information(0, success, record_succesfully_removed);
    }
}

