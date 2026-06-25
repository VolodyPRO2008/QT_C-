QT += widgets sql charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminpanel.cpp \
    attendancetab.cpp \
    attendancetablemodel.cpp \
    databasemanager.cpp \
    groupstab.cpp \
    groupstablemodel.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    models.cpp \
    reporttab.cpp \
    reporttablemodel.cpp \
    scheduletab.cpp \
    studentscheduletab.cpp \
    studentstab.cpp \
    studentstablemodel.cpp \
    studentviewtab.cpp \
    teacherviewtab.cpp

HEADERS += \
    adminpanel.h \
    attendancetab.h \
    attendancetablemodel.h \
    databasemanager.h \
    groupstab.h \
    groupstablemodel.h \
    loginwidget.h \
    mainwindow.h \
    models.h \
    reporttab.h \
    reporttablemodel.h \
    scheduletab.h \
    studentscheduletab.h \
    studentstab.h \
    studentstablemodel.h \
    studentviewtab.h \
    teacherviewtab.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
