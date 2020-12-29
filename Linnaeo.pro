QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    linnaeo.cpp \
    clustalo.cpp \
    preferences.cpp \
    searchuniprot.cpp \
    seqeditor.cpp \
    seqentrytextedit.cpp \
    sequence.cpp \
    seqviewer.cpp \
    themes.cpp

HEADERS += \
    linnaeo.h \
    clustalo.h \
    preferences.h \
    searchuniprot.h \
    seqeditor.h \
    seqentrytextedit.h \
    sequence.h \
    seqviewer.h \
    themes.h

FORMS += \
    linnaeo.ui \
    preferences.ui \
    searchuniprot.ui \
    seqeditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/external/clustalo/lib/ -lclustalo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/external/clustalo/lib/ -lclustalod

INCLUDEPATH += $$PWD/external/clustalo/include
DEPENDPATH += $$PWD/external/clustalo/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/external/clustalo/lib/libclustalo.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/external/clustalo/lib/libclustalo.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/external/clustalo/lib/clustalo.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/external/clustalo/lib/clustalo.lib
