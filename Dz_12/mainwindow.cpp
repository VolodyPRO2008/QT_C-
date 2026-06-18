#include "mainwindow.h"
#include <QScrollArea>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Лабораторная работа 2: Пользовательские сценарии. Вариант 5: Агентство недвижимости");
    setMinimumSize(1100, 750);
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QTabWidget *tabs = new QTabWidget(this);
    tabs->setStyleSheet(
        "QTabBar::tab { padding: 10px 18px; font-size: 13px; }"
        "QTabBar::tab:selected { background-color: #2C3E50; color: white; }"
        );

    tabs->addTab(createStoriesTab(), "📖 Пользовательские истории");
    tabs->addTab(createConceptualTab(), "📝 Концептуальные сценарии");
    tabs->addTab(createUseCasesTab(), "📋 Сценарии использования");
    tabs->addTab(createUserFlowTab(), "🗺️ Диаграммы путей");
    tabs->addTab(createScreenMapTab(), "📱 Карта экранов");
    tabs->addTab(createAnswersTab(), "❓ Контрольные вопросы");

    setCentralWidget(tabs);
}

// ==================== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ====================

QTableWidget* MainWindow::createTable(const QStringList &headers, const QList<QStringList> &data)
{
    QTableWidget *table = new QTableWidget;
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->setRowCount(data.size());
    table->horizontalHeader()->setStretchLastSection(true);
    table->setAlternatingRowColors(true);
    table->setEditTriggers(QTableWidget::NoEditTriggers);
    table->setStyleSheet("font-size: 12px;");

    for (int row = 0; row < data.size(); ++row) {
        for (int col = 0; col < data[row].size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(data[row][col]);
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, col, item);
        }
    }
    table->resizeColumnsToContents();
    return table;
}

QFrame* MainWindow::createCard(const QString &title, const QString &desc, const QString &icon)
{
    QFrame *card = new QFrame;
    card->setStyleSheet(
        "background-color: #f8f9fa; border: 1px solid #dee2e6; border-radius: 8px; padding: 10px;"
        );
    card->setFixedHeight(100);

    QVBoxLayout *layout = new QVBoxLayout(card);
    QLabel *titleLabel = new QLabel(icon + " " + title);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #2C3E50;");
    QLabel *descLabel = new QLabel(desc);
    descLabel->setStyleSheet("font-size: 12px; color: #555;");
    descLabel->setWordWrap(true);

    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);
    return card;
}

// ==================== ВКЛАДКА 1: ПОЛЬЗОВАТЕЛЬСКИЕ ИСТОРИИ ====================

QWidget* MainWindow::createStoriesTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("📖 Пользовательские истории");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QLabel *desc = new QLabel(
        "Пользовательские истории описывают потребности пользователей в формате:\n"
        "«Как <тип пользователя>, я хочу <цель>, чтобы <причина>»"
        );
    desc->setStyleSheet("font-size: 14px; padding: 10px; background-color: #f0f8ff; border-radius: 5px;");
    desc->setWordWrap(true);
    layout->addWidget(desc);

    // Истории
    QStringList stories = {
        "👩‍💼 История 1: Риелтор Анна\n"
        "Как риелтор с опытом работы 7 лет, я хочу быстро добавлять объекты в базу и вести историю сделок,\n"
        "чтобы эффективно управлять своей работой и не терять клиентов.\n",

        "👨‍💼 История 2: Покупатель Дмитрий\n"
        "Как покупатель, который ищет квартиру для семьи, я хочу видеть удобные фильтры и записываться на просмотр онлайн,\n"
        "чтобы экономить время и быстро найти подходящее жилье.\n",

        "👩‍💼 История 3: Продавец Елена\n"
        "Как продавец квартиры, я хочу разместить объект с фото и описанием, видеть количество просмотров,\n"
        "чтобы быстро продать недвижимость по хорошей цене.\n",

        "👨‍💼 История 4: Арендатор Сергей\n"
        "Как арендатор, я хочу искать жилье по параметрам (цена, метро, район) и связываться с риелтором напрямую,\n"
        "чтобы снять квартиру без посредников.\n",

        "👩‍💼 История 5: Администратор Ольга\n"
        "Как директор агентства, я хочу видеть отчеты по продажам и управлять сотрудниками,\n"
        "чтобы контролировать эффективность работы агентства."
    };

    for (const QString &story : stories) {
        QLabel *label = new QLabel(story);
        label->setStyleSheet("font-size: 13px; padding: 12px; background-color: #f8f9fa; border-radius: 5px; border-left: 4px solid #2C3E50; margin: 5px;");
        label->setWordWrap(true);
        layout->addWidget(label);
    }

    layout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scroll);
    widget->setLayout(mainLayout);
    return widget;
}

