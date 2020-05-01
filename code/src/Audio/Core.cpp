#include "Core.h"
#include <QFontDatabase>
#include <QFile>


Core::Core(QApplication *_levels)
{
    // Stores the app reference
    levels = _levels;
}

void Core::configure()
{
    // Loads default font
    setDefaultFontFamily();

    // Loads the default style
    loadDefaultStyle();
}

void Core::run()
{
    // Creates the main window
    mainWindow = new MainWindow();
    mainWindow->show();
}

// Carga los estilos por defecto
void Core::loadDefaultStyle()
{
    QFile File(":/res/styles/widgets.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    File.close();

    File.setFileName(":/res/styles/tracks.qss");
    File.open(QFile::ReadOnly);
    StyleSheet.append(QLatin1String(File.readAll()));
    File.close();

    levels->setStyleSheet(StyleSheet);
}

void Core::setDefaultFontFamily()
{
    int id = QFontDatabase::addApplicationFont(":res/fonts/HelveticaNeue.ttc");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    QApplication::setFont(font);
}
