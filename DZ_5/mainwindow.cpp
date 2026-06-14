#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Variant 5.5 - Fishermen and Fish");

    ui->textEditResult->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Преобразует множество в строку для вывода
QString MainWindow::setToString(const QSet<QString>& set)
{
    if (set.isEmpty()) {
        return "(нет рыб)";
    }

    QString result;
    QList<QString> list = set.values();  // Превращаем множество в список
    std::sort(list.begin(), list.end()); // Сортируем для красоты

    for (const QString& item : list) {
        result += item + ", ";
    }

    // Убираем последнюю запятую
    result.chop(2);
    return result;
}


void MainWindow::processData()
{


    lakeFish = {
        "Окунь", "Щука", "Карп", "Сом", "Лещ",
        "Судак", "Плотва", "Карась", "Форель", "Лосось"
    };

    // Что поймал первый рыбак
    fisherman1 = {
        "Окунь", "Щука", "Карп", "Лещ"
    };

    // Что поймал второй рыбак
    fisherman2 = {
        "Щука", "Сом", "Судак", "Карась"
    };

    // Что поймал третий рыбак
    fisherman3 = {
        "Карп", "Лещ", "Плотва", "Окунь", "Судак"
    };



    QString output;



    output += "Виды рыб в озере:\n";
    output += setToString(lakeFish) + "\n\n";

    output += "Рыбак 1 поймал:\n";
    output += setToString(fisherman1) + "\n\n";

    output += "Рыбак 2 поймал:\n";
    output += setToString(fisherman2) + "\n\n";

    output += "Рыбак 3 поймал:\n";
    output += setToString(fisherman3) + "\n\n";



    output += "1) Рыбы, которые есть у каждого рыбака:\n";

    // Находим пересечение всех трёх множеств
    QSet<QString> commonToAll = fisherman1;
    commonToAll.intersect(fisherman2);
    commonToAll.intersect(fisherman3);

    output += setToString(commonToAll) + "\n\n";



    output += "2) Рыбы, которые есть ТОЛЬКО у конкретного рыбака:\n\n";

    // Рыбы только у первого рыбака
    QSet<QString> onlyFisherman1 = fisherman1;
    QSet<QString> others1 = fisherman2;
    others1.unite(fisherman3);
    onlyFisherman1.subtract(others1);
    output += "   Только у рыбака 1: " + setToString(onlyFisherman1) + "\n";

    // Рыбы только у второго рыбака
    QSet<QString> onlyFisherman2 = fisherman2;
    QSet<QString> others2 = fisherman1;
    others2.unite(fisherman3);
    onlyFisherman2.subtract(others2);
    output += "   Только у рыбака 2: " + setToString(onlyFisherman2) + "\n";

    // Рыбы только у третьего рыбака
    QSet<QString> onlyFisherman3 = fisherman3;
    QSet<QString> others3 = fisherman1;
    others3.unite(fisherman2);
    onlyFisherman3.subtract(others3);
    output += "   Только у рыбака 3: " + setToString(onlyFisherman3) + "\n\n";

    // ========== 5. РЫБЫ, КОТОРЫЕ ЕСТЬ В ОЗЕРЕ, НО НЕТ НИ У ОДНОГО РЫБАКА ==========

    output += "3) Рыбы, которые есть в озере, но не поймал никто:\n";

    QSet<QString> allCaught = fisherman1;
    allCaught.unite(fisherman2);
    allCaught.unite(fisherman3);

    QSet<QString> notCaught = lakeFish;
    notCaught.subtract(allCaught);

    output += setToString(notCaught) + "\n\n";


    output += "Рыбы, пойманные хотя бы двумя рыбаками:\n";

    // Считаем количество поймавших каждую рыбу
    QStringList allFishList = lakeFish.values();
    std::sort(allFishList.begin(), allFishList.end());

    QString atLeastTwo;
    for (const QString& fish : allFishList) {
        int count = 0;
        if (fisherman1.contains(fish)) count++;
        if (fisherman2.contains(fish)) count++;
        if (fisherman3.contains(fish)) count++;
        if (count >= 2) {
            atLeastTwo += fish + ", ";
        }
    }
    if (!atLeastTwo.isEmpty()) {
        atLeastTwo.chop(2);
        output += "   " + atLeastTwo + "\n\n";
    } else {
        output += "   (нет таких рыб)\n\n";
    }

    // Какие рыбы поймал только один рыбак
    output += "Рыбы, пойманные только одним рыбаком:\n";

    QString onlyOne;
    for (const QString& fish : allFishList) {
        int count = 0;
        if (fisherman1.contains(fish)) count++;
        if (fisherman2.contains(fish)) count++;
        if (fisherman3.contains(fish)) count++;
        if (count == 1) {
            onlyOne += fish + ", ";
        }
    }
    if (!onlyOne.isEmpty()) {
        onlyOne.chop(2);
        output += "   " + onlyOne + "\n";
    } else {
        output += "   (нет таких рыб)\n";
    }

    // Выводим результат в textEdit
    ui->textEditResult->setText(output);
}

void MainWindow::on_buttonProcess_clicked()
{
    processData();
}

