cmake_minimum_required(VERSION 3.16)

project(Camera VERSION 0.1 LANGUAGES CXX)
set(OpenCV_DIR D:/DevelopTools/OpenCV4/build/x64/vc16/lib)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Concurrent)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)
find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)
qt_standard_project_setup()

qt_add_executable(appCamera
        main.cpp
)
INCLUDE_DIRECTORIES(./include ./Inc ${OpenCV_INCLUDE_DIRS}
        ${CUDA_INCLUDE_DIRS}
        D:/DevelopTools/TensorRT-8.6.0.12/include
        ./yolov5/include)

file(GLOB_RECURSE USERCODE "Src/*.*" "Inc/*.*")
qt_add_qml_module(appCamera
        URI Camera
        VERSION 1.0
        QML_FILES
        Main.qml
        SOURCES
        ${USERCODE}
)
add_subdirectory(QFModule)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCamera PROPERTIES
        #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCamera
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)
target_link_directories(appCamera
        PRIVATE ${CMAKE_SOURCE_DIR}/lib/
        D:/DevelopTools/TensorRT-8.6.0.12/lib
        ${CMAKE_SOURCE_DIR}/yolov5/lib
)
target_link_libraries(appCamera
        PRIVATE Qt6::Quick
        neoapi_cpp
        Qt6::Concurrent
        Qt6::SerialPort
        QFModuleplugin
        ${OpenCV_LIBS}
        ${CUDA_LIBS}
        yolov5segtrt.lib
)

include(GNUInstallDirs)
install(TARGETS appCamera
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
