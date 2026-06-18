#include "mainwindow.h"
#include <QScrollArea>
#include <QHeaderView>  // ← ЭТО БЫЛО ПРОПУЩЕНО!

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("RealtyPro — Техническое задание. Вариант 5: Агентство недвижимости");
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

    tabs->addTab(createInfoTab(), "📋 Общая информация");
    tabs->addTab(createAnalogsTab(), "📊 Анализ аналогов");
    tabs->addTab(createRequirementsTab(), "📝 Требования");
    tabs->addTab(createAudienceTab(), "👤 Целевая аудитория");
    tabs->addTab(createStructureTab(), "🗺️ Структура");
    tabs->addTab(createScreensTab(), "🖥️ Макеты экранов");
    tabs->addTab(createDataTab(), "💾 Модель данных");
    tabs->addTab(createResultsTab(), "✅ Итоги");

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

// ==================== ВКЛАДКА 1: ОБЩАЯ ИНФОРМАЦИЯ ====================

QWidget* MainWindow::createInfoTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("🏢 RealtyPro — Агентство недвижимости");
    title->setStyleSheet("font-size: 26px; font-weight: bold; color: #2C3E50; padding: 10px;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QLabel *subtitle = new QLabel("Техническое задание | Вариант 5");
    subtitle->setStyleSheet("font-size: 16px; color: #7F8C8D;");
    subtitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(subtitle);

    layout->addSpacing(10);

    QGroupBox *infoBox = new QGroupBox("📌 Общая информация");
    QVBoxLayout *infoLayout = new QVBoxLayout;

    QStringList infoData = {
        "🔹 Название проекта: RealtyPro",
        "🔹 Тип: Веб-приложение для агентства недвижимости",
        "🔹 Цель: Управление объектами, клиентами, сделками и просмотрами",
        "🔹 Целевая аудитория: Риелторы, покупатели, продавцы, арендаторы",
        "🔹 Ключевая особенность: CRM-система для риелторов"
    };

    for (const QString &item : infoData) {
        QLabel *label = new QLabel(item);
        label->setStyleSheet("font-size: 14px; padding: 3px;");
        infoLayout->addWidget(label);
    }
    infoBox->setLayout(infoLayout);
    layout->addWidget(infoBox);

    QGroupBox *goalsBox = new QGroupBox("🎯 Основные цели");
    QHBoxLayout *goalsLayout = new QHBoxLayout;

    goalsLayout->addWidget(createCard("Эффективность", "Повышение эффективности работы риелторов", "📈"));
    goalsLayout->addWidget(createCard("Удобство", "Улучшение качества обслуживания клиентов", "👤"));
    goalsLayout->addWidget(createCard("Прозрачность", "Прозрачность всех процессов агентства", "👁️"));
    goalsLayout->addWidget(createCard("Рост", "Рост количества успешных сделок", "💰"));

    goalsBox->setLayout(goalsLayout);
    layout->addWidget(goalsBox);

    QGroupBox *descBox = new QGroupBox("📖 Описание проекта");
    QVBoxLayout *descLayout = new QVBoxLayout;
    QLabel *descText = new QLabel(
        "RealtyPro — это веб-приложение для агентства недвижимости, которое позволяет:\n\n"
        "• Хранить информацию об агентстве, его сотрудниках и клиентах\n"
        "• Отображать каталог объектов недвижимости (квартиры, дома, офисы, участки)\n"
        "• Осуществлять поиск и фильтрацию объектов по параметрам\n"
        "• Записывать клиентов на просмотр объектов\n"
        "• Вести историю сделок и формировать отчеты"
        );
    descText->setStyleSheet("font-size: 14px; padding: 10px; line-height: 1.6;");
    descText->setWordWrap(true);
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

// ==================== ВКЛАДКА 2: АНАЛИЗ АНАЛОГОВ ====================

QWidget* MainWindow::createAnalogsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("📊 Анализ аналогов");
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QStringList headers = {"Критерий", "RealtyPro", "ЦИАН", "Avito", "Домклик"};
    QList<QStringList> data = {
        {"Каталог объектов", "✅", "✅", "✅", "✅"},
        {"Поиск с фильтрами", "✅", "✅", "✅", "✅"},
        {"Карта с объектами", "✅", "✅", "✅", "✅"},
        {"ЛК риелтора", "✅", "❌", "❌", "❌"},
        {"ЛК клиента", "✅", "✅", "✅", "✅"},
        {"Запись на просмотр", "✅", "❌", "❌", "❌"},
        {"История сделок", "✅", "❌", "❌", "✅"},
        {"Чат с риелтором", "✅", "✅", "✅", "❌"},
        {"Ипотечный калькулятор", "✅", "✅", "❌", "✅"}
    };

    QTableWidget *table = createTable(headers, data);
    layout->addWidget(table);

    QGroupBox *conclusionBox = new QGroupBox("📌 Выводы по анализу");
    QVBoxLayout *conclusionLayout = new QVBoxLayout;
    QLabel *conclusion = new QLabel(
        "Основные конкуренты ориентированы на клиентов, а не на агентства.\n\n"
        "Наше приложение будет сочетать:\n"
        "• Удобный интерфейс для клиентов (поиск, фильтры, запись на просмотр)\n"
        "• Профессиональные инструменты для риелторов (CRM, история сделок)\n"
        "• Административный модуль для руководства (отчеты, аналитика)"
        );
    conclusion->setStyleSheet("font-size: 14px; padding: 10px; line-height: 1.6;");
    conclusion->setWordWrap(true);
    conclusionLayout->addWidget(conclusion);
    conclusionBox->setLayout(conclusionLayout);
    layout->addWidget(conclusionBox);

    return widget;
}

