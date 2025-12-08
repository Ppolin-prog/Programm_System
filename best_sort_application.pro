QT += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32 {
    QMAKE_POST_LINK += $$quote($$QMAKE_COPY_DIR "$$[QT_INSTALL_PLUGINS]/sqldrivers" "$$OUT_PWD/sqldrivers")
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authorization.cpp \
    data_base.cpp \
    main.cpp \
    mainwindow.cpp \
    registration.cpp \
    sort_functions.cpp \
    sort_with_range.cpp

HEADERS += \
    authorization.h \
    data_base.h \
    mainwindow.h \
    registration.h \
    sort_functions.h \
    sort_with_range.h

FORMS += \
    authorization.ui \
    mainwindow.ui \
    registration.ui \
    sort_with_range.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