// ==================== ВКЛАДКА 2: КОНЦЕПТУАЛЬНЫЕ СЦЕНАРИИ ====================

QWidget* MainWindow::createConceptualTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("📝 Концептуальные сценарии");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QLabel *desc = new QLabel(
        "Концептуальные сценарии обобщают множество пользовательских историй в несколько основных сценариев."
        );
    desc->setStyleSheet("font-size: 14px; padding: 10px; background-color: #f0f8ff; border-radius: 5px;");
    desc->setWordWrap(true);
    layout->addWidget(desc);

    // Сценарий 1
    QGroupBox *scenario1 = new QGroupBox("🏠 Сценарий 1: Поиск и покупка квартиры");
    QTextEdit *text1 = new QTextEdit;
    text1->setStyleSheet("font-family: monospace; font-size: 13px; background-color: #f8f9fa;");
    text1->setText(
        "Покупатель Дмитрий ищет 2-комнатную квартиру для семьи.\n\n"
        "1. Заходит на сайт RealtyPro\n"
        "2. Вводит в поиск: «2-комнатная квартира, до 6 млн рублей»\n"
        "3. Применяет фильтры: район, этаж, состояние\n"
        "4. Просматривает подходящие варианты\n"
        "5. Открывает карточку понравившегося объекта\n"
        "6. Изучает фото, описание, характеристики\n"
        "7. Нажимает кнопку «Записаться на просмотр»\n"
        "8. Выбирает удобное время\n"
        "9. Получает подтверждение от риелтора\n"
        "10. Приходит на просмотр и принимает решение"
        );
    text1->setReadOnly(true);
    QVBoxLayout *lay1 = new QVBoxLayout;
    lay1->addWidget(text1);
    scenario1->setLayout(lay1);
    layout->addWidget(scenario1);

    // Сценарий 2
    QGroupBox *scenario2 = new QGroupBox("👩‍💼 Сценарий 2: Размещение объекта");
    QTextEdit *text2 = new QTextEdit;
    text2->setStyleSheet("font-family: monospace; font-size: 13px; background-color: #f8f9fa;");
    text2->setText(
        "Продавец Елена хочет продать свою квартиру.\n\n"
        "1. Регистрируется на сайте RealtyPro\n"
        "2. Заходит в личный кабинет\n"
        "3. Нажимает кнопку «Добавить объект»\n"
        "4. Заполняет форму: адрес, площадь, цена, фото\n"
        "5. Указывает контактные данные\n"
        "6. Публикует объявление\n"
        "7. Получает уведомление о публикации\n"
        "8. Отслеживает количество просмотров\n"
        "9. Получает звонки от риелторов\n"
        "10. Выбирает лучшее предложение"
        );
    text2->setReadOnly(true);
    QVBoxLayout *lay2 = new QVBoxLayout;
    lay2->addWidget(text2);
    scenario2->setLayout(lay2);
    layout->addWidget(scenario2);

    // Сценарий 3
    QGroupBox *scenario3 = new QGroupBox("👩‍💼 Сценарий 3: Управление сделками");
    QTextEdit *text3 = new QTextEdit;
    text3->setStyleSheet("font-family: monospace; font-size: 13px; background-color: #f8f9fa;");
    text3->setText(
        "Риелтор Анна управляет сделками в агентстве.\n\n"
        "1. Входит в личный кабинет риелтора\n"
        "2. Видит список своих объектов\n"
        "3. Открывает календарь просмотров\n"
        "4. Подтверждает запись клиента на просмотр\n"
        "5. После просмотра вносит отзыв клиента\n"
        "6. При согласии клиента создает сделку\n"
        "7. Заполняет документы в системе\n"
        "8. Закрывает сделку\n"
        "9. Формирует отчет по итогам месяца"
        );
    text3->setReadOnly(true);
    QVBoxLayout *lay3 = new QVBoxLayout;
    lay3->addWidget(text3);
    scenario3->setLayout(lay3);
    layout->addWidget(scenario3);

    layout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scroll);
    widget->setLayout(mainLayout);
    return widget;
}