// ==================== ВКЛАДКА 3: ТРЕБОВАНИЯ ====================

QWidget* MainWindow::createRequirementsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("📝 Функциональные требования");
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // Модуль 1: Агентство
    QGroupBox *agencyBox = new QGroupBox("🏢 Модуль «Агентство»");
    QStringList headers1 = {"ID", "Требование", "Приоритет"};
    QList<QStringList> data1 = {
        {"FR1", "Отображение информации об агентстве", "Высокий"},
        {"FR2", "Редактирование информации об агентстве", "Высокий"},
        {"FR3", "Отображение списка сотрудников", "Высокий"},
        {"FR4", "Добавление/удаление сотрудников", "Высокий"}
    };
    QVBoxLayout *agencyLayout = new QVBoxLayout;
    agencyLayout->addWidget(createTable(headers1, data1));
    agencyBox->setLayout(agencyLayout);
    layout->addWidget(agencyBox);

    // Модуль 2: Объекты
    QGroupBox *propsBox = new QGroupBox("🏠 Модуль «Объекты недвижимости»");
    QStringList headers2 = {"ID", "Требование", "Приоритет"};
    QList<QStringList> data2 = {
        {"FR6", "Добавление объекта (адрес, цена, фото)", "Высокий"},
        {"FR7", "Редактирование объекта", "Высокий"},
        {"FR8", "Удаление объекта", "Высокий"},
        {"FR9", "Просмотр каталога с фото", "Высокий"},
        {"FR10", "Фильтрация объектов по параметрам", "Высокий"},
        {"FR11", "Поиск объектов по адресу", "Высокий"},
        {"FR12", "Отображение объектов на карте", "Средний"},
        {"FR13", "Статус объекта (в продаже/продан)", "Высокий"}
    };
    QVBoxLayout *propsLayout = new QVBoxLayout;
    propsLayout->addWidget(createTable(headers2, data2));
    propsBox->setLayout(propsLayout);
    layout->addWidget(propsBox);

    // Модуль 3: Клиенты
    QGroupBox *clientsBox = new QGroupBox("👤 Модуль «Клиенты»");
    QStringList headers3 = {"ID", "Требование", "Приоритет"};
    QList<QStringList> data3 = {
        {"FR15", "Регистрация клиента (ФИО, телефон, email)", "Высокий"},
        {"FR16", "Просмотр списка клиентов", "Высокий"},
        {"FR17", "Поиск клиентов по ФИО или телефону", "Высокий"},
        {"FR18", "История просмотренных объектов", "Средний"},
        {"FR19", "Отметка клиента как «постоянный»", "Низкий"}
    };
    QVBoxLayout *clientsLayout = new QVBoxLayout;
    clientsLayout->addWidget(createTable(headers3, data3));
    clientsBox->setLayout(clientsLayout);
    layout->addWidget(clientsBox);

    // Модуль 4: Сделки
    QGroupBox *dealsBox = new QGroupBox("💰 Модуль «Сделки»");
    QStringList headers4 = {"ID", "Требование", "Приоритет"};
    QList<QStringList> data4 = {
        {"FR20", "Создание сделки (клиент, объект, сумма)", "Высокий"},
        {"FR21", "Просмотр истории сделок", "Высокий"},
        {"FR22", "Статус сделки (в процессе/завершена)", "Высокий"},
        {"FR23", "Формирование документов по сделке", "Низкий"}
    };
    QVBoxLayout *dealsLayout = new QVBoxLayout;
    dealsLayout->addWidget(createTable(headers4, data4));
    dealsBox->setLayout(dealsLayout);
    layout->addWidget(dealsBox);

    // Модуль 5: Просмотры
    QGroupBox *viewingBox = new QGroupBox("📅 Модуль «Просмотры»");
    QStringList headers5 = {"ID", "Требование", "Приоритет"};
    QList<QStringList> data5 = {
        {"FR24", "Запись клиента на просмотр объекта", "Высокий"},
        {"FR25", "Календарь просмотров для сотрудника", "Высокий"},
        {"FR26", "Подтверждение/отмена просмотра", "Средний"},
        {"FR27", "Отзыв клиента о просмотре", "Низкий"}
    };
    QVBoxLayout *viewingLayout = new QVBoxLayout;
    viewingLayout->addWidget(createTable(headers5, data5));
    viewingBox->setLayout(viewingLayout);
    layout->addWidget(viewingBox);

    return widget;
}

