#ifndef ATTENDANCETAB_H
#define ATTENDANCETAB_H

#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDate>
#include "attendancetablemodel.h"
#include "databasemanager.h"

class AttendanceTab : public QWidget
{
    Q_OBJECT
public:
    explicit AttendanceTab(QWidget* parent = nullptr);

public slots:
    void refresh();
    void markAllPresent();
    void saveAttendance();
    void onGroupChanged(int index);

private:
    QComboBox* m_groupCombo;
    QComboBox* m_lessonCombo;
    QDateEdit* m_dateEdit;
    QTableView* m_tableView;
    AttendanceTableModel* m_model;
    QPushButton* m_markAllButton;
    QPushButton* m_saveButton;

    void setupGroupCombo();
    void setupLessonCombo();
};

#endif // ATTENDANCETAB_H