// ==================== ВКЛАДКА 3: СЦЕНАРИИ ИСПОЛЬЗОВАНИЯ ====================

QWidget* MainWindow::createUseCasesTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("📋 Сценарии использования (Use Cases)");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // Сценарий 1: Поиск и запись на просмотр
    QGroupBox *uc1 = new QGroupBox("📋 Сценарий 1: Поиск объекта и запись на просмотр");
    QVBoxLayout *uc1Layout = new QVBoxLayout;

    QLabel *uc1Info = new QLabel(
        "Название: Поиск объекта и запись на просмотр\n"
        "Первичные актёры: Клиент (авторизованный)\n"
        "Предусловие: Клиент авторизован, открыта главная страница"
        );
    uc1Info->setStyleSheet("font-size: 13px; padding: 5px; background-color: #e8f4fd; border-radius: 3px;");
    uc1Info->setWordWrap(true);
    uc1Layout->addWidget(uc1Info);

    QLabel *uc1Main = new QLabel(
        "Основной сценарий:\n"
        "1. Клиент вводит параметры поиска (район, цена, комнаты)\n"
        "2. Система выводит список объектов\n"
        "3. Клиент открывает карточку объекта\n"
        "4. Клиент изучает информацию, фото, характеристики\n"
        "5. Клиент нажимает кнопку «Записаться на просмотр»\n"
        "6. Система отображает календарь с доступными датами\n"
        "7. Клиент выбирает удобное время\n"
        "8. Система отправляет запрос риелтору\n"
        "9. Риелтор подтверждает запись\n"
        "10. Клиент получает уведомление о подтверждении"
        );
    uc1Main->setStyleSheet("font-size: 13px; padding: 10px; font-family: monospace;");
    uc1Main->setWordWrap(true);
    uc1Layout->addWidget(uc1Main);

    QLabel *uc1Alt = new QLabel(
        "Альтернативный сценарий 1: Нет подходящих объектов\n"
        "3.1 Система отображает сообщение «По вашему запросу ничего не найдено»\n"
        "3.2 Клиент изменяет параметры поиска\n"
        "3.3 Система повторяет поиск"
        );
    uc1Alt->setStyleSheet("font-size: 13px; padding: 10px; background-color: #fff3cd; border-radius: 3px; font-family: monospace;");
    uc1Alt->setWordWrap(true);
    uc1Layout->addWidget(uc1Alt);

    QLabel *uc1Alt2 = new QLabel(
        "Альтернативный сценарий 2: Клиент не авторизован\n"
        "5.1 При нажатии «Записаться на просмотр» система предлагает авторизоваться\n"
        "5.2 Клиент переходит на страницу входа\n"
        "5.3 После авторизации возвращается к карточке объекта"
        );
    uc1Alt2->setStyleSheet("font-size: 13px; padding: 10px; background-color: #fff3cd; border-radius: 3px; font-family: monospace;");
    uc1Alt2->setWordWrap(true);
    uc1Layout->addWidget(uc1Alt2);

    uc1->setLayout(uc1Layout);
    layout->addWidget(uc1);

    // Сценарий 2: Добавление объекта
    QGroupBox *uc2 = new QGroupBox("📋 Сценарий 2: Добавление объекта недвижимости");
    QVBoxLayout *uc2Layout = new QVBoxLayout;

    QLabel *uc2Info = new QLabel(
        "Название: Добавление объекта недвижимости\n"
        "Первичные актёры: Продавец / Риелтор (авторизованный)\n"
        "Предусловие: Пользователь авторизован как риелтор или продавец"
        );
    uc2Info->setStyleSheet("font-size: 13px; padding: 5px; background-color: #e8f4fd; border-radius: 3px;");
    uc2Info->setWordWrap(true);
    uc2Layout->addWidget(uc2Info);

    QLabel *uc2Main = new QLabel(
        "Основной сценарий:\n"
        "1. Пользователь входит в личный кабинет\n"
        "2. Нажимает кнопку «Добавить объект»\n"
        "3. Система открывает форму добавления\n"
        "4. Пользователь заполняет поля (адрес, цена, площадь, описание)\n"
        "5. Пользователь загружает фото объекта\n"
        "6. Пользователь нажимает «Опубликовать»\n"
        "7. Система проверяет заполнение всех полей\n"
        "8. Система сохраняет объект в базе данных\n"
        "9. Система отображает объект в каталоге\n"
        "10. Пользователь получает уведомление об успешной публикации"
        );
    uc2Main->setStyleSheet("font-size: 13px; padding: 10px; font-family: monospace;");
    uc2Main->setWordWrap(true);
    uc2Layout->addWidget(uc2Main);

    QLabel *uc2Alt = new QLabel(
        "Альтернативный сценарий: Не все поля заполнены\n"
        "7.1 Система отображает сообщение «Заполните все обязательные поля»\n"
        "7.2 Пользователь заполняет пропущенные поля\n"
        "7.3 Система повторяет проверку"
        );
    uc2Alt->setStyleSheet("font-size: 13px; padding: 10px; background-color: #fff3cd; border-radius: 3px; font-family: monospace;");
    uc2Alt->setWordWrap(true);
    uc2Layout->addWidget(uc2Alt);

    uc2->setLayout(uc2Layout);
    layout->addWidget(uc2);

    // Сценарий 3: Оформление сделки
    QGroupBox *uc3 = new QGroupBox("📋 Сценарий 3: Оформление сделки");
    QVBoxLayout *uc3Layout = new QVBoxLayout;

    QLabel *uc3Info = new QLabel(
        "Название: Оформление сделки купли-продажи\n"
        "Первичные актёры: Риелтор\n"
        "Предусловие: Клиент согласен на покупку, объект в продаже"
        );
    uc3Info->setStyleSheet("font-size: 13px; padding: 5px; background-color: #e8f4fd; border-radius: 3px;");
    uc3Info->setWordWrap(true);
    uc3Layout->addWidget(uc3Info);

    QLabel *uc3Main = new QLabel(
        "Основной сценарий:\n"
        "1. Риелтор открывает карточку клиента\n"
        "2. Нажимает «Создать сделку»\n"
        "3. Система открывает форму сделки\n"
        "4. Риелтор выбирает объект из списка\n"
        "5. Вводит финальную цену и дату сделки\n"
        "6. Нажимает «Сохранить»\n"
        "7. Система создает запись о сделке\n"
        "8. Система меняет статус объекта на «Продан»\n"
        "9. Система отправляет уведомление клиенту\n"
        "10. Риелтор формирует документы в PDF"
        );
    uc3Main->setStyleSheet("font-size: 13px; padding: 10px; font-family: monospace;");
    uc3Main->setWordWrap(true);
    uc3Layout->addWidget(uc3Main);

    uc3->setLayout(uc3Layout);
    layout->addWidget(uc3);

    layout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scroll);
    widget->setLayout(mainLayout);
    return widget;
}

