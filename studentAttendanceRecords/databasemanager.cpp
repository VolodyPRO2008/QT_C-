#include "databasemanager.h"
#include <QDir>
#include <QDate>

DatabaseManager::~DatabaseManager()
{
    disconnect();
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::init()
{
    QString dbPath = QDir::currentPath() + "/attendance.db";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!connect()) {
        qDebug() << "Failed to connect to database!";
        return false;
    }

    createTables();
    insertTestData();
    return true;
}

bool DatabaseManager::connect()
{
    if (m_db.isOpen()) return true;

    if (!m_db.open()) {
        qDebug() << "Error opening database:" << m_db.lastError().text();
        return false;
    }

    m_isConnected = true;
    qDebug() << "Database connected successfully!";
    return true;
}

void DatabaseManager::disconnect()
{
    if (m_db.isOpen()) {
        m_db.close();
        m_isConnected = false;
    }
}

bool DatabaseManager::executeQuery(const QString& query, const QVariantList& params)
{
    if (!m_isConnected && !connect()) return false;

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query);

    for (int i = 0; i < params.size(); ++i) {
        sqlQuery.bindValue(i, params[i]);
    }

    if (!sqlQuery.exec()) {
        qDebug() << "Query execution failed:" << sqlQuery.lastError().text();
        return false;
    }

    return true;
}

void DatabaseManager::createTables()
{
    QStringList queries = {
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL,"
        "role TEXT NOT NULL,"
        "full_name TEXT NOT NULL)",

        "CREATE TABLE IF NOT EXISTS groups ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT UNIQUE NOT NULL,"
        "course INTEGER NOT NULL,"
        "year INTEGER NOT NULL)",

        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "full_name TEXT NOT NULL,"
        "student_card TEXT UNIQUE NOT NULL,"
        "group_id INTEGER NOT NULL,"
        "FOREIGN KEY (group_id) REFERENCES groups(id) ON DELETE CASCADE)",

        "CREATE TABLE IF NOT EXISTS disciplines ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT UNIQUE NOT NULL,"
        "semester INTEGER NOT NULL,"
        "hours INTEGER NOT NULL)",

        "CREATE TABLE IF NOT EXISTS lessons ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "discipline_id INTEGER NOT NULL,"
        "group_id INTEGER NOT NULL,"
        "teacher TEXT NOT NULL,"
        "lesson_date TEXT NOT NULL,"
        "FOREIGN KEY (discipline_id) REFERENCES disciplines(id),"
        "FOREIGN KEY (group_id) REFERENCES groups(id))",

        "CREATE TABLE IF NOT EXISTS attendance ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "student_id INTEGER NOT NULL,"
        "lesson_id INTEGER NOT NULL,"
        "status INTEGER NOT NULL,"
        "comment TEXT,"
        "FOREIGN KEY (student_id) REFERENCES students(id) ON DELETE CASCADE,"
        "FOREIGN KEY (lesson_id) REFERENCES lessons(id) ON DELETE CASCADE)"
    };

    for (const QString& query : queries) {
        executeQuery(query);
    }
}

void DatabaseManager::insertTestData()
{
    QSqlQuery checkQuery("SELECT COUNT(*) FROM users");
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        qDebug() << "Test data already exists.";
        return;
    }

    QStringList queries = {
        "INSERT INTO users (username, password, role, full_name) VALUES "
        "('admin', 'admin123', 'administrator', 'Иванов Иван Иванович'),"
        "('teacher', 'teacher123', 'teacher', 'Петров Петр Петрович'),"
        "('dean', 'dean123', 'dean_office', 'Сидорова Анна Сергеевна')",

        "INSERT INTO groups (name, course, year) VALUES "
        "('ИС-101', 1, 2025),"
        "('ИС-102', 1, 2025),"
        "('ИС-201', 2, 2024),"
        "('ИС-301', 3, 2023)",

        "INSERT INTO students (full_name, student_card, group_id) VALUES "
        "('Александров Алексей Алексеевич', 'С-001', 1),"
        "('Борисов Борис Борисович', 'С-002', 1),"
        "('Васильева Василиса Васильевна', 'С-003', 1),"
        "('Григорьев Григорий Григорьевич', 'С-004', 2),"
        "('Дмитриева Дарья Дмитриевна', 'С-005', 2),"
        "('Егоров Егор Егорович', 'С-006', 3),"
        "('Жукова Жанна Жановна', 'С-007', 3),"
        "('Зайцев Захар Захарович', 'С-008', 4),"
        "('Иванова Ирина Ивановна', 'С-009', 4)",

        "INSERT INTO disciplines (name, semester, hours) VALUES "
        "('Программирование', 1, 64),"
        "('Базы данных', 1, 48),"
        "('Веб-технологии', 2, 48),"
        "('Тестирование ПО', 2, 32),"
        "('Системный анализ', 3, 48)",

        "INSERT INTO lessons (discipline_id, group_id, teacher, lesson_date) VALUES "
        "(1, 1, 'Петров П.П.', '2026-02-10'),"
        "(1, 1, 'Петров П.П.', '2026-02-17'),"
        "(1, 1, 'Петров П.П.', '2026-02-24'),"
        "(2, 1, 'Сидорова А.С.', '2026-02-12'),"
        "(1, 2, 'Петров П.П.', '2026-02-11'),"
        "(2, 2, 'Сидорова А.С.', '2026-02-13')",

        "INSERT INTO attendance (student_id, lesson_id, status, comment) VALUES "
        "(1, 1, 1, ''), (2, 1, 1, ''), (3, 1, 0, 'Болел'),"
        "(1, 2, 1, ''), (2, 2, 0, 'Опоздал на 15 минут'), (3, 2, 1, ''),"
        "(1, 3, 1, ''), (2, 3, 1, ''), (3, 3, 1, ''),"
        "(4, 5, 1, ''), (5, 5, 0, 'Уважительная причина'),"
        "(4, 6, 1, ''), (5, 6, 1, ''),"
        "(6, 4, 0, 'Не явился')"
    };

    for (const QString& query : queries) {
        executeQuery(query);
    }

    qDebug() << "Test data inserted successfully!";
}

