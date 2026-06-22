#ifndef GROUPSTAB_H
#define GROUPSTAB_H

#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "groupstablemodel.h"
#include "databasemanager.h"

class GroupsTab : public QWidget
{
    Q_OBJECT
public:
    explicit GroupsTab(QWidget* parent = nullptr);

public slots:
    void refresh();
    void addGroup();
    void deleteGroup();

private:
    QTableView* m_tableView;
    GroupsTableModel* m_model;
    QLineEdit* m_nameEdit;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
};

#endif // GROUPSTAB_H