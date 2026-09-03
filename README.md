# Qt 5 Basics

A minimal Qt 5 Widgets application for learning Qt's object model and
signal/slot connections. The interface is constructed in C++ so all of the
important pieces are visible in the source. The hand-written files contain
line-by-line teaching comments and links to the relevant official references.

## What to look at

- `src/main.cpp` creates the application and main window, then starts Qt's
  event loop.
- `src/MainWindow.h` declares a custom signal and three slots.
- `src/MainWindow.cpp` creates widgets and connects signals to slots.
- `CMakeLists.txt` enables Qt's code generation and links Qt 5 Widgets.

## Build and run

From a terminal whose Qt 5 installation is available to CMake:

```sh
cmake -S . -B build
cmake --build build
./build/QtBasics
```

On Windows with a multi-configuration generator, the executable will usually
be under `build/Debug/QtBasics.exe` after this instead:

```powershell
cmake -S . -B build
cmake --build build --config Debug
./build/Debug/QtBasics.exe
```

If CMake cannot locate Qt, give it the Qt kit's CMake directory. For example:

```powershell
cmake -S . -B build -DCMAKE_PREFIX_PATH=C:/Qt/5.15.2/msvc2019_64
```

Use the path and compiler kit that match your Qt installation. An MSVC Qt kit
must be built with MSVC, and a MinGW Qt kit must be built with MinGW.

## Adding Qt SerialPort later

Install the Qt 5 SerialPort component for your kit, then update the CMake lines
as shown in the comments in `CMakeLists.txt`. Your communication code can live
in a separate `QObject` class and connect its signals to the window's slots.

## Recommended official reading

- [Qt 5 Signals & Slots](https://doc.qt.io/archives/qt-5.15/signalsandslots.html)
  explains decoupled communication between `QObject` instances.
- [QObject](https://doc.qt.io/archives/qt-5.15/qobject.html) covers the base Qt
  object type, `connect()`, the meta-object system, and thread affinity.
- [Object Trees & Ownership](https://doc.qt.io/archives/qt-5.15/objecttrees.html)
  explains why this project does not manually delete its child widgets.
- [QApplication](https://doc.qt.io/archives/qt-5.15/qapplication.html) documents
  application initialization and the main event loop.
- [QMainWindow](https://doc.qt.io/archives/qt-5.15/qmainwindow.html) describes
  the central widget, status bar, menus, toolbars, and dock areas.
- [Layout Management](https://doc.qt.io/archives/qt-5.15/layout.html) explains
  automatic positioning and resizing of child widgets.
- [Qt Serial Port](https://doc.qt.io/archives/qt-5.15/qtserialport-index.html)
  is the starting point for the project's planned serial features.
- [Qt Network](https://doc.qt.io/archives/qt-5.15/qtnetwork-index.html) covers
  TCP, UDP, local sockets, DNS, proxies, and higher-level network requests.
- [Using Qt with CMake](https://doc.qt.io/archives/qt-5.15/cmake-manual.html)
  explains Qt 5's imported CMake targets and build integration.
