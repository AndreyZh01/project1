/*!
\file
\brief Заголовочный файл с описанием классов

Данный файл содержит в себе определения основных
классов, используемых для работы с базой
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlResult>
#include <QSqlDatabase>
#include <QTranslator>
#include <QMessageBox>

/*!
 * \brief Структура сущности Банка
 *
 * Данная структура служит для преобразования сырых данных в удобную структуру
*/
struct Bank  {
    int id;
    QString name;
    QString country;
    QString currency;

    Bank (int id, QString name, QString country, QString currency) : id(id), name(name), country(country), currency(currency) {}
};

/*!
 * \brief Структура сущности Филиала
 *
 * Данная структура служит для преобразования сырых данных в удобную структуру
*/
struct Branch {
    int id;
    int bank_id;
    QString city;
    QString street;
    QString building_number;
    QString postal_code;

    Branch (int id, int bank_id, QString city, QString street, QString building_number, QString postal_code) :
        id(id), bank_id(bank_id), city(city), street(street), building_number(building_number), postal_code(postal_code) {}
};

/*!
 * \brief Структура сущности Контактная информация
 *
 * Данная структура служит для преобразования сырых данных в удобную структуру
*/
struct ContactInfo {
    int id;
    int branch_id;
    QString phone_number;
    QString email;
    QString website;

    ContactInfo(int id, int branch_id, QString phone_number, QString email, QString website) :
        id(id), branch_id(branch_id), phone_number(phone_number), email(email), website(website) {}
};

/*!
 * \brief Класс для подключения к базе
 *
 * Данный класс содержит в себе всю логику работы с базой данных, а именно:
 * подключение и отключение от базы, получение записей, добавление, удаление и изменение
 *
 * У класса Database может быть только 1 объект! Это необходимо для быстрого получения текущего
 * соединения в любом месте кода
*/
class Database
{
public:
    // Getters
    std::vector<Bank> GetAllBanks();
    std::vector<Branch> GetAllBranches();
    std::vector<ContactInfo> GetAllContactsInfo();

    // Add records
    QSqlQuery AddBankRecord(QString name, QString country, QString currency_code);
    QSqlQuery AddBranchRecord(QString bank_id,
                              QString city,
                              QString street,
                              QString building_number,
                              QString postal_code);
    QSqlQuery AddContactInfoRecord (QString branch_id, QString phone_number, QString email, QString website);

    // Remove records
    QSqlQuery RemoveBankRecord(int bank_id);
    QSqlQuery RemoveBranchRecord(int branch_id);
    QSqlQuery RemoveContactInfoRecord(int contact_info_id);

    // Change recods
    QSqlQuery UpdateBankRecord(int bank_id, QString name, QString country, QString currency_code);
    QSqlQuery UpdateBranchRecord(int branch_id, int bank_id, QString city, QString street, QString building_number, QString postal_code);
    QSqlQuery UpdateContactInfoRecord(int contact_info_id, int branch_id, QString phone_number, QString email, QString website);

    void Disconnect();
    bool IsConnectionAlive();
    void ConnectToDatabase(QString database_name,
                           QString user,
                           QString user_password,
                           QString host = "localhost",
                           int port = 5432);
    static Database* getInstance();
private:
    QSqlDatabase connection = QSqlDatabase::addDatabase("QPSQL");
    Database() {}
    ~Database();
    Database(Database& /*other*/) {}
    Database& operator=(Database& /*other*/) {}
    static Database * database;
};

// Statuses
const static QString success = QTranslator::tr("Успех!");
const static QString connection_is_success = QTranslator::tr("Подключение прошло успешно");
const static QString connection_is_closed = QTranslator::tr("Подключение успешно разорвано");
const static QString failure = QTranslator::tr("Ошибка!");
const static QString bad_connection = QTranslator::tr("База данных недоступна");
const static QString database_is_not_connected = QTranslator::tr(
    "Убедитесь, что база данных доступна для подключения или данные введены верно"
    );
const static QString query_error = QTranslator::tr("Во время запроса произошла ошибка:\n");
const static QString enexpected_failure = QTranslator::tr("Произошла непредвиденная ошибка");
const static QString record_successfully_added = QTranslator::tr("Запись успешно добавлена");
const static QString all_fields_should_be_exists = QTranslator::tr("Все поля должны быть заполнены");
const static QString wrong_data_type = QTranslator::tr("Поля имееют неверный тип данных для запроса");
const static QString record_succesfully_removed = QTranslator::tr("Запись успешно удалена");
const static QString successfully_updated = QTranslator::tr("Запись успешно обновлена");

// Queries
const static QString all_records_from_banks = R"(
SELECT id, name, country, currency_code FROM banks
ORDER BY id;
)";
const static QString all_records_from_branches = R"(
SELECT id, bank_id, city, street, building_number, postal_code
FROM branches ORDER BY id;
)";
const static QString all_records_from_contacts = R"(
SELECT id, branch_id, phone_number, email, website
FROM contact_info ORDER BY id;
)";
const static QString add_bank_record = R"(
INSERT INTO banks (name, country, currency_code)
VALUES ('%1', '%2', '%3');
)";
const static QString add_branch_record = R"(
INSERT INTO branches (bank_id, city, street, building_number, postal_code)
VALUES ('%1', '%2', '%3', '%4', '%5');
)";
const static QString add_contact_info = R"(
INSERT INTO contact_info (branch_id, phone_number, email, website)
VALUES ('%1', '%2', '%3', '%4');
)";
const static QString remove_bank_record = R"(
DELETE FROM banks CASCADE
WHERE id = %1;
)";
const static QString remove_branch_record = R"(
DELETE FROM branches
WHERE id = %1;
)";
const static QString remove_contact_info_record = R"(
DELETE FROM contact_info
WHERE id = %1;
)";
const static QString update_bank_record = R"(
UPDATE banks
SET
    name = COALESCE(NULLIF(:name, ''), name),
    country = COALESCE(NULLIF(:country, ''), country),
    currency_code = COALESCE(NULLIF(:currency_code, ''), currency_code)
WHERE id = :bank_id;
)";
const static QString update_branch_record = R"(
UPDATE branches
SET
    bank_id = CASE WHEN :bank_id = '' THEN bank_id ELSE :bank_id::integer END,
    city = COALESCE(nullif(:city, ''), city),
    street = COALESCE(nullif(:street, ''), street),
    building_number = COALESCE(nullif(:building_number, ''), building_number),
    postal_code = COALESCE(nullif(:postal_code, ''), postal_code)
WHERE id = :branch_id;
)";
const static QString update_contact_info_record = R"(
UPDATE contact_info
SET
    branch_id =  CASE WHEN :branch_id = '' THEN branch_id ELSE :branch_id::integer END,
    phone_number = COALESCE(NULLIF(:phone_number, ''), phone_number),
    email = COALESCE(NULLIF(:email, ''), email),
    website = COALESCE(NULLIF(:website, ''), website)
WHERE id = :contact_info_id;
)";

#endif // DATABASE_H
