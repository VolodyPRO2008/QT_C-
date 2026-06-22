QT += widgets sql charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attendancetab.cpp \
    attendancetablemodel.cpp \
    databasemanager.cpp \
    groupstab.cpp \
    groupstablemodel.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    reporttab.cpp \
    reporttablemodel.cpp \
    studentstab.cpp \
    studentstablemodel.cpp

HEADERS += \
    attendancetab.h \
    attendancetablemodel.h \
    databasemanager.h \
    groupstab.h \
    groupstablemodel.h \
    loginwidget.h \
    mainwindow.h \
    reporttab.h \
    reporttablemodel.h \
    studentstab.h \
    studentstablemodel.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
