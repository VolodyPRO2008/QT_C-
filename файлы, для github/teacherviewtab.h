#ifndef TEACHERVIEWTAB_H
#define TEACHERVIEWTAB_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QGroupBox>
#include "models.h"

class TeacherViewTab : public QWidget
{
    Q_OBJECT
public:
    explicit TeacherViewTab(int teacherId, QWidget* parent = nullptr);

public slots:
    void refresh();

private:
    int m_teacherId;
    QTableView* m_scheduleView;
    TeacherScheduleModel* m_scheduleModel;

    void setupUI();
    void loadSchedule();
};

#endif // TEACHERVIEWTAB_H