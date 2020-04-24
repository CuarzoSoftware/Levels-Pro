#include "MainWindow.h"

// Constructor
MainWindow::MainWindow(QApplication *app)
{
    // Almacena una instancia de la aplicación
    levels = app;

    // Carga los estilos por defecto
    loadDefaultStyle();

    // Conecta las señales de los botones
    connectButtons();

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
    verticalLayout->addWidget(toolBar);
    verticalLayout->addWidget(horizontalSplitter);

    // Configura el splitter vertical
    verticalSplitter->setProperty("class","verticalMenuSplitter");

    // Añade los menus al splitter vertical
    verticalSplitter->addWidget(tracksMenu);
    verticalSplitter->addWidget(mixerMenu);
    verticalSplitter->addWidget(editorMenu);

    // Añade los menus al splitter horizontal
    horizontalSplitter->addWidget(libraryMenu);
    horizontalSplitter->addWidget(inspectorMenu);
    horizontalSplitter->addWidget(verticalSplitter);
    horizontalSplitter->setStretchFactor(2,2);
    horizontalSplitter->addWidget(listsEditorMenu);
    horizontalSplitter->addWidget(notesMenu);
    horizontalSplitter->addWidget(loopsMenu);
    horizontalSplitter->addWidget(mediaMenu);



}

// Cambios de estado de los botónes del topbar
void MainWindow::libraryBtnChanged(bool state)
{
    libraryMenu->setVisible(state);
}

void MainWindow::inspectorBtnChanged(bool state)
{
    inspectorMenu->setVisible(state);
}
void MainWindow::mixerBtnChanged(bool state)
{
    // Oculta el menú editor
    if(state && topBar->editBtn->isActive())
        topBar->editBtn->setActive(false);

    mixerMenu->setVisible(state);

}
void MainWindow::editorBtnChanged(bool state)
{
    // Oculta el menú mixer
    if(state && topBar->mixerBtn->isActive())
        topBar->mixerBtn->setActive(false);

    editorMenu->setVisible(state);
}
void MainWindow::listsEditorBtnChanged(bool state)
{
    listsEditorMenu->setVisible(state);
}
void MainWindow::notesBtnChanged(bool state)
{
    notesMenu->setVisible(state);
}
void MainWindow::loopsBtnChanged(bool state)
{
    loopsMenu->setVisible(state);
}
void MainWindow::mediaBtnChanged(bool state)
{
    mediaMenu->setVisible(state);
}

void MainWindow::connectButtons()
{
    connect(topBar->libraryBtn,&ToggleButton::changed,this,&MainWindow::libraryBtnChanged);
    connect(topBar->inspectorBtn,&ToggleButton::changed,this,&MainWindow::inspectorBtnChanged);
    connect(topBar->mixerBtn,&ToggleButton::changed,this,&MainWindow::mixerBtnChanged);
    connect(topBar->editBtn,&ToggleButton::changed,this,&MainWindow::editorBtnChanged);
    connect(topBar->listsEditorBtn,&ToggleButton::changed,this,&MainWindow::listsEditorBtnChanged);
    connect(topBar->notesBtn,&ToggleButton::changed,this,&MainWindow::notesBtnChanged);
    connect(topBar->loopsBtn,&ToggleButton::changed,this,&MainWindow::loopsBtnChanged);
    connect(topBar->mediaBtn,&ToggleButton::changed,this,&MainWindow::mediaBtnChanged);
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

