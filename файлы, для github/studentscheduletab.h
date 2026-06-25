#ifndef STUDENTSCHEDULETAB_H
#define STUDENTSCHEDULETAB_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QGroupBox>
#include "models.h"

class StudentScheduleTab : public QWidget
{
    Q_OBJECT
public:
    explicit StudentScheduleTab(int studentId, QWidget* parent = nullptr);

public slots:
    void refresh();

private:
    int m_studentId;
    QTableView* m_scheduleView;
    ScheduleModel* m_scheduleModel;
    QLabel* m_infoLabel;

    void setupUI();
    void loadSchedule();
};

#endif // STUDENTSCHEDULETAB_H