cmake_minimum_required(VERSION 3.5)

project(Linnaeo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
find_package(spdlog CONFIG REQUIRED)

#set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/linnaeo_win.rc")
#set(MACOSX_BUNDLE_ICON_FILE linnaeo_mac.icns)
#set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/linnaeo_mac.icns)
#set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

add_executable(Linnaeo
main.cpp
linnaeo.cpp
linnaeo.h
linnaeo.ui
preferences.cpp
preferences.h
preferences.ui
seqeditor.cpp
seqeditor.h
seqeditor.ui
seqentrytextedit.cpp
seqentrytextedit.h
sequence.cpp
sequence.h
resources/linnaeo.qrc
README.md
searchuniprot.h
searchuniprot.cpp
searchuniprot.ui
#newsequence.cpp
#newsequence.h
#newsequence.ui
#folderitem.cpp
#folderitem.h
#MACOSX_BUNDLE
#${APP_ICON_RESOURCE_WINDOWS}
#${APP_ICON_MACOSX}
)


target_link_libraries(Linnaeo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt::Network spdlog::spdlog spdlog::spdlog_header_only)


