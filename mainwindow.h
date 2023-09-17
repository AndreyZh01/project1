#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*!
 * \brief Основное окно
 *
 * Окно служит абсолютно всю логику работы с приложением
 * Внутри данного окна живет логика подключения к базе данных,
 * отключение, изменение данных, отображение, изменение языка
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void ChangeStateFromConnection();
    void LoadRecords();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ConnectDatabase_triggered();

    void on_DisconnectDatabase_triggered();

    void on_AboutAuthor_triggered();

    void on_IDE_triggered();

    void on_ReloadTables_triggered();

    void on_AddRecord_triggered();

    void on_DeleteRecord_triggered();

    void on_ChangeRecord_triggered();

    void on_RussianChange_triggered();

    void on_EnglishChange_triggered();

    /// Чтение заданных настроек
    void readSettings();

    /// Запись настроек
    void writeSettings();

private:
    Ui::MainWindow *ui;
    QTranslator translator;
};
#endif // MAINWINDOW_H