// ==================== ГРУППЫ ====================

bool DatabaseManager::addGroup(const QString& name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO groups (name, course, year) VALUES (?, 1, 2025)");
    query.bindValue(0, name);
    return query.exec();
}

QList<QStringList> DatabaseManager::getAllGroups()
{
    QList<QStringList> groups;
    QSqlQuery query("SELECT id, name, course, year FROM groups");

    if (!query.exec()) return groups;

    while (query.next()) {
        QStringList group;
        group << query.value(0).toString()
              << query.value(1).toString()
              << query.value(2).toString()
              << query.value(3).toString();
        groups.append(group);
    }

    return groups;
}

bool DatabaseManager::deleteGroup(const QString& name)
{
    QSqlQuery query;
    query.prepare("DELETE FROM groups WHERE name = ?");
    query.bindValue(0, name);
    return query.exec();
}

// ==================== СТУДЕНТЫ ====================

bool DatabaseManager::addStudent(const QString& name, const QString& groupName)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM groups WHERE name = ?");
    query.bindValue(0, groupName);

    if (!query.exec() || !query.next()) {
        qDebug() << "Group not found:" << groupName;
        return false;
    }

    int groupId = query.value(0).toInt();

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO students (full_name, student_card, group_id) "
                        "VALUES (?, ?, ?)");
    insertQuery.bindValue(0, name);
    insertQuery.bindValue(1, "С-" + QString::number(QDateTime::currentMSecsSinceEpoch()));
    insertQuery.bindValue(2, groupId);

    return insertQuery.exec();
}

QList<QStringList> DatabaseManager::getStudentsByGroup(const QString& groupName)
{
    QList<QStringList> students;

    QSqlQuery query;
    query.prepare("SELECT s.id, s.full_name, s.student_card, g.name "
                  "FROM students s "
                  "JOIN groups g ON s.group_id = g.id "
                  "WHERE g.name = ?");
    query.bindValue(0, groupName);

    if (!query.exec()) return students;

    while (query.next()) {
        QStringList student;
        student << query.value(0).toString()
                << query.value(1).toString()
                << query.value(2).toString()
                << query.value(3).toString();
        students.append(student);
    }

    return students;
}

QList<QStringList> DatabaseManager::getAllStudents()
{
    QList<QStringList> students;

    QSqlQuery query("SELECT s.id, s.full_name, s.student_card, g.name "
                    "FROM students s "
                    "JOIN groups g ON s.group_id = g.id");

    if (!query.exec()) return students;

    while (query.next()) {
        QStringList student;
        student << query.value(0).toString()
                << query.value(1).toString()
                << query.value(2).toString()
                << query.value(3).toString();
        students.append(student);
    }

    return students;
}

// ==================== ПОСЕЩАЕМОСТЬ ====================

bool DatabaseManager::markAttendance(int studentId, int lessonId, bool status, const QString& /*date*/)
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM attendance WHERE student_id = ? AND lesson_id = ?");
    checkQuery.bindValue(0, studentId);
    checkQuery.bindValue(1, lessonId);

    if (checkQuery.exec() && checkQuery.next()) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE attendance SET status = ? WHERE student_id = ? AND lesson_id = ?");
        updateQuery.bindValue(0, status ? 1 : 0);
        updateQuery.bindValue(1, studentId);
        updateQuery.bindValue(2, lessonId);
        return updateQuery.exec();
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO attendance (student_id, lesson_id, status, comment) VALUES (?, ?, ?, '')");
    insertQuery.bindValue(0, studentId);
    insertQuery.bindValue(1, lessonId);
    insertQuery.bindValue(2, status ? 1 : 0);

    return insertQuery.exec();
}

// ==================== ОТЧЁТЫ ====================

QList<QStringList> DatabaseManager::generateReport(const QString& groupName, const QString& startDate, const QString& endDate)
{
    QList<QStringList> report;

    QSqlQuery query;
    query.prepare("SELECT s.id, s.full_name, "
                  "COUNT(DISTINCT l.id) as total_lessons, "
                  "SUM(CASE WHEN a.status = 1 THEN 1 ELSE 0 END) as present, "
                  "SUM(CASE WHEN a.status = 0 AND a.comment LIKE '%опозда%' THEN 1 ELSE 0 END) as late "
                  "FROM students s "
                  "JOIN groups g ON s.group_id = g.id "
                  "JOIN lessons l ON l.group_id = g.id "
                  "LEFT JOIN attendance a ON a.student_id = s.id AND a.lesson_id = l.id "
                  "WHERE g.name = ? AND l.lesson_date BETWEEN ? AND ? "
                  "GROUP BY s.id");
    query.bindValue(0, groupName);
    query.bindValue(1, startDate);
    query.bindValue(2, endDate);

    if (!query.exec()) return report;

    while (query.next()) {
        QStringList row;
        row << query.value(0).toString()
            << query.value(1).toString()
            << query.value(2).toString()
            << query.value(3).toString()
            << query.value(4).toString();
        report.append(row);
    }

    return report;
}