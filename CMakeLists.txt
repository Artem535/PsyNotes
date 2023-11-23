cmake_minimum_required(VERSION 3.16)

project(PsyNotes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_STANDARD 20)


# Adding objectbox support
if (NOT ANDROID)
    include(FetchContent)
    FetchContent_Declare(
        objectbox
        GIT_REPOSITORY https://github.com/objectbox/objectbox-c.git
        GIT_TAG        v0.19.0
    )

    FetchContent_MakeAvailable(objectbox)
else ()
    add_library(objectbox SHARED IMPORTED)
    set_property(TARGET objectbox PROPERTY
       IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/arm64-v8a/libobjectbox-jni.so)
    # Copy files
    file(GLOB libraries
        "${CMAKE_SOURCE_DIR}/lib/arm64-v8a/*")
    file(COPY ${libraries}
        DESTINATION ${CMAKE_BINARY_DIR}/android-build/libs/arm64-v8a/)

    include_directories(
        ./third-party/objectbox-c/include/
        ./third-party/flatbuffers/include
        )
endif()


find_package(Felgo REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core)


# Project identifier and version
# More information: https://felgo.com/doc/felgo-publishing/#project-configuration
set(PRODUCT_IDENTIFIER "com.PhoenixLab.PsyNotes")
set(PRODUCT_VERSION_NAME "1.0.0")
set(PRODUCT_VERSION_CODE 1)

# Set either "test" or "publish" stage:
set(PRODUCT_STAGE "test")

# Optionally set a license key that is used instead of the license key from
# main.qml file (App::licenseKey for your app or GameWindow::licenseKey for your game)
# Only used for local builds and Felgo Cloud Builds (https://felgo.com/cloud-builds)
# Not used if using Felgo Live
set(PRODUCT_LICENSE_KEY "B0030341A3D8B1312E118EAFE6D59A69A0ED364E692587C2C00C4AE5B208690A7B01C929553592082C5F236F800C7F5946A95F5D825BBA0A67A20AD274E581D9DE27010D561D780DB033AAEC8B0B5347AE4D60230F9CF83D0AD5AAB94F2B09A6DC1228F6295F48FB656D7F7FD5EFDF1B3A1A5AB6D3F26E46008D463354B626D0CE0F4B844B2D9454729D388753B4328D2818C902F82EC3841526969C0ADA77B3733A54BC181EAB77244B9B2907EDFDB47833704A29A5772F6B0527B078526308D9CE0E881E13DB22864E37341EC36EDF01AB5AD0519857D0C0423EF2E2DC985BD53AE096E4BF8F51774C5EE07D75D5796EC6939905D79A431806A6E51541D460570B69A9FC69078C6769A4B70570C5D49BEAC856DD77B5E2FCF70AC0D77A0E077F31B1545482A2A9F41147DBC696543F")

set(FELGO_PLUGINS
)

# Find all QML/JS files for the QML compiler:
file(GLOB_RECURSE QmlFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} qml/*.qml qml/*.js)

# Find all non-QML/JS files in the qml and assets folder to add as resources:
file(GLOB_RECURSE AssetsFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} assets/* qml/*)
list(REMOVE_ITEM AssetsFiles ${QmlFiles})

include_directories(headers
    headers/notestorage
    headers/database
    database)

file(GLOB_RECURSE SrcFiles  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*)
file(GLOB_RECURSE HeadersFiles  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} headers/*)

qt_add_executable(appPsyNotes
    ./src/main.cpp
    ${SrcFiles}
    ${HeadersFiles}
    ${QmlFiles}
    ${AssetsFiles}
)

felgo_configure_executable(appPsyNotes)

# Deploy resources to build folder/package directly
# comment for publishing
#deploy_resources("${QmlFiles};${AssetsFiles}")

# Add QML files and resources to QML module to included them via QRC automatically:
qt_add_qml_module(appPsyNotes
    URI PsyNotes
    VERSION 1.0
    # uncomment for publishing:
    QML_FILES ${QmlFiles}
    RESOURCES ${AssetsFiles}
)

# NOTE: for PUBLISHING, perform the following steps:
# 1. comment the deploy_resources line above, to avoid shipping your qml files with the application (instead they get compiled to the app binary)
# 2. uncomment the QML_FILES and RESOURCES above; this compiles your qml files and js files to the app binary and protects your source code
# 3. change the setMainQmlFile() call in main.cpp to the one starting with "qrc:/" - this loads the qml files from the resources
# for more details see the "Deployment Guides" in the Felgo Documentation

# during development, use the deploy_resources because you then get shorter compilation times (the qml files do not need to be compiled to the binary but are just copied)
# also, for quickest deployment on Desktop disable the "Shadow Build" option in Projects/Builds - you can then select "Run Without Deployment" from the Build menu in Qt Creator if you only changed QML files; this speeds up application start, because your app is not copied & re-compiled but just re-interpreted

target_compile_definitions(appPsyNotes
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(appPsyNotes
    PRIVATE
    objectbox
    Felgo)

# uncomment this line to add the Live Client Module and use live reloading with your custom C++ code
# for the remaining steps to build a custom Live Code Reload app see here: https://felgo.com/custom-code-reload-app/
#find_package(FelgoLive REQUIRED)
#target_link_libraries(appPsyNotes PRIVATE FelgoLive)
