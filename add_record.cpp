#include "add_record.h"
#include "ui_add_record.h"
#include "database.h"

#include <QSqlQuery>
#include <QSqlError>

AddRecord::AddRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecord)
{
    ui->setupUi(this);
}

AddRecord::~AddRecord()
{
    delete ui;
}

/*!
Вызывается после нажатия кнопки в окне добавления записей.
Добавляет запись в таблице banks, взяв данные из полей ввода
*/
void AddRecord::on_BankRecordButton_clicked() {
    Database* connection = Database::getInstance();
    if (connection->IsConnectionAlive()) {
        QString name = this->ui->nameLine->text();
        QString country = this->ui->countryLine->text();
        QString currency_code = this->ui->currencyLine->text();
        if (name.isEmpty() || country.isEmpty() || currency_code.isEmpty()) {
            QMessageBox::warning(0, failure, all_fields_should_be_exists);
            return;
        }
        QSqlQuery query = connection->AddBankRecord(name, country, currency_code);
        if (!query.lastError().text().isEmpty()) {
            QMessageBox::warning(0, failure, query.lastError().text());
        }
        else {
            QMessageBox::information(0, success, record_successfully_added);
        }
    }
}


/*!
Вызывается после нажатия кнопки в окне добавления записей.
Добавляет запись в таблице branches, взяв данные из полей ввода
*/
void AddRecord::on_BranchRecordButton_clicked() {
    Database* connection = Database::getInstance();
    if (connection->IsConnectionAlive()) {
        QString bank_id = this->ui->bankLine->text();
        QString city = this->ui->cityLine->text();
        QString street = this->ui->streetLine->text();
        QString building_number = this->ui->buildingNumberLine->text();
        QString postal_code = this->ui->postalCodeLine->text();
        if (bank_id.isEmpty() || city.isEmpty() || street.isEmpty() || building_number.isEmpty() || postal_code.isEmpty()) {
            QMessageBox::warning(0, failure, all_fields_should_be_exists);
            return;
        }
        QSqlQuery query = connection->AddBranchRecord(bank_id, city, street, building_number, postal_code);
        if (!query.lastError().text().isEmpty()) {
            QMessageBox::warning(0, failure, query.lastError().text());
        }
        else {
            QMessageBox::information(0, success, record_successfully_added);
        }
    }
}


/*!
Вызывается после нажатия кнопки в окне добавления записей.
Добавляет запись в таблице contact_info, взяв данные из полей ввода
*/
void AddRecord::on_ContactInfoRecordButton_clicked() {
    Database* connection = Database::getInstance();
    if (connection->IsConnectionAlive()) {
        QString branch_id = this->ui->branchIdLine->text();
        QString phone_number = this->ui->phoneNumberLine->text();
        QString email = this->ui->emailLine->text();
        QString website = this->ui->websiteLine->text();
        if (branch_id.isEmpty() || phone_number.isEmpty() || email.isEmpty() || website.isEmpty()) {
            QMessageBox::warning(0, failure, all_fields_should_be_exists);
            return;
        }
        QSqlQuery query = connection->AddContactInfoRecord(branch_id, phone_number, email, website);
        if (!query.lastError().text().isEmpty()) {
            QMessageBox::warning(0, failure, query.lastError().text());
        }
        else {
            QMessageBox::information(0, success, record_successfully_added);
        }
    }
}

