#-------------------------------------------------
#
# Project created by QtCreator 2012-01-11T23:59:46
#
#-------------------------------------------------

QT       += core gui network sql -plugin-sql-sqlite xml

TARGET = CopyDroidTest1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    copydroid.cpp \
    adddialog.cpp

HEADERS  += widget.h \
    copydroid.h \
    adddialog.h

FORMS    += widget.ui

OTHER_FILES += \
    copydroid.png \
    widget.rc

RESOURCES += \
    resources.qrc

RC_FILE = widget.rc



