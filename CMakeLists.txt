cmake_minimum_required(VERSION 3.7.2 FATAL_ERROR)

project(BibleByByte
    VERSION 1.0
    LANGUAGES CXX)

enable_testing()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(bible_by_byte
    src/abstractcheckwdgt.cpp
    src/abstractdatachecker.cpp
    src/abstractdatachecker.ui
    src/abstractdataentry.cpp
    src/abstractdataentry.ui
    src/abstractdatatype.cpp
    src/abstractentrywdgt.cpp
    src/abstractstoragebackend.cpp
    src/backend.cpp
    src/configurationhandler.cpp
    src/filestoragebackend.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/singleton.cpp
    src/sqlitestoragebackend.cpp
    src/storagecache.cpp
    src/modules/helpers.cpp
    src/modules/bibleVerse/verse.cpp
    src/modules/bibleVerse/versechecker.cpp
    src/modules/bibleVerse/versecheckwdgt.cpp
    src/modules/bibleVerse/versecheckwdgt.ui
    src/modules/bibleVerse/verseentry.cpp
    src/modules/bibleVerse/verseentrywdgt.cpp
    src/modules/bibleVerse/verseentrywdgt.ui
    src/modules/songVerse/songverse.cpp
    src/modules/songVerse/songversechecker.cpp
    src/modules/songVerse/songversecheckwdgt.cpp
    src/modules/songVerse/songversecheckwdgt.ui
    src/modules/songVerse/songverseentry.cpp
    src/modules/songVerse/songverseentrywdgt.cpp
    src/modules/songVerse/songverseentrywdgt.ui)
target_compile_definitions(bible_by_byte PRIVATE WIDGETS_APP)
target_link_libraries(bible_by_byte PRIVATE Qt5::Widgets)

add_subdirectory(tests)
