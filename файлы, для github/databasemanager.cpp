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
        //  ТАБЛИЦА ПОЛЬЗОВАТЕЛЕЙ
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE,"
        "password TEXT,"
        "role INTEGER NOT NULL DEFAULT 0,"
        "full_name TEXT UNIQUE NOT NULL,"
        "teacher_id INTEGER)",

        //  ТАБЛИЦА ГРУПП
        "CREATE TABLE IF NOT EXISTS groups ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT UNIQUE NOT NULL,"
        "course INTEGER NOT NULL,"
        "year INTEGER NOT NULL,"
        "student_count INTEGER DEFAULT 0)",

        //  ТАБЛИЦА СТУДЕНТОВ
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "full_name TEXT NOT NULL,"
        "student_card TEXT UNIQUE NOT NULL,"
        "group_id INTEGER NOT NULL,"
        "user_id INTEGER UNIQUE,"
        "FOREIGN KEY (group_id) REFERENCES groups(id) ON DELETE CASCADE,"
        "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE)",

        //  ТАБЛИЦА ПРЕПОДАВАТЕЛЕЙ
        "CREATE TABLE IF NOT EXISTS teachers ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "full_name TEXT UNIQUE NOT NULL,"
        "user_id INTEGER UNIQUE,"
        "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE SET NULL)",

        //  ТАБЛИЦА ДИСЦИПЛИН
        "CREATE TABLE IF NOT EXISTS disciplines ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT UNIQUE NOT NULL,"
        "semester INTEGER NOT NULL,"
        "hours INTEGER NOT NULL)",

        //  ТАБЛИЦА ПАР (УРОКОВ)
        "CREATE TABLE IF NOT EXISTS lessons ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "discipline_id INTEGER NOT NULL,"
        "group_id INTEGER NOT NULL,"
        "teacher_id INTEGER NOT NULL,"
        "lesson_date TEXT NOT NULL,"
        "lesson_number INTEGER NOT NULL,"
        "room TEXT DEFAULT 'Ауд. 101',"
        "FOREIGN KEY (discipline_id) REFERENCES disciplines(id),"
        "FOREIGN KEY (group_id) REFERENCES groups(id),"
        "FOREIGN KEY (teacher_id) REFERENCES teachers(id))",

        //  ТАБЛИЦА ПОСЕЩАЕМОСТИ
        "CREATE TABLE IF NOT EXISTS attendance ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "student_id INTEGER NOT NULL,"
        "lesson_id INTEGER NOT NULL,"
        "status INTEGER NOT NULL,"
        "comment TEXT,"
        "FOREIGN KEY (student_id) REFERENCES students(id) ON DELETE CASCADE,"
        "FOREIGN KEY (lesson_id) REFERENCES lessons(id) ON DELETE CASCADE)",

        //  ТАБЛИЦА ОЦЕНОК
        "CREATE TABLE IF NOT EXISTS grades ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "student_id INTEGER NOT NULL,"
        "lesson_id INTEGER NOT NULL,"
        "grade INTEGER CHECK(grade BETWEEN 2 AND 5),"
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

    //  СОЗДАЁМ ГРУППЫ
    executeQuery("INSERT INTO groups (name, course, year) VALUES ('ИОС-105', 1, 2025)");
    executeQuery("INSERT INTO groups (name, course, year) VALUES ('ИОС-102', 1, 2025)");
    executeQuery("INSERT INTO groups (name, course, year) VALUES ('ИОС-104', 1, 2025)");

    QStringList queries = {
        // Пользователи
        "INSERT INTO users (username, password, role, full_name) VALUES "
        "('admin', 'admin123', 2, 'Иванов Иван Иванович'),"
        "('teacher1', 'teacher123', 1, 'Петров Петр Петрович'),"
        "('teacher2', 'teacher123', 1, 'Сидорова Анна Сергеевна'),"
        "('student1', NULL, 0, 'Александров Алексей Алексеевич'),"
        "('student2', NULL, 0, 'Борисов Борис Борисович'),"
        "('student3', NULL, 0, 'Васильева Василиса Васильевна'),"
        "('student4', NULL, 0, 'Григорьев Григорий Григорьевич'),"
        "('student5', NULL, 0, 'Дмитриева Дарья Дмитриевна'),"
        "('student6', NULL, 0, 'Егоров Егор Егорович')",

        // Преподаватели
        "INSERT INTO teachers (full_name, user_id) VALUES "
        "('Петров Петр Петрович', 2),"
        "('Сидорова Анна Сергеевна', 3)",

        // Студенты
        "INSERT INTO students (full_name, student_card, group_id, user_id) VALUES "
        "('Александров Алексей Алексеевич', 'С-001', 1, 4),"
        "('Борисов Борис Борисович', 'С-002', 1, 5),"
        "('Васильева Василиса Васильевна', 'С-003', 1, 6),"
        "('Григорьев Григорий Григорьевич', 'С-004', 2, NULL),"
        "('Дмитриева Дарья Дмитриевна', 'С-005', 2, NULL),"
        "('Егоров Егор Егорович', 'С-006', 3, NULL)",

        // Дисциплины
        "INSERT INTO disciplines (name, semester, hours) VALUES "
        "('Программирование', 1, 64),"
        "('Базы данных', 1, 48),"
        "('Веб-технологии', 2, 48),"
        "('Тестирование ПО', 2, 32),"
        "('Системный анализ', 3, 48)"
    };

    for (const QString& query : queries) {
        executeQuery(query);
    }

    //  СОЗДАЁМ РАСПИСАНИЕ ДЛЯ КАЖДОЙ ГРУППЫ
    // Для группы "Общая" (id=1)
    executeQuery("INSERT INTO lessons (discipline_id, group_id, teacher_id, lesson_date, lesson_number, room) VALUES "
                 "(1, 1, 1, '2026-06-25', 1, 'Ауд. 101'),"
                 "(1, 1, 1, '2026-06-25', 2, 'Ауд. 102'),"
                 "(2, 1, 2, '2026-06-25', 3, 'Ауд. 103'),"
                 "(1, 1, 1, '2026-06-26', 1, 'Ауд. 101'),"
                 "(2, 1, 2, '2026-06-26', 2, 'Ауд. 103'),"
                 "(3, 1, 1, '2026-06-26', 3, 'Ауд. 104'),"
                 "(1, 1, 1, '2026-06-27', 2, 'Ауд. 102'),"
                 "(2, 1, 2, '2026-06-27', 3, 'Ауд. 103')");

    // Для группы "ИОС-102" (id=2)
    executeQuery("INSERT INTO lessons (discipline_id, group_id, teacher_id, lesson_date, lesson_number, room) VALUES "
                 "(1, 2, 1, '2026-06-25', 1, 'Ауд. 201'),"
                 "(2, 2, 2, '2026-06-25', 2, 'Ауд. 202'),"
                 "(1, 2, 1, '2026-06-26', 1, 'Ауд. 201'),"
                 "(3, 2, 1, '2026-06-26', 2, 'Ауд. 203'),"
                 "(2, 2, 2, '2026-06-27', 1, 'Ауд. 202')");

    // Для группы "ИОС-104" (id=3)
    executeQuery("INSERT INTO lessons (discipline_id, group_id, teacher_id, lesson_date, lesson_number, room) VALUES "
                 "(1, 3, 1, '2026-06-25', 1, 'Ауд. 301'),"
                 "(2, 3, 2, '2026-06-25', 2, 'Ауд. 302'),"
                 "(3, 3, 1, '2026-06-26', 1, 'Ауд. 303'),"
                 "(1, 3, 1, '2026-06-26', 2, 'Ауд. 301'),"
                 "(2, 3, 2, '2026-06-27', 1, 'Ауд. 302')");

    //  СОЗДАЁМ ЗАПИСИ ПОСЕЩАЕМОСТИ ДЛЯ КАЖДОГО СТУДЕНТА (по умолчанию "Отсутствовал")
    // Получаем всех студентов и все уроки
    QSqlQuery studentsQuery("SELECT id FROM students");
    QSqlQuery lessonsQuery("SELECT id FROM lessons");

    QList<int> studentIds;
    QList<int> lessonIds;

    while (studentsQuery.next()) {
        studentIds.append(studentsQuery.value(0).toInt());
    }
    while (lessonsQuery.next()) {
        lessonIds.append(lessonsQuery.value(0).toInt());
    }

    // Для каждого студента и каждого урока создаём запись посещаемости
    for (int studentId : studentIds) {
        for (int lessonId : lessonIds) {
            // Проверяем, существует ли уже запись
            QSqlQuery checkExist;
            checkExist.prepare("SELECT id FROM attendance WHERE student_id = ? AND lesson_id = ?");
            checkExist.bindValue(0, studentId);
            checkExist.bindValue(1, lessonId);

            if (!checkExist.exec() || !checkExist.next()) {
                // Создаём запись с статусом "Отсутствовал" (0)
                QSqlQuery insertAttendance;
                insertAttendance.prepare("INSERT INTO attendance (student_id, lesson_id, status, comment) VALUES (?, ?, 0, '')");
                insertAttendance.bindValue(0, studentId);
                insertAttendance.bindValue(1, lessonId);
                insertAttendance.exec();
            }
        }
    }

    // Обновляем счётчики студентов
    auto groups = getAllGroups();
    for (const auto& group : groups) {
        if (group.size() > 0) {
            updateStudentCount(group[0].toInt());
        }
    }

    qDebug() << "Test data inserted successfully!";
}



