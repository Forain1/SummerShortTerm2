cmake_minimum_required(VERSION 3.19)
project(V1 LANGUAGES CXX)

find_package(Qt6 6.6 REQUIRED COMPONENTS Core Widgets Multimedia)


qt_standard_project_setup()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


qt_add_executable(V1
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    view/scene.h view/scene.cpp
    view/menu.h view/menu.cpp view/menu.ui
    src.qrc
    view/cast.h view/cast.cpp view/cast.ui
    model/character.h model/character.cpp
    model/characterstate.h model/characterstate.cpp

    model/scenestate.h model/scenestate.cpp
    common/index.h
    view/battle.h view/battle.cpp
    view/fighter.h view/fighter.cpp
    view/role.h view/role.cpp view/role.ui

    view/settlement.h view/settlement.cpp view/settlement.ui
    app/app.h app/app.cpp
    view/showhealth.h view/showhealth.cpp
    model/topmodel.h model/topmodel.cpp
    view/bgmplayer.h view/bgmplayer.cpp
    view/about.h view/about.cpp view/about.ui
    view/esc.h view/esc.cpp view/esc.ui

)

target_link_libraries(V1
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
)




include(GNUInstallDirs)

install(TARGETS V1
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET V1
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

add_subdirectory(test)
