#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T13:07:47
#
#-------------------------------------------------

QT       += core gui network xml multimedia script  webkitwidgets  webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IM_QXmpp
TEMPLATE = app
RC_FILE = MyAppicon.rc

SOURCES += main.cpp\
    chatwindow.cpp \
    listwindow.cpp \
    loginwindow.cpp \
    session.cpp \
    qfiletrans.cpp \
    sendfiles.cpp \
    filereceivedlg.cpp \
    searchdlg.cpp \
    findfriend.cpp \
    roomchat.cpp \
    resetnickname.cpp \
    mucroom.cpp \
    selectmucroom.cpp \
    setdlg.cpp \
    chats.cpp \
    passworddlg.cpp \
    maindialog.cpp \
    setstate.cpp \
    skin/iconbutton.cpp \
    skin/tabbutton.cpp \
    skin/framelesswin.cpp \
    safe/safeping.cpp \
    loginwithsafe.cpp \
    skin/shadowdlg.cpp \
    widget.cpp

SOURCES += main.cpp\
    chatwindow.cpp \
    listwindow.cpp \
    loginwindow.cpp \
    session.cpp \
    qfiletrans.cpp \
    sendfiles.cpp \
    filereceivedlg.cpp \
    searchdlg.cpp \
    findfriend.cpp \
    roomchat.cpp \
    resetnickname.cpp \
    mucroom.cpp \
    selectmucroom.cpp \
    setdlg.cpp \
    set_dirpath.cpp \
    addfiles.cpp \
    skin/shadowdlg.cpp

HEADERS  += \
    chatwindow.h \
    listwindow.h \
    loginwindow.h \
    session.h \
    qfiletrans.h \
    sendfiles.h \
    filereceivedlg.h \
    searchdlg.h \
    findfriend.h \
    roomchat.h \
    resetnickname.h \
    mucroom.h \
    selectmucroom.h \
    setdlg.h \
    set_dirpath.h \
    addfiles.h \
    chats.h \
    passworddlg.h \
    maindialog.h \
    setstate.h \
    ui_listwindow.h \
    ui_maindialog.h \
    ui_chatwindow.h \
    ui_roomchat.h \
    ui_mucroom.h \
    skin/iconbutton.h \
    skin/tabbutton.h \
    skin/framelesswin.h \
    safe/safeping.h \
    loginwithsafe.h \
    skin/shadowdlg.h \
    widget.h \
    ui_widget.h

FORMS    += \
    #chatwindow.ui \
    #listwindow.ui \
    #loginwindow.ui \
    sendfiles.ui \
    filereceivedlg.ui \
    searchdlg.ui \
    findfriend.ui \
    #roomchat.ui \
    resetnickname.ui \
    #mucroom.ui \
    selectmucroom.ui \
    setdlg.ui \
    set_dirpath.ui \
    addfiles.ui \
    commitdlg.ui \
    chats.ui \
    passworddlg.ui \
    #maindialog.ui \
    setstate.ui


INCLUDEPATH += "E:\Workspace\QT\qxmpp-master\src\client"
INCLUDEPATH += "E:\Workspace\QT\qxmpp-master\src\base"

LIBS += "E:\Workspace\QT\build-qxmpp-unknown-Debug\src\qxmpp_d0.lib"


RESOURCES += \
    resource.qrc

OTHER_FILES += \
    exit.png \
    MyAppicon.rc

