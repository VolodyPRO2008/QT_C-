#ifndef REPORTTAB_H
#define REPORTTAB_H

#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include "reporttablemodel.h"
#include "databasemanager.h"

class ReportTab : public QWidget
{
    Q_OBJECT
public:
    explicit ReportTab(QWidget* parent = nullptr);

public slots:
    void refresh();
    void exportToCSV();

private:
    QComboBox* m_groupCombo;
    QDateEdit* m_startDateEdit;
    QDateEdit* m_endDateEdit;
    QPushButton* m_refreshButton;
    QPushButton* m_exportButton;
    QTableView* m_tableView;
    ReportTableModel* m_model;
};

#endif