// ==================== ВКЛАДКА 4: ДИАГРАММЫ ПУТЕЙ ====================

QWidget* MainWindow::createUserFlowTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("🗺️ Диаграммы пользовательских путей (User Flow)");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QLabel *desc = new QLabel(
        "User Flow — это наглядное представление последовательности действий пользователя для достижения цели."
        );
    desc->setStyleSheet("font-size: 14px; padding: 10px; background-color: #f0f8ff; border-radius: 5px;");
    desc->setWordWrap(true);
    layout->addWidget(desc);

    // Путь 1: Поиск и покупка
    QGroupBox *flow1 = new QGroupBox("🗺️ Путь 1: Поиск и покупка квартиры");
    QTextEdit *text1 = new QTextEdit;
    text1->setStyleSheet("font-family: monospace; font-size: 14px; background-color: #f8f9fa;");
    text1->setText(
        "Главная → Поиск (параметры) → Результаты поиска → Карточка объекта\n"
        "    ↓\n"
        "    ↓ (понравилось)\n"
        "    ↓\n"
        "Запись на просмотр → Выбор даты/времени → Подтверждение → Уведомление\n"
        "    ↓\n"
        "    ↓ (осмотр прошел успешно)\n"
        "    ↓\n"
        "Оформление сделки → Документы → Оплата → Поздравление!"
        );
    text1->setReadOnly(true);
    QVBoxLayout *lay1 = new QVBoxLayout;
    lay1->addWidget(text1);
    flow1->setLayout(lay1);
    layout->addWidget(flow1);

    // Путь 2: Размещение объекта
    QGroupBox *flow2 = new QGroupBox("🗺️ Путь 2: Размещение объекта продавцом");
    QTextEdit *text2 = new QTextEdit;
    text2->setStyleSheet("font-family: monospace; font-size: 14px; background-color: #f8f9fa;");
    text2->setText(
        "Главная → Вход/Регистрация → Личный кабинет → Добавить объект\n"
        "    ↓\n"
        "    ↓ (заполнение формы)\n"
        "    ↓\n"
        "Адрес → Цена → Площадь → Комнаты → Описание → Фото\n"
        "    ↓\n"
        "    ↓ (проверка)\n"
        "    ↓\n"
        "Опубликовать → Уведомление → Объект в каталоге → Отслеживание просмотров"
        );
    text2->setReadOnly(true);
    QVBoxLayout *lay2 = new QVBoxLayout;
    lay2->addWidget(text2);
    flow2->setLayout(lay2);
    layout->addWidget(flow2);

    // Путь 3: Управление сделками (риелтор)
    QGroupBox *flow3 = new QGroupBox("🗺️ Путь 3: Управление сделками (риелтор)");
    QTextEdit *text3 = new QTextEdit;
    text3->setStyleSheet("font-family: monospace; font-size: 14px; background-color: #f8f9fa;");
    text3->setText(
        "Главная → Вход (риелтор) → Личный кабинет → Мои объекты\n"
        "    ↓\n"
        "    ↓ (выбор объекта)\n"
        "    ↓\n"
        "Карточка объекта → Записи на просмотр → Календарь\n"
        "    ↓\n"
        "    ↓ (клиент согласен)\n"
        "    ↓\n"
        "Создать сделку → Заполнить документы → Закрыть сделку → Отчет"
        );
    text3->setReadOnly(true);
    QVBoxLayout *lay3 = new QVBoxLayout;
    lay3->addWidget(text3);
    flow3->setLayout(lay3);
    layout->addWidget(flow3);

    // Путь 4: Регистрация
    QGroupBox *flow4 = new QGroupBox("🗺️ Путь 4: Регистрация пользователя");
    QTextEdit *text4 = new QTextEdit;
    text4->setStyleSheet("font-family: monospace; font-size: 14px; background-color: #f8f9fa;");
    text4->setText(
        "Главная → Регистрация\n"
        "    ↓\n"
        "    ↓ (ввод данных)\n"
        "    ↓\n"
        "Имя → Email → Пароль → Телефон\n"
        "    ↓\n"
        "    ↓ (отправка)\n"
        "    ↓\n"
        "Подтверждение email → Переход по ссылке → Вход → Личный кабинет"
        );
    text4->setReadOnly(true);
    QVBoxLayout *lay4 = new QVBoxLayout;
    lay4->addWidget(text4);
    flow4->setLayout(lay4);
    layout->addWidget(flow4);

    layout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scroll);
    widget->setLayout(mainLayout);
    return widget;
}