// ==================== ВКЛАДКА 4: ЦЕЛЕВАЯ АУДИТОРИЯ ====================

QWidget* MainWindow::createAudienceTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("👤 Целевая аудитория");
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QGroupBox *groupsBox = new QGroupBox("Группы пользователей");
    QStringList headers = {"Группа", "Возраст", "Особенности", "Потребности"};
    QList<QStringList> data = {
        {"Риелторы", "25-55", "Профессионалы рынка", "Управление объектами, клиентами, сделки"},
        {"Покупатели", "25-50", "Ищут жилье для семьи", "Простой поиск, запись на просмотр"},
        {"Продавцы", "30-60", "Хотят продать объект", "Размещение объекта, отслеживание"},
        {"Арендаторы", "18-35", "Снимают жилье", "Поиск по параметрам, быстрая связь"},
        {"Администратор", "30-50", "Управляет агентством", "Отчеты, аналитика, сотрудники"}
    };
    QVBoxLayout *groupsLayout = new QVBoxLayout;
    groupsLayout->addWidget(createTable(headers, data));
    groupsBox->setLayout(groupsLayout);
    layout->addWidget(groupsBox);

    QGroupBox *personasBox = new QGroupBox("Портреты пользователей (Personas)");
    QVBoxLayout *personasLayout = new QVBoxLayout;

    QStringList personas = {
        "👩‍💼 Риелтор Анна (35 лет):\n"
        "   • Опыт: 7 лет в недвижимости\n"
        "   • Цели: Быстро добавлять объекты, вести историю сделок\n"
        "   • Ожидания: Интуитивный интерфейс, быстрый поиск\n\n",

        "👨‍💼 Покупатель Дмитрий (28 лет):\n"
        "   • Семья: жена, ребенок 2 года\n"
        "   • Бюджет: 5-6 млн рублей\n"
        "   • Цели: Купить 2-комнатную квартиру\n"
        "   • Ожидания: Удобные фильтры, запись на просмотр онлайн\n\n",

        "👩‍💼 Администратор Ольга (42 года):\n"
        "   • Должность: Директор агентства\n"
        "   • Цели: Контроль работы риелторов, статистика\n"
        "   • Ожидания: Отчеты по продажам, управление сотрудниками"
    };

    for (const QString &p : personas) {
        QLabel *label = new QLabel(p);
        label->setStyleSheet("font-size: 13px; padding: 8px; background-color: #f8f9fa; border-radius: 5px;");
        label->setWordWrap(true);
        personasLayout->addWidget(label);
    }

    personasBox->setLayout(personasLayout);
    layout->addWidget(personasBox);

    return widget;
}