//  АВТОРИЗАЦИЯ

UserInfo DatabaseManager::authenticateUser(const QString& fullName)
{
    UserInfo result;
    result.id = -1;
    result.role = UserRole::Student;

    QSqlQuery query;
    query.prepare("SELECT id, role, full_name FROM users WHERE full_name = ?");
    query.bindValue(0, fullName);

    if (!query.exec() || !query.next()) {
        qDebug() << "User not found:" << fullName;
        return result;
    }

    result.id = query.value(0).toInt();
    result.role = static_cast<UserRole>(query.value(1).toInt());
    result.fullName = query.value(2).toString();

    return result;
}



bool DatabaseManager::deleteGroup(const QString& name)
{
    // Получаем ID группы перед удалением
    QSqlQuery getIdQuery;
    getIdQuery.prepare("SELECT id FROM groups WHERE name = ?");
    getIdQuery.bindValue(0, name);

    int groupId = -1;
    if (getIdQuery.exec() && getIdQuery.next()) {
        groupId = getIdQuery.value(0).toInt();
    }

    QSqlQuery query;
    query.prepare("DELETE FROM groups WHERE name = ?");
    query.bindValue(0, name);

    if (!query.exec()) {
        return false;
    }

    // Студенты удаляются каскадно, но счётчик нужно обновить
    if (groupId != -1) {
        // Обновляем счётчик студентов в группе (он станет 0, т.к. группа удалена)
        // Но группа уже удалена, поэтому ничего не делаем
    }

    return true;
}
//  СТУДЕНТЫ

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

    if (!insertQuery.exec()) {
        return false;
    }

    //  ОБНОВЛЯЕМ КОЛИЧЕСТВО СТУДЕНТОВ В ГРУППЕ
    updateStudentCount(groupId);

    return true;
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

