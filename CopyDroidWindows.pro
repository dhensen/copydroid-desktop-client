#-------------------------------------------------
#
# Project created by QtCreator 2012-01-11T23:59:46
#
#-------------------------------------------------

QT       += core gui network sql xml

TARGET = copydroid
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    copydroid.cpp \
    adddialog.cpp \
    attachdialog.cpp

HEADERS  += widget.h \
    copydroid.h \
    adddialog.h \
    attachdialog.h

FORMS    += widget.ui

OTHER_FILES += \
    copydroid.png \
    widget.rc

RESOURCES += \
    resources.qrc

RC_FILE = widget.rc




