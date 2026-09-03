# Tell CMake which behavior/policies this project expects. Qt 5 supports much
# older CMake versions, but 3.16 is a practical baseline with good Qt support.
# CMake command reference:
# https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html
cmake_minimum_required(VERSION 3.16)

# Create a project named QtBasics and enable C++ as its implementation language.
# VERSION is available to CMake as QtBasics_VERSION and related variables.
# https://cmake.org/cmake/help/latest/command/project.html
project(QtBasics VERSION 1.0 LANGUAGES CXX)

# Ask for standard C++17. REQUIRED prevents CMake from silently falling back to
# an older standard, while EXTENSIONS OFF selects portable ISO C++ rather than
# compiler-specific modes such as gnu++17.
# https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt uses code generators in addition to the C++ compiler:
#
# - AUTOMOC runs Qt's Meta-Object Compiler (moc) for classes containing
#   Q_OBJECT. moc generates the machinery used by signals, slots, properties,
#   and run-time type information.
# - AUTOUIC would convert any future Qt Designer .ui files into C++ headers.
# - AUTORCC would compile any future .qrc resource files containing icons,
#   translations, or other files embedded in the executable.
#
# CMake's Qt integration:
# https://cmake.org/cmake/help/latest/manual/cmake-qt.7.html
# Qt 5's CMake guide:
# https://doc.qt.io/archives/qt-5.15/cmake-manual.html
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Locate Qt 5.12 or newer and specifically require its Widgets module. REQUIRED
# stops configuration with a useful error if a matching Qt installation cannot
# be found. Qt5::Widgets will be made available as an imported CMake target.
# https://cmake.org/cmake/help/latest/command/find_package.html
find_package(Qt5 5.12 REQUIRED COMPONENTS Widgets)

# Define the executable and list every hand-written source/header belonging to
# it. Listing MainWindow.h lets AUTOMOC reliably discover its Q_OBJECT macro.
# https://cmake.org/cmake/help/latest/command/add_executable.html
add_executable(QtBasics
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
)

# Link the executable to Qt Widgets. PRIVATE means Qt is an implementation
# dependency of this executable and is not propagated to another CMake target.
# Qt5::Widgets also supplies its required include paths and compile definitions.
# https://cmake.org/cmake/help/latest/command/target_link_libraries.html
target_link_libraries(QtBasics PRIVATE Qt5::Widgets)

# When you are ready to use serial communication, install Qt SerialPort for the
# same Qt/compiler kit, then change the two active commands above as follows:
# find_package(Qt5 REQUIRED COMPONENTS Widgets SerialPort)
# target_link_libraries(QtBasics PRIVATE Qt5::Widgets Qt5::SerialPort)
# Qt 5 SerialPort module: https://doc.qt.io/archives/qt-5.15/qtserialport-index.html