bool DatabaseManager::deleteStudent(int studentId)
{
    // Сначала получаем group_id студента
    QSqlQuery getGroupQuery;
    getGroupQuery.prepare("SELECT group_id FROM students WHERE id = ?");
    getGroupQuery.bindValue(0, studentId);

    int groupId = -1;
    if (getGroupQuery.exec() && getGroupQuery.next()) {
        groupId = getGroupQuery.value(0).toInt();
    }

    QSqlQuery query;
    query.prepare("DELETE FROM students WHERE id = ?");
    query.bindValue(0, studentId);

    if (!query.exec()) {
        return false;
    }

    //  ОБНОВЛЯЕМ КОЛИЧЕСТВО СТУДЕНТОВ В ГРУППЕ
    if (groupId != -1) {
        updateStudentCount(groupId);
    }

    return true;
}

bool DatabaseManager::updateStudentName(int studentId, const QString& newName)
{
    QSqlQuery query;
    query.prepare("UPDATE students SET full_name = ? WHERE id = ?");
    query.bindValue(0, newName);
    query.bindValue(1, studentId);
    return query.exec();
}

//  ПРЕПОДАВАТЕЛИ

QList<QStringList> DatabaseManager::getAllTeachers()
{
    QList<QStringList> teachers;
    QSqlQuery query("SELECT id, full_name FROM teachers");

    if (!query.exec()) return teachers;

    while (query.next()) {
        QStringList teacher;
        teacher << query.value(0).toString()
                << query.value(1).toString();
        teachers.append(teacher);
    }

    return teachers;
}