// ==================== ВКЛАДКА 5: СТРУКТУРА САЙТА ====================

QWidget* MainWindow::createStructureTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("🗺️ Структура сайта (Sitemap)");
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QTextEdit *structure = new QTextEdit;
    structure->setStyleSheet("font-family: monospace; font-size: 13px; background-color: #f8f9fa;");
    structure->setText(
        "RealtyPro (Агентство недвижимости)\n"
        "│\n"
        "├── Главная страница\n"
        "│   ├── Поиск объектов\n"
        "│   ├── Популярные объекты\n"
        "│   ├── Акции и спецпредложения\n"
        "│   └── Отзывы клиентов\n"
        "│\n"
        "├── Каталог объектов\n"
        "│   ├── Квартиры (Новостройки / Вторичка)\n"
        "│   ├── Дома и коттеджи\n"
        "│   ├── Офисы и коммерческая недвижимость\n"
        "│   ├── Земельные участки\n"
        "│   └── Поиск с фильтрами\n"
        "│\n"
        "├── Карточка объекта\n"
        "│   ├── Фото объекта\n"
        "│   ├── Описание и характеристики\n"
        "│   ├── Цена\n"
        "│   ├── Контактный риелтор\n"
        "│   ├── Запись на просмотр\n"
        "│   └── Похожие объекты\n"
        "│\n"
        "├── Личный кабинет (Риелтор)\n"
        "│   ├── Мои объекты\n"
        "│   ├── Мои клиенты\n"
        "│   ├── Календарь просмотров\n"
        "│   ├── История сделок\n"
        "│   └── Отчеты\n"
        "│\n"
        "├── Личный кабинет (Клиент)\n"
        "│   ├── Избранное\n"
        "│   ├── История просмотров\n"
        "│   ├── Запись на просмотр\n"
        "│   └── Настройки\n"
        "│\n"
        "├── Личный кабинет (Администратор)\n"
        "│   ├── Управление сотрудниками\n"
        "│   ├── Общая статистика\n"
        "│   ├── Отчеты по продажам\n"
        "│   └── Настройки системы\n"
        "│\n"
        "├── О компании\n"
        "│   ├── Информация об агентстве\n"
        "│   ├── Сотрудники\n"
        "│   ├── Отзывы\n"
        "│   └── Контакты\n"
        "│\n"
        "└── Вход/Регистрация\n"
        );
    structure->setReadOnly(true);
    layout->addWidget(structure);

    return widget;
}

// ==================== ВКЛАДКА 6: МАКЕТЫ ЭКРАНОВ ====================

