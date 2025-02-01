TEMPLATE = app

QTITANDIR = $$quote($$(QTITANDIR))
INCLUDEPATH += $$quote($$PWD)

isEmpty(QTITANDIR):QTITANDIR = D:/Qt/Developer Machines/QtitanComponents2024.2.0 Demo

include($$QTITANDIR/src/shared/qtitanribbon.pri)
include($$QTITANDIR/src/shared/qtitanstyle.pri)
include($$QTITANDIR/src/shared/qtitanfastinfoset.pri)
include($$QTITANDIR/src/shared/qtitandocking.pri)
include($$QTITANDIR/src/shared/qtitangrid.pri)

#DESTDIR = $$QTITANDIR/bin
#DESTDIR = $$member(DESTDIR, 0)$$QTITAN_LIB_PREFIX

!debug_and_release|build_pass {
    CONFIG(debug, debug|release) {
        TARGET = $$member(TARGET, 0)d
    }
}

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    treeitem.cpp \
    treemodel.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    treeitem.h \
    treemodel.h


macx {
    CONFIG-=app_bundle
}

!lessThan(QT_VER_MAJ, 5) {
  QT += printsupport
}

RESOURCES += \
    UpdateWizardClone.qrc \
    treemodel.qrc