bool DatabaseManager::addTeacher(const QString& fullName)
{
    QSqlQuery query;
    query.prepare("INSERT INTO teachers (full_name) VALUES (?)");
    query.bindValue(0, fullName);
    return query.exec();
}

bool DatabaseManager::deleteTeacher(int teacherId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM teachers WHERE id = ?");
    query.bindValue(0, teacherId);
    return query.exec();
}

//  ПОСЕЩАЕМОСТЬ

bool DatabaseManager::markAttendance(int studentId, int lessonId, bool status, const QString& /*date*/)
{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM attendance WHERE student_id = ? AND lesson_id = ?");
    checkQuery.bindValue(0, studentId);
    checkQuery.bindValue(1, lessonId);

    if (checkQuery.exec() && checkQuery.next()) {
        return updateAttendance(studentId, lessonId, status, "");
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO attendance (student_id, lesson_id, status, comment) VALUES (?, ?, ?, '')");
    insertQuery.bindValue(0, studentId);
    insertQuery.bindValue(1, lessonId);
    insertQuery.bindValue(2, status ? 1 : 0);

    return insertQuery.exec();
}

bool DatabaseManager::updateAttendance(int studentId, int lessonId, bool status, const QString& comment)
{
    QSqlQuery query;
    query.prepare("UPDATE attendance SET status = ?, comment = ? WHERE student_id = ? AND lesson_id = ?");
    query.bindValue(0, status ? 1 : 0);
    query.bindValue(1, comment);
    query.bindValue(2, studentId);
    query.bindValue(3, lessonId);
    return query.exec();
}

QList<QStringList> DatabaseManager::getAttendanceForStudent(int studentId)
{
    QList<QStringList> records;
    QSqlQuery query;
    query.prepare("SELECT l.lesson_date, d.name, a.status, a.comment "
                  "FROM attendance a "
                  "JOIN lessons l ON a.lesson_id = l.id "
                  "JOIN disciplines d ON l.discipline_id = d.id "
                  "WHERE a.student_id = ? "
                  "ORDER BY l.lesson_date DESC");
    query.bindValue(0, studentId);

    if (!query.exec()) return records;

    while (query.next()) {
        QStringList record;
        record << query.value(0).toString()
               << query.value(1).toString()
               << (query.value(2).toInt() == 1 ? "Присутствовал" : "Отсутствовал")
               << query.value(3).toString();
        records.append(record);
    }

    return records;
}

//  РАСПИСАНИЕ

QList<QStringList> DatabaseManager::getScheduleForTeacher(int teacherId)
{
    QList<QStringList> schedule;
    QSqlQuery query;
    query.prepare(
        "SELECT l.lesson_date, d.name, g.name, l.lesson_number, l.room "
        "FROM lessons l "
        "JOIN disciplines d ON l.discipline_id = d.id "
        "JOIN groups g ON l.group_id = g.id "
        "WHERE l.teacher_id = ? "
        "ORDER BY l.lesson_date, l.lesson_number"
        );
    query.bindValue(0, teacherId);

    if (!query.exec()) {
        qDebug() << "Error getting schedule for teacher:" << query.lastError().text();
        return schedule;
    }

    while (query.next()) {
        QStringList item;
        QDate date = QDate::fromString(query.value(0).toString(), "yyyy-MM-dd");
        item << date.toString("dd.MM.yyyy")           // Дата
             << query.value(1).toString()              // Дисциплина
             << query.value(2).toString()              // Группа
             << query.value(3).toString() + "-я пара"  // Номер пары
             << query.value(4).toString();             // Аудитория
        schedule.append(item);
    }

    return schedule;
}

QList<QStringList> DatabaseManager::getScheduleForStudent(int studentId)
{
    QList<QStringList> schedule;

    // Сначала получаем group_id студента
    QSqlQuery groupQuery;
    groupQuery.prepare("SELECT group_id FROM students WHERE id = ?");
    groupQuery.bindValue(0, studentId);

    int groupId = -1;
    if (groupQuery.exec() && groupQuery.next()) {
        groupId = groupQuery.value(0).toInt();
        qDebug() << "Student group ID:" << groupId;
    } else {
        qDebug() << "Student not found:" << studentId;
        return schedule;
    }

    // Получаем расписание для группы студента
    QSqlQuery query;
    query.prepare(
        "SELECT l.lesson_date, d.name, t.full_name, l.lesson_number, l.room "
        "FROM lessons l "
        "JOIN disciplines d ON l.discipline_id = d.id "
        "JOIN teachers t ON l.teacher_id = t.id "
        "WHERE l.group_id = ? "
        "ORDER BY l.lesson_date, l.lesson_number"
        );
    query.bindValue(0, groupId);

    if (!query.exec()) {
        qDebug() << "Error getting schedule for student:" << query.lastError().text();
        return schedule;
    }

    while (query.next()) {
        QStringList item;
        QDate date = QDate::fromString(query.value(0).toString(), "yyyy-MM-dd");
        item << date.toString("dd.MM.yyyy")           // Дата
             << query.value(1).toString()              // Дисциплина
             << query.value(2).toString()              // Преподаватель
             << query.value(3).toString() + "-я пара"  // Номер пары
             << query.value(4).toString();             // Аудитория
        schedule.append(item);
        qDebug() << "Added schedule item:" << item;
    }

    qDebug() << "Total schedule items:" << schedule.size();
    return schedule;
}
bool DatabaseManager::updateSchedule(const QString& groupName, const QString& discipline, const QString& teacher, const QString& date)
{
    // Упрощённая версия — в реальном проекте нужно получать ID
    QSqlQuery query;
    query.prepare("INSERT INTO lessons (discipline_id, group_id, teacher_id, lesson_date) "
                  "SELECT d.id, g.id, t.id, ? "
                  "FROM disciplines d, groups g, teachers t "
                  "WHERE d.name = ? AND g.name = ? AND t.full_name = ?");
    query.bindValue(0, date);
    query.bindValue(1, discipline);
    query.bindValue(2, groupName);
    query.bindValue(3, teacher);
    return query.exec();
}

//  ОТЧЁТЫ

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

//  УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ (АДМИН)



bool DatabaseManager::updateUserRole(int userId, int newRole)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET role = ? WHERE id = ?");
    query.bindValue(0, newRole);
    query.bindValue(1, userId);
    return query.exec();
}