// ==================== ВКЛАДКА 5: КАРТА ЭКРАНОВ ====================

QWidget* MainWindow::createScreenMapTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("📱 Карта экранов приложения");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QLabel *desc = new QLabel(
        "Карта экранов показывает все страницы приложения и переходы между ними."
        );
    desc->setStyleSheet("font-size: 14px; padding: 10px; background-color: #f0f8ff; border-radius: 5px;");
    desc->setWordWrap(true);
    layout->addWidget(desc);

    // Карта экранов
    QGroupBox *mapBox = new QGroupBox("📱 Карта экранов RealtyPro");
    QTextEdit *mapText = new QTextEdit;
    mapText->setStyleSheet("font-family: monospace; font-size: 12px; background-color: #f8f9fa;");
    mapText->setText(
        "┌─────────────────────────────────────────────────────────────────────┐\n"
        "│                       КАРТА ЭКРАНОВ REALTYPRO                      │\n"
        "├─────────────────────────────────────────────────────────────────────┤\n"
        "│                                                                     │\n"
        "│  ┌──────────────┐                                                  │\n"
        "│  │  ГЛАВНАЯ     │ ────────┐                                        │\n"
        "│  │  Страница    │         ↓                                        │\n"
        "│  └──────────────┘    ┌──────────────┐    ┌──────────────┐        │\n"
        "│         │             │  КАТАЛОГ    │ ──│  КАРТОЧКА   │        │\n"
        "│         ↓             │  Объектов   │    │  Объекта    │        │\n"
        "│    ┌──────────────┐   └──────────────┘    └──────────────┘        │\n"
        "│    │   ВХОД/      │         │                     │                │\n"
        "│    │  Регистрация │         ↓                     ↓                │\n"
        "│    └──────────────┘   ┌──────────────┐    ┌──────────────┐        │\n"
        "│         │             │  РЕЗУЛЬТАТЫ  │    │  ЗАПИСЬ НА  │        │\n"
        "│         ↓             │  Поиска      │    │  ПРОСМОТР   │        │\n"
        "│    ┌──────────────┐   └──────────────┘    └──────────────┘        │\n"
        "│    │  ЛИЧНЫЙ      │         │                     │                │\n"
        "│    │  КАБИНЕТ     │         ↓                     ↓                │\n"
        "│    └──────────────┘   ┌──────────────┐    ┌──────────────┐        │\n"
        "│         │             │  ИЗБРАННОЕ   │    │  ПОДТВЕРЖДЕНИЕ│        │\n"
        "│         ↓             └──────────────┘    │  ЗАПИСИ     │        │\n"
        "│    ┌──────────────┐                        └──────────────┘        │\n"
        "│    │  МОИ ОБЪЕКТЫ │                              │                │\n"
        "│    └──────────────┘                              ↓                │\n"
        "│         │                                 ┌──────────────┐        │\n"
        "│         ↓                                 │  СДЕЛКА      │        │\n"
        "│    ┌──────────────┐                        │  Оформление  │        │\n"
        "│    │  ДОБАВИТЬ    │                        └──────────────┘        │\n"
        "│    │  ОБЪЕКТ      │                              │                │\n"
        "│    └──────────────┘                              ↓                │\n"
        "│                                              ┌──────────────┐        │\n"
        "│                                              │  ДОКУМЕНТЫ  │        │\n"
        "│                                              └──────────────┘        │\n"
        "│                                                                     │\n"
        "│  Легенда: ──→ основной переход    ──→ альтернативный переход      │\n"
        "└─────────────────────────────────────────────────────────────────────┘"
        );
    mapText->setReadOnly(true);
    QVBoxLayout *mapLayout = new QVBoxLayout;
    mapLayout->addWidget(mapText);
    mapBox->setLayout(mapLayout);
    layout->addWidget(mapBox);

    // Описание экранов
    QGroupBox *descBox = new QGroupBox("📋 Описание экранов");
    QTextEdit *descText = new QTextEdit;
    descText->setStyleSheet("font-family: monospace; font-size: 12px; background-color: #f8f9fa;");
    descText->setText(
        "1. Главная страница — поиск, популярные объекты, статистика\n"
        "2. Вход/Регистрация — форма авторизации и регистрации\n"
        "3. Личный кабинет — профиль пользователя, настройки\n"
        "4. Каталог объектов — список с фильтрами и поиском\n"
        "5. Результаты поиска — объекты по заданным параметрам\n"
        "6. Карточка объекта — подробная информация с фото\n"
        "7. Запись на просмотр — выбор даты и времени\n"
        "8. Подтверждение записи — уведомление об успехе\n"
        "9. Избранное — сохраненные объекты клиента\n"
        "10. Мои объекты — список объектов риелтора\n"
        "11. Добавить объект — форма создания объекта\n"
        "12. Оформление сделки — создание сделки с клиентом\n"
        "13. Документы — формирование PDF документов"
        );
    descText->setReadOnly(true);
    QVBoxLayout *descLayout = new QVBoxLayout;
    descLayout->addWidget(descText);
    descBox->setLayout(descLayout);
    layout->addWidget(descBox);

    layout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scroll);
    widget->setLayout(mainLayout);
    return widget;
}

