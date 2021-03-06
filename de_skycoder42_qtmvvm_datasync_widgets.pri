QT *= network jsonserializer datasync

HEADERS += \
	$$PWD/datasyncdialog.h \
	$$PWD/userdataexchangedialog.h \
    $$PWD/changeremotedialog.h

SOURCES += \
	$$PWD/datasyncdialog.cpp \
	$$PWD/userdataexchangedialog.cpp \
    $$PWD/changeremotedialog.cpp

FORMS += \
	$$PWD/datasyncdialog.ui \
	$$PWD/userdataexchangedialog.ui \
    $$PWD/changeremotedialog.ui

RESOURCES += \
	$$PWD/de_skycoder42_qtmvvm_datasync_widgets.qrc
	
TRANSLATIONS += $$PWD/qtmvvm_datasync_widgets_de.ts \
	$$PWD/qtmvvm_datasync_widgets_template.ts

INCLUDEPATH += $$PWD
