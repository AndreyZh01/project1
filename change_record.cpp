#include "change_record.h"
#include "ui_change_record.h"
#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

ChangeRecord::ChangeRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeRecord)
{
    ui->setupUi(this);
}

ChangeRecord::~ChangeRecord()
{
    delete ui;
}

/*!
Вызывается после нажатия кнопки в окне изменения записей.
Изменяет запись в таблице banks, взяв данные из полей ввода
*/
void ChangeRecord::on_BankRecordButton_clicked() {
    int id = this->ui->BankIdLine->text().toInt();
    QString name = this->ui->nameLine->text();
    QString country = this->ui->countryLine->text();
    QString currency_code = this->ui->currencyLine->text();
    Database* connection = Database::getInstance();
    if (id != 0 && connection->IsConnectionAlive()) {
        QSqlQuery query = connection->UpdateBankRecord(id, name, country, currency_code);
        if (!query.lastError().text().isEmpty()) {
            QMessageBox::warning(0, failure, query.lastError().text());
        } else {
            QMessageBox::information(0, success, successfully_updated);
        }
    }
}

/*!
Вызывается после нажатия кнопки в окне изменения записей.
Изменяет запись в таблице branches, взяв данные из полей ввода
*/
void ChangeRecord::on_BranchRecordButton_clicked() {
    int branch_id = this->ui->BranchIdLine->text().toInt();
    int bank_id = this->ui->BankIdRelationLine->text().toInt();
    QString city = this->ui->CityLine->text();
    QString street = this->ui->StreetLine->text();
    QString building_number = this->ui->BuildingNumberLine->text();
    QString postal_code = this->ui->PostalCodeLine->text();
    Database* connection = Database::getInstance();
    if (branch_id != 0 && connection->IsConnectionAlive()) {
        QSqlQuery query = connection->UpdateBranchRecord(branch_id, bank_id, city, street, building_number, postal_code);
        if (!query.lastError().text().isEmpty()) {
            QMessageBox::warning(0, failure, query.lastError().text());
        } else {
            QMessageBox::information(0, success, successfully_updated);
        }
    }
}

/*!
Вызывается после нажатия кнопки в окне изменения записей.
Изменяет запись в таблице contact_info, взяв данные из полей ввода
*/
void ChangeRecord::on_ContactInfoRecordButton_clicked() {
    int contact_info_id = this->ui->ContactInfoIdLine->text().toInt();
    int branch_id = this->ui->BranchIdRelationLine->text().toInt();
    QString phone_number = this->ui->PhoneNumberLine->text();
    QString email = this->ui->EmailLine->text();
    QString website = this->ui->WebsiteLine->text();
    Database* connection = Database::getInstance();
    if (contact_info_id != 0 && connection->IsConnectionAlive()) {
        QSqlQuery query = connection->UpdateContactInfoRecord(contact_info_id, branch_id, phone_number, email, website);
        if (!query.lastError().text().isEmpty()) {
            QMessageBox::warning(0, failure, query.lastError().text());
        } else {
            QMessageBox::information(0, success, successfully_updated);
        }
    }
}