QWidget* MainWindow::createScreensTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("🖥️ Макеты экранов");
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // Главная страница
    QGroupBox *mainPage = new QGroupBox("🏠 Главная страница");
    QTextEdit *mainText = new QTextEdit;
    mainText->setStyleSheet("font-family: monospace; font-size: 12px; background-color: #f8f9fa;");
    mainText->setText(
        "┌─────────────────────────────────────────────────────────────────┐\n"
        "│  🏠 RealtyPro  [Поиск...]          [Вход]  [Регистрация]       │\n"
        "├─────────────────────────────────────────────────────────────────┤\n"
        "│                                                                 │\n"
        "│  🏡 НАЙДИТЕ ЖИЛЬЕ МЕЧТЫ                                        │\n"
        "│  ┌─────────────────────────────────────────────────────────┐   │\n"
        "│  │  🔍 Найти объект...                                    │   │\n"
        "│  │  [Продажа] [Аренда]   [Квартира] [Дом] [Участок]      │   │\n"
        "│  └─────────────────────────────────────────────────────────┘   │\n"
        "│                                                                 │\n"
        "│  🔥 ПОПУЛЯРНЫЕ ОБЪЕКТЫ                                        │\n"
        "│  ┌────────────┐  ┌────────────┐  ┌────────────┐              │\n"
        "│  │  📸 Фото   │  │  📸 Фото   │  │  📸 Фото   │              │\n"
        "│  │  Квартира  │  │  Квартира  │  │  Дом       │              │\n"
        "│  │  3-комн    │  │  1-комн    │  │  150 м²    │              │\n"
        "│  │  8 500 000 │  │  4 200 000 │  │  12 000 000│              │\n"
        "│  └────────────┘  └────────────┘  └────────────┘              │\n"
        "│                                                                 │\n"
        "│  📊 СТАТИСТИКА АГЕНТСТВА                                       │\n"
        "│  ✅ 1 234 объекта   ✅ 567 сделок    ✅ 89 клиентов           │\n"
        "├─────────────────────────────────────────────────────────────────┤\n"
        "│  © RealtyPro 2026                                              │\n"
        "└─────────────────────────────────────────────────────────────────┘"
        );
    mainText->setReadOnly(true);
    QVBoxLayout *mainPageLayout = new QVBoxLayout;
    mainPageLayout->addWidget(mainText);
    mainPage->setLayout(mainPageLayout);
    layout->addWidget(mainPage);

    // Карточка объекта
    QGroupBox *cardPage = new QGroupBox("📄 Карточка объекта");
    QTextEdit *cardText = new QTextEdit;
    cardText->setStyleSheet("font-family: monospace; font-size: 12px; background-color: #f8f9fa;");
    cardText->setText(
        "┌─────────────────────────────────────────────────────────────────┐\n"
        "│  📍 3-комнатная квартира на ул. Мира, 15                      │\n"
        "│  ★ 4.8 (34 отзыва)                                            │\n"
        "│                                                                 │\n"
        "│  ┌─────────────────────┐  ┌─────────────────────────────────┐ │\n"
        "│  │  💰 Цена: 8 500 000 │  │  🏢 Характеристики:             │ │\n"
        "│  │  (свободна)         │  │  • Площадь: 78 м²               │ │\n"
        "│  │                     │  │  • Жилая площадь: 52 м²         │ │\n"
        "│  │  [ЗАПИСАТЬСЯ НА     │  │  • Кухня: 10 м²                │ │\n"
        "│  │   ПРОСМОТР]         │  │  • Этаж: 5/9                   │ │\n"
        "│  │                     │  │  • Год: 2018                    │ │\n"
        "│  │  [ДОБАВИТЬ В        │  │  • Состояние: евроремонт       │ │\n"
        "│  │   ИЗБРАННОЕ]        │  │  • Санузел: раздельный         │ │\n"
        "│  └─────────────────────┘  └─────────────────────────────────┘ │\n"
        "│                                                                 │\n"
        "│  👤 Риелтор: Анна Иванова   📱 +7 (999) 123-45-67            │\n"
        "│                                                                 │\n"
        "│  🔄 ПОХОЖИЕ ОБЪЕКТЫ                                           │\n"
        "│  ┌──────────┐ ┌──────────┐ ┌──────────┐                     │\n"
        "│  │ 2-комн   │ │ 4-комн   │ │ 3-комн   │                     │\n"
        "│  │ 6.2 млн  │ │ 12.5 млн │ │ 7.8 млн  │                     │\n"
        "│  └──────────┘ └──────────┘ └──────────┘                     │\n"
        "└─────────────────────────────────────────────────────────────────┘"
        );
    cardText->setReadOnly(true);
    QVBoxLayout *cardPageLayout = new QVBoxLayout;
    cardPageLayout->addWidget(cardText);
    cardPage->setLayout(cardPageLayout);
    layout->addWidget(cardPage);

    // ЛК Риелтора
    QGroupBox *realtorPage = new QGroupBox("👩‍💼 Личный кабинет риелтора");
    QTextEdit *realtorText = new QTextEdit;
    realtorText->setStyleSheet("font-family: monospace; font-size: 12px; background-color: #f8f9fa;");
    realtorText->setText(
        "┌─────────────────────────────────────────────────────────────────┐\n"
        "│  👩‍💼 ЛИЧНЫЙ КАБИНЕТ РИЕЛТОРА                                  │\n"
        "│                                                                 │\n"
        "│  [Мои объекты] [Мои клиенты] [Календарь] [Сделки] [Отчеты]    │\n"
        "│                                                                 │\n"
        "│  📊 Статистика:                                                │\n"
        "│  ┌────────────┐  ┌────────────┐  ┌────────────┐              │\n"
        "│  │  🏠 15     │  │  👤 23     │  │  💰 12     │              │\n"
        "│  │  Объектов  │  │  Клиентов  │  │  Сделок    │              │\n"
        "│  └────────────┘  └────────────┘  └────────────┘              │\n"
        "│                                                                 │\n"
        "│  🏠 МОИ ОБЪЕКТЫ                              [+ Добавить]     │\n"
        "│  ┌────────────┬──────────┬──────────┬──────────┐              │\n"
        "│  │  Название  │  Цена    │  Статус  │ Действия │              │\n"
        "│  ├────────────┼──────────┼──────────┼──────────┤              │\n"
        "│  │  ул. Мира  │ 8.5 млн  │ В продаже│ ✏️ 🗑️ │              │\n"
        "│  │  ул. Ленина│ 6.2 млн  │ В продаже│ ✏️ 🗑️ │              │\n"
        "│  │  пр. Побед │ 4.0 млн  │ Продан   │ 📋      │              │\n"
        "│  └────────────┴──────────┴──────────┴──────────┘              │\n"
        "│                                                                 │\n"
        "│  📅 КАЛЕНДАРЬ ПРОСМОТРОВ                                      │\n"
        "│  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐                │\n"
        "│  │ ПН  │ ВТ  │ СР  │ ЧТ  │ ПТ  │ СБ  │ ВС  │                │\n"
        "│  │     │     │ 10:00│     │ 11:00│ 15:00│     │                │\n"
        "│  └─────┴─────┴─────┴─────┴─────┴─────┴─────┘                │\n"
        "└─────────────────────────────────────────────────────────────────┘"
        );
    realtorText->setReadOnly(true);
    QVBoxLayout *realtorPageLayout = new QVBoxLayout;
    realtorPageLayout->addWidget(realtorText);
    realtorPage->setLayout(realtorPageLayout);
    layout->addWidget(realtorPage);

    layout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scroll);
    widget->setLayout(mainLayout);
    return widget;
}

