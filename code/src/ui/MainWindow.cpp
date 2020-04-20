#include "MainWindow.h"

// Constructor
MainWindow::MainWindow(QApplication *app)
{
    // Almacena una instancia de la aplicación
    levels = app;

    // Carga los estilos por defecto
    loadDefaultStyle();

    // Asigna el widget de la ventana principal
    setCentralWidget(mainWidget);

    // Ajusta el tamaño de la ventana pincipal al del escritorio
    resize(QApplication::screens()[0]->size());

    // La posiciona en el origen
    move(0,0);

    // Asigna el layout vertical al widget principal
    mainWidget->setLayout(verticalLayout);

    // Asigna clase de estilos a el widget principal
    mainWidget->setProperty("class","mainWindow");
    mainWidget->setAttribute(Qt::WA_StyledBackground, true);

    // Elimina los márgenes del layout vertical
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(2);

    // Añade los menus principales al layout vertical
    verticalLayout->addWidget(topBar);
    verticalLayout->addWidget(horizontalSplitter);

    // Configura el splitter
    horizontalSplitter->setOrientation(Qt::Horizontal);
    horizontalSplitter->setHandleWidth(2);

    // Asigna el layout horizontal al bottom widget
    horizontalSplitter->addWidget(libraryMenu);
    horizontalSplitter->addWidget(inspectorMenu);
    horizontalSplitter->addWidget(tracksMenu);


}

// Carga los estilos por defecto
void MainWindow::loadDefaultStyle()
{
    QFile File(":/res/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    levels->setStyleSheet(StyleSheet);
}

MainWindow::~MainWindow()
{
}