// ==================== ВКЛАДКА 6: КОНТРОЛЬНЫЕ ВОПРОСЫ ====================

QWidget* MainWindow::createAnswersTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("❓ Контрольные вопросы");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QLabel *desc = new QLabel("Ответы на контрольные вопросы по теме «Пользовательские сценарии»");
    desc->setStyleSheet("font-size: 14px; padding: 10px; background-color: #f0f8ff; border-radius: 5px;");
    desc->setWordWrap(true);
    layout->addWidget(desc);

    // Вопросы и ответы
    QList<QPair<QString, QString>> qa = {
        {
            "1) Что такое пользовательская история?",
            "Пользовательская история — это описание потребности пользователя в формате:\n"
            "«Как <тип пользователя>, я хочу <цель>, чтобы <причина>».\n\n"
            "Пример: «Как риелтор, я хочу быстро добавлять объекты в базу, чтобы эффективно работать»."
        },
        {
            "2) Что такое концептуальный сценарий?",
            "Концептуальный сценарий — это обобщенное описание взаимодействия пользователя с системой,\n"
            "которое объединяет множество похожих пользовательских историй.\n\n"
            "Пример: «Пользователь ищет квартиру: заходит на сайт, применяет фильтры, выбирает объект, записывается на просмотр»."
        },
        {
            "3) Что такое конкретный сценарий?",
            "Конкретный сценарий — это описание пути достижения цели конкретным персонажем (пользователем).\n"
            "В нем меньше абстракции и больше конкретики.\n\n"
            "Пример: «Анна-риелтор добавляет объект на продажу: заполняет форму, загружает фото, публикует»."
        },
        {
            "4) Что такое сценарий использования?",
            "Сценарий использования (Use Case) — это детализированное описание взаимодействия\n"
            "пользователя с системой шаг за шагом. Включает название, актёров, предусловие,\n"
            "основной сценарий и альтернативные сценарии."
        },
        {
            "5) Что включает в себя сценарий использования?",
            "Сценарий использования включает:\n"
            "• Название — краткое описание сценария\n"
            "• Первичные актёры — кто выполняет действия\n"
            "• Предусловие — условие для выполнения сценария\n"
            "• Основной сценарий — последовательность шагов\n"
            "• Альтернативные сценарии — варианты развития событий"
        },
        {
            "6) Что такое диаграмма пользовательского пути?",
            "Диаграмма пользовательского пути (User Flow) — это наглядное представление\n"
            "последовательности действий пользователя для достижения цели в приложении.\n\n"
            "Показывает переходы между экранами и помогает сделать интерфейс интуитивно понятным."
        },
        {
            "7) Что такое карта экранов?",
            "Карта экранов (User Flow Map) — это схема, состоящая из экранов или страниц приложения\n"
            "с минимальными деталями дизайна. Показывает логику и структуру интерфейса,\n"
            "основные элементы и функции на каждом экране."
        }
    };

    for (const auto &q : qa) {
        QGroupBox *box = new QGroupBox(q.first);
        QVBoxLayout *boxLayout = new QVBoxLayout;
        QLabel *answer = new QLabel(q.second);
        answer->setStyleSheet("font-size: 13px; padding: 10px; line-height: 1.6;");
        answer->setWordWrap(true);
        boxLayout->addWidget(answer);
        box->setLayout(boxLayout);
        layout->addWidget(box);
    }

    layout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scroll);
    widget->setLayout(mainLayout);
    return widget;
}