// ==================== ВКЛАДКА 7: МОДЕЛЬ ДАННЫХ ====================

QWidget* MainWindow::createDataTab()
{
    QWidget *widget = new QWidget;
    QScrollArea *scroll = new QScrollArea(widget);
    scroll->setWidgetResizable(true);

    QWidget *content = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(content);

    QLabel *title = new QLabel("💾 Модель данных");
    title->setStyleSheet("font-size: 22px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // Сущности
    QStringList entities = {
        "🏢 Агентство (Agency): id, name, address, phone, email, description\n\n",
        "👩‍💼 Сотрудник (Employee): id, agency_id, first_name, last_name, position, phone, email, hire_date\n\n",
        "🏠 Объект (Property): id, employee_id, title, address, type, price, area, rooms, floor, status\n\n",
        "📸 Фото объекта (PropertyPhoto): id, property_id, photo_url, is_main\n\n",
        "👤 Клиент (Client): id, first_name, last_name, phone, email, budget_min, budget_max\n\n",
        "📅 Запись на просмотр (Viewing): id, property_id, client_id, employee_id, date, status\n\n",
        "💰 Сделка (Deal): id, property_id, client_id, employee_id, price, deal_date, status"
    };

    for (const QString &e : entities) {
        QLabel *label = new QLabel(e);
        label->setStyleSheet("font-family: monospace; font-size: 13px; padding: 5px;");
        label->setWordWrap(true);
        layout->addWidget(label);
    }

    // Схема связей
    QGroupBox *erBox = new QGroupBox("📊 Схема связей (ER-диаграмма)");
    QLabel *erLabel = new QLabel(
        "Agency (1) ──── (N) Employee\n"
        "Employee (1) ── (N) Property\n"
        "Property (1) ── (N) PropertyPhoto\n"
        "Client (N) ──── (N) Property (через Избранное)\n"
        "Client (1) ──── (N) Viewing\n"
        "Property (1) ── (N) Viewing\n"
        "Employee (1) ── (N) Viewing\n"
        "Client (1) ──── (N) Deal\n"
        "Property (1) ── (N) Deal\n"
        "Employee (1) ── (N) Deal"
        );
    erLabel->setStyleSheet("font-family: monospace; font-size: 14px; padding: 15px; background-color: #f8f9fa; border-radius: 5px;");
    erLabel->setWordWrap(true);

    QVBoxLayout *erLayout = new QVBoxLayout;
    erLayout->addWidget(erLabel);
    erBox->setLayout(erLayout);
    layout->addWidget(erBox);

    layout->addStretch();
    scroll->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scroll);
    widget->setLayout(mainLayout);
    return widget;
}

