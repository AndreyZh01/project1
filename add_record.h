#ifndef ADD_RECORD_H
#define ADD_RECORD_H

#include <QDialog>

namespace Ui {
class AddRecord;
}

/*!
 * \brief Окно добавления записи
 *
 * Окно служит для добавления записей в одну из 3 таблиц
*/
class AddRecord : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecord(QWidget *parent = nullptr);
    ~AddRecord();

private slots:

    void on_BankRecordButton_clicked();

    void on_BranchRecordButton_clicked();

    void on_ContactInfoRecordButton_clicked();

private:
    Ui::AddRecord *ui;
};

#endif // ADD_RECORD_H
