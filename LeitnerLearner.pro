TARGET = LeitnerLearner

CONFIG += sailfishapp c++11

DEFINES += QML_APP

HEADERS += \
    src/abstractdatatype.h \
    src/abstractstoragebackend.h \
    src/filestoragebackend.h \
    src/global_definitions.h \
    src/singleton.h \
    src/sqlitestoragebackend.h \
    src/storagecache.h \
    src/modules/helpers.h \
    src/modules/bibleVerse/bookenum.h \
    src/modules/bibleVerse/booktitles.h \
    src/modules/bibleVerse/verse.h \
    src/modules/songVerse/songverse.h \

SOURCES += \
    src/abstractdatatype.cpp \
    src/abstractstoragebackend.cpp \
    src/filestoragebackend.cpp \
    src/main.cpp \
    src/singleton.cpp \
    src/sqlitestoragebackend.cpp \
    src/storagecache.cpp \
    src/modules/helpers.cpp \
    src/modules/bibleVerse/verse.cpp \
    src/modules/songVerse/songverse.cpp \

DISTFILES += \
    LeitnerLearner.desktop \
    qml/LeitnerLearner.qml \
    qml/cover/CoverPage.qml \
    qml/pages/ModeChooser.qml \
    qml/pages/VerseCheck.qml \
    qml/pages/VerseEntry.qml \
    rpm/LeitnerLearner.changes.in \
    rpm/LeitnerLearner.changes.run.in \
    rpm/LeitnerLearner.spec \
    rpm/LeitnerLearner.yaml \
    translations/*.ts \

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

TRANSLATIONS += translations/LeitnerLearner-de.ts
