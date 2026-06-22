#ifndef STUDENTSTAB_H
#define STUDENTSTAB_H

#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "studentstablemodel.h"
#include "databasemanager.h"

class StudentsTab : public QWidget
{
    Q_OBJECT
public:
    explicit StudentsTab(QWidget* parent = nullptr);

public slots:
    void refresh();
    void addStudent();
    void deleteStudent();
    void onGroupChanged(int index);

private:
    QTableView* m_tableView;
    StudentsTableModel* m_model;
    QComboBox* m_groupCombo;
    QLineEdit* m_nameEdit;
    QLineEdit* m_cardEdit;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
};

#endif // STUDENTSTAB_H