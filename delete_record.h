#ifndef DELETE_RECORD_H
#define DELETE_RECORD_H

#include <QDialog>

namespace Ui {
class DeleteRecord;
}

/*!
 * \brief Окно удаления записей
 *
 * Окно служит для удаления записей из 3 таблиц
*/
class DeleteRecord : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteRecord(QWidget *parent = nullptr);
    ~DeleteRecord();

private slots:
    void on_BankRemoveButton_clicked();

    void on_BranchRemoveButton_clicked();

    void on_ContactInfoButton_clicked();

private:
    Ui::DeleteRecord *ui;
};

#endif // DELETE_RECORD_H
