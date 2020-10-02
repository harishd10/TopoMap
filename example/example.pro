TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../cpp/

SOURCES += \
        main.cpp

unix:!macx{
    INCLUDEPATH += -I /usr/local/include/
    LIBS += -L../cpp -lTopoMap
    LIBS += -L/usr/local/lib/

    QMAKE_CXXFLAGS += -fopenmp
    QMAKE_LFLAGS   += -fopenmp
}

win32-msvc*{
    CONFIG += console

    INCLUDEPATH += $$(VCPKG_HOME)/installed/x64-windows/include

    #http://stackoverflow.com/questions/5134245/how-to-set-different-qmake-configuration-depending-on-debug-release
    CONFIG(debug, debug|release) {
        WINDOWS_BIN_PATH = debug/
        LIBS += "-L../cpp/debug/" -lTopoMap
    } else {
        WINDOWS_BIN_PATH = ./
        LIBS += "-L../cpp/release/" -lTopoMap
    }

    QMAKE_CXXFLAGS += -openmp

    LIBS += "-L$$(VCPKG_HOME)/installed/x64-windows/$${WINDOWS_BIN_PATH}/bin"
    LIBS += "-ladvapi32"
    LIBS += -lopengl32 -lRpcRT4
}
