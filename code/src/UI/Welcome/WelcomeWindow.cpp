#include "WelcomeWindow.h"
#include <QApplication>
#include <QScreen>

WelcomeWindow::WelcomeWindow(QWidget *parent) : QWidget(parent)
{
    // Sets the window title
    setWindowTitle("New Project");

    // Default window size and position
    resize(600,500);
    QSize screenSize = QApplication::primaryScreen()->size();
    move(screenSize.width()/2 - width()/2, screenSize.height()/2 - height()/2);


    // Add elements to the left bar
    listLayout->addWidget(newProjectListItem);
    listLayout->addWidget(recentListItem);
    listLayout->addWidget(templatesListItem);
    listLayout->addStretch(1);

    // Configure top horizontal layout
    horizontalLayout->addWidget(leftMenu);

    // Configure main vertical layout
    verticalLayout->addWidget(topWidget);

}
