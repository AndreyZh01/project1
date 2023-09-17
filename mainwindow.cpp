#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection_dialog.h"
#include "database.h"
#include "add_record.h"
#include "delete_record.h"
#include "change_record.h"

#include <QDebug>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QTranslator>
#include <QSettings>

/*!
Конструктор класса MainWindow. Настраивает отображение,
читает настройки и изменяет состояние окон (если подключение
к базе есть, то окна работы с базой будут активными, иначе - нет)
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    readSettings(); // Запуск метода для чтения сохраненных параметров окна
    ChangeStateFromConnection();  // Изменение состояний окон
}

/*!
Вызывается после нажатия кнопки в окне удаления записей.
Удаляет запись в таблице contact_info, взяв данные из полей ввода
*/
MainWindow::~MainWindow() {
    writeSettings();  // Сохранение настроек
    delete ui;
}

/*!
Изменяет состояние окон, которые связаны с работой записей
в базе данных. Устанавливает setEnabled (возможность
нажать на кнопку) в соответствующее состояние
*/
void MainWindow::ChangeStateFromConnection() {
    Database* connection = Database::getInstance();
    bool connection_is_available = connection->IsConnectionAlive();
    ui->DisconnectDatabase->setEnabled(connection_is_available);
    ui->AddRecord->setEnabled(connection_is_available);
    ui->DeleteRecord->setEnabled(connection_is_available);
    ui->ChangeRecord->setEnabled(connection_is_available);
    ui->ReloadTables->setEnabled(connection_is_available);
}

/*!
Добавляет записи в ячейки TableWidget каждой из 3 таблиц.
Для этого из текущего подключения вызываем функции:
GetAllBanks - для получения всех записей банков
GetAllBranches - получение всех записей филиалов
GetAllContactsInfo - получение всех записей контактной информации
*/
void MainWindow::LoadRecords() {
    Database* connection = Database::getInstance();
    if (connection->IsConnectionAlive()) {
        std::vector<Bank> banks = connection->GetAllBanks();
        this->ui->BanksView->setRowCount(banks.size());
        for (int i = 0; i<this->ui->BanksView->rowCount();i++) {
            this->ui->BanksView->setItem(i, 0, new QTableWidgetItem(QString::number(banks[i].id)));
            this->ui->BanksView->setItem(i, 1, new QTableWidgetItem(banks[i].name));
            this->ui->BanksView->setItem(i, 2, new QTableWidgetItem(banks[i].country));
            this->ui->BanksView->setItem(i, 3, new QTableWidgetItem(banks[i].currency));
        }

        std::vector<Branch> branches = connection->GetAllBranches();
        this->ui->BranchesView->setRowCount(branches.size());
        for (int i = 0; i<this->ui->BranchesView->rowCount();i++) {
            this->ui->BranchesView->setItem(i, 0, new QTableWidgetItem(QString::number(branches[i].id)));
            this->ui->BranchesView->setItem(i, 1, new QTableWidgetItem(QString::number(branches[i].bank_id)));
            this->ui->BranchesView->setItem(i, 2, new QTableWidgetItem(branches[i].city));
            this->ui->BranchesView->setItem(i, 3, new QTableWidgetItem(branches[i].street));
            this->ui->BranchesView->setItem(i, 4, new QTableWidgetItem(branches[i].building_number));
            this->ui->BranchesView->setItem(i, 5, new QTableWidgetItem(branches[i].postal_code));
        }

        std::vector<ContactInfo> contacts = connection->GetAllContactsInfo();
        this->ui->ContactInfoView->setRowCount(contacts.size());
        for (int i = 0; i<this->ui->ContactInfoView->rowCount();i++) {
            this->ui->ContactInfoView->setItem(i, 0, new QTableWidgetItem(QString::number(contacts[i].id)));
            this->ui->ContactInfoView->setItem(i, 1, new QTableWidgetItem(QString::number(contacts[i].branch_id)));
            this->ui->ContactInfoView->setItem(i, 2, new QTableWidgetItem(contacts[i].phone_number));
            this->ui->ContactInfoView->setItem(i, 3, new QTableWidgetItem(contacts[i].email));
            this->ui->ContactInfoView->setItem(i, 4, new QTableWidgetItem(contacts[i].website));
            }
    }
}

/*!
Вызывает окно подключения к базе данных, после чего
обновляет состояние кнопок относительно подключения к базе
*/
void MainWindow::on_ConnectDatabase_triggered() {
    auto dialog = ConnectionDialog(this);
    dialog.exec();
    ChangeStateFromConnection();
}


/*!
Отключается от базы данных, если существует подключение
*/
void MainWindow::on_DisconnectDatabase_triggered() {
    Database* connection = Database::getInstance();
    if (connection->IsConnectionAlive()) {
        connection->Disconnect();
        ChangeStateFromConnection();
        QMessageBox::information(0, success, connection_is_closed);
    }
}

/*!
Вызов окна "Об авторе"
*/
void MainWindow::on_AboutAuthor_triggered() {
    QMessageBox::about(
        this,
        QTranslator::tr("Об авторе"),
        QTranslator::tr("Данная работа была выполнена Жуковым Андреем ИЦТМС-3-5, 2023.")
    );
}

/*!
Вызов окна "Среда разработки"
*/
void MainWindow::on_IDE_triggered() {
    QMessageBox::aboutQt(this);
}

/*!
Вызов действия "Обновить таблицы/данные"
*/
void MainWindow::on_ReloadTables_triggered() {
    LoadRecords();
}

/*!
Вызов окна "Добавить запись"
*/
void MainWindow::on_AddRecord_triggered() {
    auto dialog = AddRecord(this);
    dialog.exec();
    LoadRecords();
}

/*!
Вызов окна "Удалить запись"
*/
void MainWindow::on_DeleteRecord_triggered() {
    auto dialog = DeleteRecord(this);
    dialog.exec();
    LoadRecords();
}

/*!
Вызов окна "Изменить запись"
*/
void MainWindow::on_ChangeRecord_triggered() {
    auto dialog = ChangeRecord(this);
    dialog.exec();
    LoadRecords();
}

/*!
Производит чтение текущих настроек приложения
*/
void MainWindow::readSettings() {
    QSettings settings("ZhukovAndrey", "Project");

    // Группа для чтения настроек геометрии главного окна
    settings.beginGroup("MainWindowGeometry");
    resize(settings.value("size", QSize(1000, 500)).toSize());
    move(settings.value("position", QPoint(200, 200)).toPoint());
    settings.endGroup();

    // Группа для установки языка
    settings.beginGroup("Language");
    if (settings.value("language", "ru_RU") == "")
        translator.load(":/languages/banks_en_EN.qm");
    else translator.load(":/languages/banks_ru_RU.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    settings.endGroup();
}

/*!
Записывает текущие настройки в группы настроек для последующего чтения
*/
void MainWindow::writeSettings() {
    // Запись настроек
    QSettings settings("ZhukovAndrey", "Project");

    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.endGroup();

    settings.beginGroup("Language");
    settings.setValue("language", translator.language());
    settings.endGroup();
}

/*!
Переключает язык интерфейса на русский
*/
void MainWindow::on_RussianChange_triggered() {
    translator.load(":/languages/banks_ru_RU.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

/*!
Переключает язык интерфейса на английский
*/
void MainWindow::on_EnglishChange_triggered() {
    translator.load(":/languages/banks_en_EN.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}
