#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFrame>
#include <QSqlQuery>
#include "databasemanager.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget* parent = nullptr);

signals:
    void loginSuccess(const UserInfo& user);

private slots:
    void onLoginClicked();
    void onExitClicked();

private:
    QLineEdit* m_fullNameEdit;
    QPushButton* m_loginButton;
    QPushButton* m_exitButton;
    QLabel* m_statusLabel;
};

#endif // LOGINWIDGET_H