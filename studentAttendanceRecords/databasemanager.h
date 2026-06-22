#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QList>
#include <QVariant>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager& instance();
    bool init();
    bool connect();
    void disconnect();

    // Группы
    bool addGroup(const QString& name);
    QList<QStringList> getAllGroups();
    bool deleteGroup(const QString& name);

    // Студенты
    bool addStudent(const QString& name, const QString& groupName);
    QList<QStringList> getStudentsByGroup(const QString& groupName);
    QList<QStringList> getAllStudents();

    // Посещаемость
    bool markAttendance(int studentId, int lessonId, bool status, const QString& date);
    QList<QStringList> generateReport(const QString& groupName, const QString& startDate, const QString& endDate);

private:
    DatabaseManager() = default;
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    ~DatabaseManager();

    QSqlDatabase m_db;
    bool m_isConnected = false;

    void createTables();
    void insertTestData();
    bool executeQuery(const QString& query, const QVariantList& params = {});
};

#endif // DATABASEMANAGER_H