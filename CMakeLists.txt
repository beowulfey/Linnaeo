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

#set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/linnaeo_win.rc")
#set(MACOSX_BUNDLE_ICON_FILE linnaeo_mac.icns)
#set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/linnaeo_mac.icns)
#set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

add_executable(Linnaeo
main.cpp
linnaeo.cpp
linnaeo.h
linnaeo.ui
preferences.h
preferences.cpp
preferences.ui
searchuniprot.h
searchuniprot.cpp
searchuniprot.ui
resources/linnaeo.qrc
#MACOSX_BUNDLE
#${APP_ICON_RESOURCE_WINDOWS}
#${APP_ICON_MACOSX}
)


target_link_libraries(Linnaeo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


