#ifndef CHANGE_RECORD_H
#define CHANGE_RECORD_H

#include <QDialog>

namespace Ui {
class ChangeRecord;
}

/*!
 * \brief Окно изменения записи
 *
 * Окно служит для изменения записей в одну из 3 таблиц
*/
class ChangeRecord : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeRecord(QWidget *parent = nullptr);
    ~ChangeRecord();

private slots:
    void on_BankRecordButton_clicked();

    void on_BranchRecordButton_clicked();

    void on_ContactInfoRecordButton_clicked();

private:
    Ui::ChangeRecord *ui;
};

#endif // CHANGE_RECORD_H
