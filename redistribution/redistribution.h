#ifndef REDISTRIBUTION_H
#define REDISTRIBUTION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class redistribution;
}
QT_END_NAMESPACE

class redistribution : public QMainWindow
{
    Q_OBJECT

public:
    explicit redistribution(QWidget *parent = nullptr);
    ~redistribution() override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::redistribution *ui;
};
#endif // REDISTRIBUTION_H
