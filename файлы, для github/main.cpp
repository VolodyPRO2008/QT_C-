#include <QApplication>
#include <QMessageBox>
#include "loginwidget.h"
#include "mainwindow.h"
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!DatabaseManager::instance().init()) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось инициализировать базу данных!");
        return -1;
    }

    LoginWidget loginWidget;
    loginWidget.show();

    QObject::connect(&loginWidget, &LoginWidget::loginSuccess, [&](const UserInfo& user) {
        loginWidget.hide();
        MainWindow* mainWindow = new MainWindow(user);
        mainWindow->show();
    });

    return app.exec();
}