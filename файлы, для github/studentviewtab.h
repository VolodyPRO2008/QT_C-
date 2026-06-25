#ifndef STUDENTVIEWTAB_H
#define STUDENTVIEWTAB_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QGroupBox>
#include <QProgressBar>
#include "models.h"

class StudentViewTab : public QWidget
{
    Q_OBJECT
public:
    explicit StudentViewTab(int studentId, QWidget* parent = nullptr);

public slots:
    void refresh();

private:
    int m_studentId;

    // Посещаемость
    QTableView* m_attendanceView;
    AttendanceViewModel* m_attendanceModel;
    QLabel* m_percentLabel;
    QProgressBar* m_progressBar;
    QLabel* m_infoLabel;

    void setupUI();
    void loadAttendance();
    void updateStats();
};

#endif // STUDENTVIEWTAB_H