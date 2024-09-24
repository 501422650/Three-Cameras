
set(QML_IMPORT_PATH ${CMAKE_BINARY_DIR}/QFModule ${CMAKE_BINARY_DIR}/imports CACHE STRING "" FORCE)
find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Gui)
INCLUDE_DIRECTORIES(QFModule ./Control)
add_library(QFModule STATIC
        QFInit.hpp
)

qt_add_qml_module(QFModule
        URI QFModule
        VERSION 1.0
        QML_FILES
        ./Control/QFButton.qml
        ./Control/QFProgress.qml
        ./Control/QFUpload.qml
        ./Control/QFImgWindow.qml
        ./Control/QFTextInput.qml
        ./Control/QFTitle.qml
        ./Control/QFButton1.qml
        ./Control/QFButton2.qml
        ./Control/QFInput.qml
        ./Control/QFFolderDialog.qml
        ./Control/QFListView.qml
        ./Control/QFDialog.qml
        RESOURCES
        Image/button.png
        Image/button-d.png
        Image/light.png
        Image/upload.png
        Image/upload-d.png
        Image/textInput_bg.png
        Image/Background/background1.png
        Image/Background/background2.png
        Image/Background/background3.png
        Image/Background/background4.png
        Image/Background/background5.png
        Image/Title/title_background.png
        Image/Title/title_button1.png
        Image/Title/title_button1_c.png
        Image/Title/title_button2.png
        Image/Title/title_button2_c.png
        Image/Board/board1.png
        Image/Button/button1.png
        Image/Button/button1_c.png
        Image/Button/button2.png
        Image/Button/button2_c.png
        Image/Progress/progress1.png
        Image/Progress/progress2.png
        Image/TextInput/textinput1.png
        Image/TextInput/textinput2.png
        Image/TextInput/textinput3.png
        Image/TextInput/textinput4.png
        Image/TextInput/textinput5.png
        Image/TextInput/textinput6.png
        Image/TextInput/textinput7.png
        Image/ListView/head.png
        Image/ListView/item1.png
        Image/ListView/item2.png
        Image/ListView/item_clicked.png
        Image/ListView/ok.png
        Image/ListView/error.png
        Font/PangMenZhengDaoBiaoTiTiMianFeiBan-2.ttf
)
target_link_libraries(QFModule
        PRIVATE Qt6::Quick
        Qt6::Gui
)