// ==================== ВКЛАДКА 8: ИТОГИ ====================

QWidget* MainWindow::createResultsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *title = new QLabel("✅ Итоговые результаты");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #2C3E50;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QGroupBox *summaryBox = new QGroupBox("📊 Сводка по ТЗ");
    QStringList headers = {"Раздел", "Статус", "Описание"};
    QList<QStringList> data = {
        {"Анализ аналогов", "✅ Выполнен", "Проанализированы ЦИАН, Avito, Домклик"},
        {"Функциональные требования", "✅ Выполнены", "30 требований с приоритетами"},
        {"Нефункциональные требования", "✅ Выполнены", "7 требований"},
        {"Целевая аудитория", "✅ Выполнена", "5 групп + 3 персонажа"},
        {"Структура сайта", "✅ Выполнена", "Полное дерево страниц"},
        {"Макеты экранов", "✅ Выполнены", "Главная, карточка, ЛК"},
        {"Модель данных", "✅ Выполнена", "7 сущностей + схема связей"}
    };
    QVBoxLayout *summaryLayout = new QVBoxLayout;
    summaryLayout->addWidget(createTable(headers, data));
    summaryBox->setLayout(summaryLayout);
    layout->addWidget(summaryBox);

    QLabel *verdict = new QLabel("✅ Техническое задание полностью готово к разработке!");
    verdict->setStyleSheet(
        "font-size: 20px; font-weight: bold; color: #27ae60; "
        "padding: 20px; background-color: #d5f5e3; border-radius: 10px;"
        );
    verdict->setAlignment(Qt::AlignCenter);
    layout->addWidget(verdict);

    QGroupBox *conclusionBox = new QGroupBox("📌 Выводы");
    QVBoxLayout *conclusionLayout = new QVBoxLayout;
    QLabel *conclusion = new QLabel(
        "Разработанное техническое задание описывает веб-приложение RealtyPro\n"
        "для агентства недвижимости.\n\n"
        "Приложение:\n"
        "1. Покрывает все потребности агентства\n"
        "2. Учитывает интересы всех участников\n"
        "3. Имеет понятную структуру с удобной навигацией\n"
        "4. Использует современные технологии\n\n"
        "В результате внедрения системы агентство получит:\n"
        "• 📈 Повышение эффективности работы риелторов\n"
        "• 👤 Улучшение качества обслуживания клиентов\n"
        "• 📊 Прозрачность всех процессов\n"
        "• 💰 Рост количества успешных сделок"
        );
    conclusion->setStyleSheet("font-size: 14px; padding: 10px; line-height: 1.8;");
    conclusion->setWordWrap(true);
    conclusionLayout->addWidget(conclusion);
    conclusionBox->setLayout(conclusionLayout);
    layout->addWidget(conclusionBox);

    layout->addStretch();
    return widget;
}