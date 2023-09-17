#include "database.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

Database* Database::database;

/*!
Возвращает существующий объект класса. Если его
нет, то создает.
*/
Database* Database::getInstance() {
    if (database == nullptr) {
        database = new Database();
    }
    return database;
}

Database::~Database() {
    if (connection.isOpen()) {
        connection.close();
    }
}

/*!
Проверяет, существует ли на данный момент подключение к базе данных
*/
bool Database::IsConnectionAlive() {
    return connection.isOpen();
};

/*!
Производит отключение от базы данных
*/
void Database::Disconnect() {
    if (connection.isOpen()) {
        connection.close();
    }
}

/*!
Производит подключение к базе
*/
void Database::ConnectToDatabase(
    QString database_name, QString user,
    QString user_password, QString host,
    int port
) {
    connection.setHostName(host);
    connection.setPort(port);
    connection.setDatabaseName(database_name);
    connection.open(user, user_password);
    if (connection.isOpen()) {
        QMessageBox::information(0, success, connection_is_success);
    } else {
        QMessageBox::warning(0, failure, database_is_not_connected);
    }
}

/*!
Получение всех записей банков из сырых данных
\return Список структур банков
*/
std::vector<Bank> Database::GetAllBanks() {
    std::vector<Bank> banks;
    if (connection.isOpen()) {
        QSqlQuery query = connection.exec(all_records_from_banks);
        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString country = query.value(2).toString();
            QString currency_code = query.value(3).toString();
            banks.push_back(Bank(id, name, country, currency_code));
        }
    }
    return banks;
}

/*!
Получение всех записей филиалов из сырых данных
\return Список структур филиалов
*/
std::vector<Branch> Database::GetAllBranches() {
    std::vector<Branch> branches;
    if (connection.isOpen()) {
        QSqlQuery query = connection.exec(all_records_from_branches);
        while (query.next()) {
            int id = query.value(0).toInt();
            int bank_id = query.value(1).toInt();
            QString city = query.value(2).toString();
            QString street = query.value(3).toString();
            QString building_number = query.value(4).toString();
            QString postal_code = query.value(5).toString();
            branches.push_back(Branch(id, bank_id, city, street, building_number, postal_code));
        }
    }
    return branches;
}

/*!
Получение всех записей контактной информации из сырых данных
\return Список структур контактной информации
*/
std::vector<ContactInfo> Database::GetAllContactsInfo() {
    std::vector<ContactInfo> contacts;
    if (connection.isOpen()) {
        QSqlQuery query = connection.exec(all_records_from_contacts);
        while (query.next()) {
            int id = query.value(0).toInt();
            int branch_id = query.value(1).toInt();
            QString phone_number = query.value(2).toString();
            QString email = query.value(3).toString();
            QString website = query.value(4).toString();
            contacts.push_back(ContactInfo(id, branch_id,phone_number, email, website));
        }
    }
    return contacts;
}

/*!
Добавляет запись в таблицу банков
\return Выполненный запрос
*/
QSqlQuery Database::AddBankRecord(QString name, QString country, QString currency_code) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query = connection.exec(add_bank_record.arg(name, country, currency_code));
    }
    return query;
}

/*!
Добавляет запись в таблицу филиалов
\return Выполненный запрос
*/
QSqlQuery Database::AddBranchRecord(
    QString bank_id,
    QString city,
    QString street,
    QString building_number,
    QString postal_code) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query = connection.exec(add_branch_record.arg(bank_id, city, street, building_number, postal_code));
    }
    return query;
}

/*!
Добавляет запись в таблицу контактной информации
\return Выполненный запрос
*/
QSqlQuery Database::AddContactInfoRecord (QString branch_id, QString phone_number, QString email, QString website) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query = connection.exec(add_contact_info.arg(branch_id, phone_number, email, website));
    }
    return query;
}

/*!
Удаляет запись из таблицы банков
\return Выполненный запрос
*/
QSqlQuery Database::RemoveBankRecord(int bank_id) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query = connection.exec(remove_bank_record.arg(bank_id));
    }
    return query;
}

/*!
Удаляет запись из таблицы филиалов
\return Выполненный запрос
*/
QSqlQuery Database::RemoveBranchRecord(int branch_id) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query = connection.exec(remove_branch_record.arg(branch_id));
    }
    return query;
}

/*!
Удаляет запись из таблицы контактной информации
\return Выполненный запрос
*/
QSqlQuery Database::RemoveContactInfoRecord(int contact_info_id) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query = connection.exec(remove_contact_info_record.arg(contact_info_id));
    }
    return query;
}

/*!
Обновляет запись в таблице банков
\return Выполненный запрос
*/
QSqlQuery Database::UpdateBankRecord(int bank_id, QString name, QString country, QString currency_code) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query.prepare(update_bank_record);
        query.bindValue(":bank_id", bank_id);
        query.bindValue(":name", name);
        query.bindValue(":country", country);
        query.bindValue(":currency_code", currency_code);
        query.exec();
    }
    return query;
}

/*!
Обновляет запись в таблице филиалов
\return Выполненный запрос
*/
QSqlQuery Database::UpdateBranchRecord(int branch_id, int bank_id, QString city, QString street, QString building_number, QString postal_code) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query.prepare(update_branch_record);
        query.bindValue(":branch_id", branch_id);
        if (bank_id != 0) {
            query.bindValue(":bank_id", bank_id);
        }
        query.bindValue(":city", city);
        query.bindValue(":street", street);
        query.bindValue(":building_number", building_number);
        query.bindValue(":postal_code", postal_code);
        query.exec();
    }
    return query;
}

/*!
Обновляет запись в таблице контактной информации
\return Выполненный запрос
*/
QSqlQuery Database::UpdateContactInfoRecord(int contact_info_id, int branch_id, QString phone_number, QString email, QString website) {
    QSqlQuery query;
    if (connection.isOpen()) {
        query.prepare(update_contact_info_record);
        query.bindValue(":contact_info_id", contact_info_id);
        query.bindValue(":branch_id", branch_id);
        query.bindValue(":phone_number", phone_number);
        query.bindValue(":email", email);
        query.bindValue(":website", website);
        query.exec();
    }
    return query;
}
