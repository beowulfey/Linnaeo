QT       += core gui network

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#Application version
VERSION_MAJOR = 0
VERSION_MINOR = 5
VERSION_BUILD = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}


SOURCES += \
    alignworker.cpp \
    main.cpp \
    linnaeo.cpp \
    preferences.cpp \
    searchuniprot.cpp \
    seqeditor.cpp \
    seqentrytextedit.cpp \
    sequence.cpp \
    seqviewer.cpp \
    themes.cpp\

HEADERS += \
    alignworker.h \
    linnaeo.h \
    preferences.h \
    searchuniprot.h \
    seqeditor.h \
    seqentrytextedit.h \
    sequence.h \
    seqviewer.h \
    themes.h \


FORMS += \
    linnaeo.ui \
    preferences.ui \
    searchuniprot.ui \
    seqeditor.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = resources/icons/linnaeo.ico

RESOURCES += \
    resources/linnaeo.qrc

DISTFILES += \
    external/muscle/README.txt
