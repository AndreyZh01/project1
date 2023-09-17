QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QTPLUGIN += QPSQL
TARGET = QtLanguage
CONFIG += c++17

SOURCES += \
    add_record.cpp \
    change_record.cpp \
    connection_dialog.cpp \
    database.cpp \
    delete_record.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    add_record.h \
    change_record.h \
    connection_dialog.h \
    database.h \
    delete_record.h \
    mainwindow.h

FORMS += \
    add_record.ui \
    change_record.ui \
    connection_dialog.ui \
    delete_record.ui \
    mainwindow.ui

TRANSLATIONS += \
    banks_ru_RU.ts \
    banks_en_EN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build-banks-Desktop_Qt_6_5_2_MinGW_64_bit-Debug/debug/libpq.dll \
    ../build-banks-Desktop_Qt_6_5_2_MinGW_64_bit-Debug/debug/libpq.lib \
    banks_ru_RU.qm

RESOURCES += \
    resources.qrc