bool DatabaseManager::updateUserFullName(int userId, const QString& newName)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET full_name = ? WHERE id = ?");
    query.bindValue(0, newName);
    query.bindValue(1, userId);
    return query.exec();
}
bool DatabaseManager::addGroup(const QString& name, int course, int year)
{
    QSqlQuery query;
    query.prepare("INSERT INTO groups (name, course, year) VALUES (?, ?, ?)");
    query.bindValue(0, name);
    query.bindValue(1, course);
    query.bindValue(2, year);

    if (!query.exec()) {
        qDebug() << "Error adding group:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::updateGroup(int groupId, const QString& name, int course, int year)
{
    QSqlQuery query;
    query.prepare("UPDATE groups SET name = ?, course = ?, year = ? WHERE id = ?");
    query.bindValue(0, name);
    query.bindValue(1, course);
    query.bindValue(2, year);
    query.bindValue(3, groupId);

    if (!query.exec()) {
        qDebug() << "Error updating group:" << query.lastError().text();
        return false;
    }

    return true;
}

QList<QStringList> DatabaseManager::getAllGroups()
{
    QList<QStringList> groups;
    QSqlQuery query(
        "SELECT g.id, g.name, g.course, g.year, "
        "(SELECT COUNT(*) FROM students WHERE group_id = g.id) as student_count "
        "FROM groups g"
        );

    if (!query.exec()) {
        qDebug() << "Error executing getAllGroups:" << query.lastError().text();
        return groups;
    }

    while (query.next()) {
        QStringList group;
        group << query.value(0).toString()   // id
              << query.value(1).toString()   // name
              << query.value(2).toString()   // course
              << query.value(3).toString()   // year
              << query.value(4).toString();  // student_count
        groups.append(group);
    }

    return groups;
}
void DatabaseManager::updateStudentCount(int groupId)
{
    QSqlQuery query;
    query.prepare("UPDATE groups SET student_count = (SELECT COUNT(*) FROM students WHERE group_id = ?) WHERE id = ?");
    query.bindValue(0, groupId);
    query.bindValue(1, groupId);
    query.exec();
}

bool DatabaseManager::addUser(const QString& fullName, int role, int groupId)
{
    // Проверяем, существует ли уже пользователь с таким ФИО
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM users WHERE full_name = ?");
    checkQuery.bindValue(0, fullName);
    if (checkQuery.exec() && checkQuery.next()) {
        qDebug() << "User already exists:" << fullName;
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (full_name, role, username) VALUES (?, ?, ?)");
    query.bindValue(0, fullName);
    query.bindValue(1, role);
    query.bindValue(2, "user_" + QString::number(QDateTime::currentMSecsSinceEpoch()));

    if (!query.exec()) {
        qDebug() << "Error adding user:" << query.lastError().text();
        return false;
    }

    int userId = query.lastInsertId().toInt();

    // Если ученик, добавляем в таблицу students
    if (role == 0) {
        // Если группа не выбрана, добавляем в "ИОС-105" (id = 1)
        if (groupId == -1) {
            // Проверяем, существует ли группа "ИОС-105"
            QSqlQuery checkGroup;
            checkGroup.prepare("SELECT id FROM groups WHERE name = 'ИОС-105'");
            if (checkGroup.exec() && checkGroup.next()) {
                groupId = checkGroup.value(0).toInt();
            } else {
                // Если группы "ИОС-105" нет, создаём её
                QSqlQuery createGroup;
                createGroup.prepare("INSERT INTO groups (name, course, year) VALUES ('ИОС-105', 1, 2025)");
                if (createGroup.exec()) {
                    groupId = createGroup.lastInsertId().toInt();
                }
            }
        }

        QSqlQuery studentQuery;
        studentQuery.prepare("INSERT INTO students (full_name, student_card, group_id, user_id) VALUES (?, ?, ?, ?)");
        studentQuery.bindValue(0, fullName);
        studentQuery.bindValue(1, "С-" + QString::number(QDateTime::currentMSecsSinceEpoch()));
        studentQuery.bindValue(2, groupId);
        studentQuery.bindValue(3, userId);

        if (!studentQuery.exec()) {
            qDebug() << "Error adding student:" << studentQuery.lastError().text();
            deleteUser(userId);
            return false;
        }
        updateStudentCount(groupId);
    }

    // Если преподаватель, добавляем в таблицу teachers
    if (role == 1) {
        QSqlQuery teacherQuery;
        teacherQuery.prepare("INSERT INTO teachers (full_name, user_id) VALUES (?, ?)");
        teacherQuery.bindValue(0, fullName);
        teacherQuery.bindValue(1, userId);
        teacherQuery.exec();
    }

    return true;
}

//  ПОЛУЧЕНИЕ ВСЕХ ПОЛЬЗОВАТЕЛЕЙ С ГРУППОЙ
QList<QStringList> DatabaseManager::getAllUsers()
{
    QList<QStringList> users;
    QSqlQuery query(
        "SELECT u.id, u.full_name, u.role, "
        "CASE WHEN u.role = 0 THEN (SELECT g.name FROM students s JOIN groups g ON s.group_id = g.id WHERE s.user_id = u.id) "
        "ELSE '' END as group_name "
        "FROM users u "
        "ORDER BY u.role, u.full_name"
        );

    if (!query.exec()) {
        qDebug() << "Error executing getAllUsers:" << query.lastError().text();
        return users;
    }

    while (query.next()) {
        QStringList user;
        user << query.value(0).toString()   // id
             << query.value(1).toString()   // full_name
             << QString::number(query.value(2).toInt())  // role
             << query.value(3).toString();   // group_name (для учеников)
        users.append(user);
    }

    return users;
}

//  УДАЛЕНИЕ ПОЛЬЗОВАТЕЛЯ
bool DatabaseManager::deleteUser(int userId)
{
    // Получаем роль и группу перед удалением
    QSqlQuery getQuery;
    getQuery.prepare("SELECT role FROM users WHERE id = ?");
    getQuery.bindValue(0, userId);

    int role = -1;
    int groupId = -1;

    if (getQuery.exec() && getQuery.next()) {
        role = getQuery.value(0).toInt();
    }

    // Если ученик, получаем group_id
    if (role == 0) {
        QSqlQuery groupQuery;
        groupQuery.prepare("SELECT group_id FROM students WHERE user_id = ?");
        groupQuery.bindValue(0, userId);
        if (groupQuery.exec() && groupQuery.next()) {
            groupId = groupQuery.value(0).toInt();
        }
    }

    // Удаляем пользователя
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = ?");
    query.bindValue(0, userId);

    if (!query.exec()) {
        return false;
    }

    // Если ученик, удаляем из students и обновляем счётчик
    if (role == 0 && groupId != -1) {
        QSqlQuery deleteStudent;
        deleteStudent.prepare("DELETE FROM students WHERE user_id = ?");
        deleteStudent.bindValue(0, userId);
        deleteStudent.exec();
        updateStudentCount(groupId);
    }

    return true;
}

// УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ (АДМИН)


bool DatabaseManager::updateStudentGroup(int userId, int newGroupId)
{
    // Получаем текущую группу студента
    QSqlQuery getQuery;
    getQuery.prepare("SELECT id, group_id FROM students WHERE user_id = ?");
    getQuery.bindValue(0, userId);

    int studentId = -1;
    int oldGroupId = -1;

    if (getQuery.exec() && getQuery.next()) {
        studentId = getQuery.value(0).toInt();
        oldGroupId = getQuery.value(1).toInt();
    } else {
        qDebug() << "Student not found for user_id:" << userId;
        return false;
    }

    // Обновляем группу студента
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE students SET group_id = ? WHERE user_id = ?");
    updateQuery.bindValue(0, newGroupId);
    updateQuery.bindValue(1, userId);

    if (!updateQuery.exec()) {
        qDebug() << "Error updating student group:" << updateQuery.lastError().text();
        return false;
    }

    //  ОБНОВЛЯЕМ СЧЁТЧИКИ В СТАРОЙ И НОВОЙ ГРУППАХ
    if (oldGroupId != -1) {
        updateStudentCount(oldGroupId);
    }
    if (newGroupId != -1) {
        updateStudentCount(newGroupId);
    }

    return true;
}