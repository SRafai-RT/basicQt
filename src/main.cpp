// main.cpp is the program's entry point. Its responsibilities are intentionally
// small: construct Qt's application object, construct/show the main window, and
// start the event loop.
//
// QApplication: https://doc.qt.io/archives/qt-5.15/qapplication.html

#include "MainWindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    // Every Qt Widgets program needs exactly one QApplication. It initializes
    // the window system and processes Qt-specific command-line options. It must
    // exist before any QWidget (including MainWindow) is created.
    //
    // argc and argv are passed by reference/pointer because QApplication may
    // remove command-line arguments that Qt itself recognizes.
    QApplication application(argc, argv);
    
    QApplication::setStyle(QStyleFactory::create("macintosh"));
    
    application.setStyleSheet(R"(
    QMainWindow {
        background-color: #202124;
    }

    QLabel {
        color: #80cbb2;
        font-size: 16px;
    }

    QLineEdit {
        color: #ffffff;
        background-color: #303134;
        border: 1px solid #2e5cc0;
        border-radius: 4px;
        padding: 6px;
    }

    QPushButton {
        color: #ffffff;
        background-color: #5f6fce;
        border: none;
        border-radius: 4px;
        padding: 7px;
    }

    QPushButton:hover {
        background-color: #5c6bc0;
    }

    QPushButton:pressed {
        background-color: #303f9f;
    }
)");

    // MainWindow has no parent, so it is a top-level window. It is a local stack
    // object and will be destroyed automatically when main() eventually exits.
    MainWindow window;

    // Constructing a widget does not make it visible. show() asks the window
    // system to display it once the event loop begins processing events.
    window.show();

    qDebug() << "rendered window!";
    // exec() starts Qt's event loop. The loop waits for mouse, keyboard, timer,
    // paint, serial/network, and other events and dispatches them to QObjects.
    // It returns when the application quits, normally after the last window is
    // closed. Returning that value passes Qt's exit status to the operating
    // system.
    // Event loop overview: https://doc.qt.io/archives/qt-5.15/eventsandfilters.html
    return application.exec();
}
