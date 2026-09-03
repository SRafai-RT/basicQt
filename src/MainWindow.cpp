#include "MainWindow.h"

// This implementation file needs the full declarations for every Qt class on
// which it constructs an object or calls a member function.
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    // Initialize the base QMainWindow before executing the constructor body.
    // Member pointers start null and are assigned after centralWidget exists.
    : QMainWindow(parent),
      messageInput_(nullptr),
      statusLabel_(nullptr),
      sendButton_(nullptr),
      clearButton_(nullptr)
{
    // These properties describe the top-level native window. resize() supplies
    // an initial size, but the user and window manager may change it later.
    setWindowTitle("Qt 5 Basics");
    resize(480, 220);

    // QMainWindow expects application content inside one central widget. Passing
    // `this` as its parent transfers ownership to the MainWindow object.
    auto *centralWidget = new QWidget(this);

    // Create the interactive child widgets. Passing centralWidget as parent
    // makes the ownership tree explicit: deleting the window deletes its central
    // widget, which recursively deletes these controls.
    // QObject ownership: https://doc.qt.io/archives/qt-5.15/objecttrees.html
    messageInput_ = new QLineEdit(centralWidget);
    statusLabel_ = new QLabel("Ready", centralWidget);
    sendButton_ = new QPushButton("Send", centralWidget);
    clearButton_ = new QPushButton("Clear", centralWidget);

    // A layout calculates child positions and sizes whenever the window changes
    // size. Giving the layout centralWidget as parent also installs it as that
    // widget's layout and gives the widget ownership of the layout.
    // Layout management: https://doc.qt.io/archives/qt-5.15/layout.html
    auto *layout = new QVBoxLayout(centralWidget);

    // `auto` asks C++ to infer QLabel* from the expression. This label does not
    // need to be a member because no later function needs direct access to it.
    auto *instructions = new QLabel(
        "Enter a message, then press Send or Return.", centralWidget);

    // Placeholder text is a hint displayed only while the line edit is empty;
    // it is not part of text() and is not submitted.
    // https://doc.qt.io/archives/qt-5.15/qlineedit.html
    messageInput_->setPlaceholderText("Message to emit...");

    // Widgets are added from top to bottom. addStretch() consumes spare vertical
    // space, keeping the controls grouped near the top as the window grows.
    layout->addWidget(instructions);
    layout->addWidget(messageInput_);
    layout->addWidget(sendButton_);
    layout->addWidget(clearButton_);
    layout->addWidget(statusLabel_);
    layout->addStretch();

    // Register the content widget with QMainWindow. QMainWindow now manages it
    // in the window's center area.
    setCentralWidget(centralWidget);

    // statusBar() lazily creates QMainWindow's status bar if one does not exist.
    // This first message remains until another message replaces it.
    // https://doc.qt.io/archives/qt-5.15/qstatusbar.html
    statusBar()->showMessage("Application started");

    // QObject::connect(sender, signal, receiver, slot) routes notifications.
    // This modern pointer-to-member syntax is checked by the C++ compiler, so
    // incompatible signal/slot argument types cause a build error rather than a
    // run-time surprise.
    // QObject::connect: https://doc.qt.io/archives/qt-5.15/qobject.html#connect

    // QPushButton emits clicked(bool) after a click. submitMessage() takes no
    // arguments; Qt permits a slot to ignore trailing signal arguments.
    connect(sendButton_, &QPushButton::clicked,
            this, &MainWindow::submitMessage);

    // QLineEdit emits returnPressed() when Return/Enter is pressed, allowing two
    // different user actions to share exactly the same submission logic.
    connect(messageInput_, &QLineEdit::returnPressed,
            this, &MainWindow::submitMessage);

    // Connect the second button to independent clearing behavior.
    connect(clearButton_, &QPushButton::clicked,
            this, &MainWindow::clearMessage);

    // Connect MainWindow's custom signal back to one of its own slots. Sender
    // and receiver happen to be the same object here, but do not need to be.
    // Later the receiver could be a serial-port/network controller object.
    connect(this, &MainWindow::messageSubmitted,
            this, &MainWindow::displayMessage);
}

void MainWindow::submitMessage()
{
    // text() returns a QString. trimmed() returns a copy with leading/trailing
    // whitespace removed. const prevents accidental modification afterward.
    // QString: https://doc.qt.io/archives/qt-5.15/qstring.html
    const QString message = messageInput_->text().trimmed();

    // Reject empty input early. showMessage(text, milliseconds) automatically
    // removes this temporary status message after two seconds.
    if (message.isEmpty()) {
        statusBar()->showMessage("Please enter a message", 2000);
        return;
    }

    // `emit` documents that this is a signal invocation. It expands to nothing
    // at compile time; the moc-generated signal function calls all connected
    // receivers. With the default same-thread connection used here,
    // displayMessage() runs synchronously before the next line executes.
    emit messageSubmitted(message);

    // Clear the editor only after a valid message has been emitted.
    messageInput_->clear();
}

void MainWindow::displayMessage(const QString &message)
{
    // QString supports concatenation with string literals. setText() updates the
    // QLabel and schedules any necessary repaint through Qt's event system.
    statusLabel_->setText("Last message: " + message);

    // The timeout makes this status-bar notification disappear after 2000 ms;
    // the QLabel above continues to display the last submitted value.
    statusBar()->showMessage("messageSubmitted signal received", 2000);
}

void MainWindow::clearMessage()
{
    // Restore both pieces of visible state to their initial values.
    messageInput_->clear();
    statusLabel_->setText("Ready");
    statusBar()->showMessage("Cleared", 1500);

    // Keyboard focus returns to the line editor, so the user can immediately
    // type the next message without clicking it first.
    // https://doc.qt.io/archives/qt-5.15/qwidget.html#setFocus
    messageInput_->setFocus();
}
