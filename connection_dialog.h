#ifndef CONNECTION_DIALOG_H
#define CONNECTION_DIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionDialog;
}

/*!
 * \brief Окно подключения
 *
 * Окно для подключения к базе данных, представляющее собой
 * диалоговое окно с поля ввода необходимых данных для подключения
 * к базе (username, user_password, host и т.д)
*/
class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();

private slots:
    void on_Connect_clicked();

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTION_DIALOG_H
