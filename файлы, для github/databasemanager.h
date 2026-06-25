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

// Роли пользователей
enum class UserRole {
    Student = 0,
    Teacher = 1,
    Administrator = 2
};

struct UserInfo {
    int id;
    QString fullName;
    UserRole role;
};

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager& instance();
    bool init();
    bool connect();
    void disconnect();

    // ===== АВТОРИЗАЦИЯ =====
    UserInfo authenticateUser(const QString& fullName);

    // ===== ГРУППЫ =====
    bool addGroup(const QString& name, int course, int year);
    bool updateGroup(int groupId, const QString& name, int course, int year);
    QList<QStringList> getAllGroups();
    bool deleteGroup(const QString& name);

    // ===== СТУДЕНТЫ =====
    bool addStudent(const QString& name, const QString& groupName);
    QList<QStringList> getStudentsByGroup(const QString& groupName);
    QList<QStringList> getAllStudents();
    bool deleteStudent(int studentId);
    bool updateStudentName(int studentId, const QString& newName);

    // ===== ПРЕПОДАВАТЕЛИ =====
    QList<QStringList> getAllTeachers();
    bool addTeacher(const QString& fullName);
    bool deleteTeacher(int teacherId);

    // ===== ПОСЕЩАЕМОСТЬ =====
    bool markAttendance(int studentId, int lessonId, bool status, const QString& date);
    bool updateAttendance(int studentId, int lessonId, bool status, const QString& comment);
    QList<QStringList> getAttendanceForStudent(int studentId);

    // ===== РАСПИСАНИЕ =====
    QList<QStringList> getScheduleForTeacher(int teacherId);
    QList<QStringList> getScheduleForStudent(int studentId);
    bool updateSchedule(const QString& groupName, const QString& discipline, const QString& teacher, const QString& date);

    // ===== ОТЧЁТЫ =====
    QList<QStringList> generateReport(const QString& groupName, const QString& startDate, const QString& endDate);

    // ===== УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ (админ) =====
    QList<QStringList> getAllUsers();
    bool addUser(const QString& fullName, int role, int groupId = -1);
    bool updateUserRole(int userId, int newRole);
    bool deleteUser(int userId);
    bool updateUserFullName(int userId, const QString& newName);
    bool updateStudentGroup(int userId, int newGroupId);  // <-- ДОБАВЛЕНО

    // ===== ВСПОМОГАТЕЛЬНЫЕ =====
    void updateStudentCount(int groupId);

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