#include "redistribution.h"
#include "ui_redistribution.h"
#include <QMessageBox>

redistribution::redistribution(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::redistribution)
{
    ui->setupUi(this);
}

redistribution::~redistribution()
{
    delete ui;
}

void redistribution::on_pushButton_clicked()
{
    QString firstNumX = ui -> lineEdit -> text();
    QString secondNumY = ui -> lineEdit_2 -> text();

    bool ok;

    float firstNum = firstNumX.toFloat(&ok);
    if (!ok) {
        QMessageBox::information(this,"Ошибка", "Введите число!");
        return; }
    float secondNum = secondNumY.toFloat();
    if (!ok) {
        QMessageBox::information(this,"Ошибка", "Введите число!");
        return; }

        if (secondNum <= 0 || firstNum <= 0) {
        QMessageBox::information(this,"Ошибка", "Отрицательное число!");
        return; }

    if(firstNum < secondNum || firstNum == secondNum){
        ui -> lineEdit -> setText(QString::number(firstNum));
        ui -> lineEdit_2 -> setText(QString::number(secondNum));
    }
    else{
        ui -> lineEdit -> setText(QString::number(secondNum));
        ui -> lineEdit_2 -> setText(QString::number(firstNum));
    }



}


void redistribution::on_pushButton_2_clicked()
{
    QString firstNumX = ui -> lineEdit_3 -> text();
    QString secondNumY = ui -> lineEdit_4 -> text();
    QString thirdNumZ = ui -> lineEdit_5 -> text();

    bool ok;

    float firstNum = firstNumX.toFloat(&ok);
    if (!ok) {
        QMessageBox::information(this,"Ошибка", "Введите число!");
        return; }
    float secondNum = secondNumY.toFloat();
    if (!ok) {
        QMessageBox::information(this,"Ошибка", "Введите число!");
        return; }
    float thirdNum = thirdNumZ.toFloat();
    if (!ok) {
        QMessageBox::information(this,"Ошибка", "Введите число!");
        return; }

    if (secondNum <= 0 || firstNum <= 0 || thirdNum <=0) {
        QMessageBox::information(this,"Ошибка", "Отрицательное число!");
        return; }


    if((firstNum < secondNum && secondNum < thirdNum) || (firstNum > secondNum && secondNum > thirdNum)){

    ui -> lineEdit_3-> setText(QString::number(firstNum * 2));
    ui -> lineEdit_4-> setText(QString::number(secondNum * 2));
    ui -> lineEdit_5-> setText(QString::number(thirdNum * 2));

    }
    else {
        ui -> lineEdit_3-> setText(QString::number(firstNum * -1));
        ui -> lineEdit_4-> setText(QString::number(secondNum * -1));
        ui -> lineEdit_5-> setText(QString::number(thirdNum * -1));
    }


}

