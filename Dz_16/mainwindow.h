#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QTabWidget>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QStringList>
#include <QList>

// Структура для хранения данных пользователя
struct UserData
{
    QString login;
    QString password;
    QString email;
    QString phone;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Вкладка 1: Авторизация
    void onRegisterClicked();
    void onLoginClicked();
    void onClearClicked();
    void onLoginTextChanged(const QString &text);
    void onPasswordTextChanged(const QString &text);
    void onEmailTextChanged(const QString &text);
    void onPhoneTextChanged(const QString &text);

    // Вкладка 2: Замена чисел
    void onReplaceClicked();
    void onClearTextClicked();

private:
    void setupUI();
    QWidget* createAuthTab();
    QWidget* createReplaceTab();
    void checkFormValidity();

    // Валидация
    bool validateLogin(const QString &login);
    bool validatePassword(const QString &password);
    bool validateEmail(const QString &email);
    bool validatePhone(const QString &phone);
    bool isUserExists(const QString &login);
    bool authenticateUser(const QString &login, const QString &password);
    void addUser(const UserData &user);

    // Замена чисел
    QString replaceNumbersWithWords(const QString &text);
    QString numberToWord(int num);

    // Данные
    QList<UserData> m_users;
    int m_userCount;

    // Виджеты вкладки авторизации
    QLineEdit *lineEditLogin;
    QLineEdit *lineEditPassword;
    QLineEdit *lineEditEmail;
    QLineEdit *lineEditPhone;
    QPushButton *btnRegister;
    QPushButton *btnLogin;
    QPushButton *btnClear;
    QLabel *labelStatus;
    QTableWidget *tableUsers;

    // Виджеты вкладки замены
    QTextEdit *textEditInput;
    QTextEdit *textEditOutput;
    QPushButton *btnReplace;
    QPushButton *btnClearText;
    QLabel *labelReplaceStatus;
};

#endif // MAINWINDOW_H