#pragma once

// MainWindow is declared separately from its implementation so other source
// files can use the class without seeing every widget header and function body.
// #pragma once prevents accidental multiple inclusion of this header.

#include <QMainWindow>
#include <QString>

// Forward declarations are sufficient because this header stores only pointers
// to these classes. Their complete definitions are included in MainWindow.cpp,
// which keeps compile dependencies smaller.
class QLabel;
class QLineEdit;
class QPushButton;

// QMainWindow is a specialized QWidget with designated areas for a central
// widget, menus, toolbars, dock widgets, and a status bar.
// https://doc.qt.io/archives/qt-5.15/qmainwindow.html
class MainWindow : public QMainWindow
{
    // Q_OBJECT enables Qt's meta-object features for this class. It is required
    // here because MainWindow declares its own signal and slots. CMake's AUTOMOC
    // setting finds this macro and runs Qt's Meta-Object Compiler for us.
    // https://doc.qt.io/archives/qt-5.15/qobject.html#Q_OBJECT
    Q_OBJECT

public:
    // explicit prevents a QWidget* from being converted to MainWindow by
    // accident. A null parent makes this a top-level window by default.
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    // A signal announces that something happened without knowing who receives
    // it. moc generates this function, so it is declared but not implemented.
    // const QString& avoids copying while connected slots are being invoked.
    //
    // Later, a serial controller could receive this signal and write the text,
    // while the window remains independent of the serial implementation.
    // https://doc.qt.io/archives/qt-5.15/signalsandslots.html
    void messageSubmitted(const QString &message);

private slots:
    // Slots are ordinary member functions that may also be invoked through a
    // signal connection. "private" controls normal C++ calls, but a connected
    // signal can still invoke these slots through Qt's meta-object mechanism.
    void submitMessage();
    void displayMessage(const QString &message);
    void clearMessage();

private:
    // QObject-derived widgets are normally handled through pointers because
    // QObjects cannot be copied. Each widget receives a parent in the
    // constructor, so Qt owns and deletes it automatically; no destructor or
    // manual delete is required here.
    // https://doc.qt.io/archives/qt-5.15/objecttrees.html
    QLineEdit *messageInput_;
    QLabel *statusLabel_;
    QPushButton *sendButton_;
    QPushButton *clearButton_;
};
