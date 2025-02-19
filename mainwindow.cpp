#include "mainwindow.h"
#include "canvaswidget.h"
#include "pluginmanager.h"
#include "themeswitcher.h"
#include <QColorDialog>
#include <QInputDialog>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), pluginManager(new PluginManager(this)), themeSwitcher(new ThemeSwitcher(this))
{
    initUI();
    loadPlugins();
    setupThemes();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUI()
{
    // Set window size and minimum size
    resize(800, 600);
    setMinimumSize(400, 300);
    
    // Set window icon
    setWindowIcon(QIcon(":/icons/app_icon.png"));
    
    // Connect theme switcher signals
    connect(themeSwitcher, &ThemeSwitcher::themeChanged, this, [this](const QString &themePath) {
        QFile styleFile(themePath);
        if (styleFile.open(QFile::ReadOnly)) {
            QString styleSheet = QLatin1String(styleFile.readAll());
            setStyleSheet(styleSheet);
        }
    });
    
    // Create Plugins menu
    QMenu *pluginsMenu = menuBar()->addMenu(tr("&Plugins"));
    QAction *refreshPluginsAction = new QAction(tr("&Refresh Plugins"), this);
    connect(refreshPluginsAction, &QAction::triggered, this, &MainWindow::loadPlugins);
    pluginsMenu->addAction(refreshPluginsAction);
    
    // Create canvas widget
    canvasWidget = new CanvasWidget(this);
    
    // Create menu bar
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    
    // Create File menu
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    
    // Add New Canvas action
    QAction *newCanvasAction = new QAction(tr("&New Canvas"), this);
    connect(newCanvasAction, &QAction::triggered, canvasWidget, &CanvasWidget::clearCanvas);
    fileMenu->addAction(newCanvasAction);
    
    // Add Exit action
    QAction *exitAction = new QAction(tr("&Exit"), this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);
    
    // Create Edit menu
    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));
    
    // Add Resize Canvas action
    QAction *resizeCanvasAction = new QAction(tr("&Resize Canvas"), this);
    connect(resizeCanvasAction, &QAction::triggered, this, &MainWindow::resizeCanvas);
    editMenu->addAction(resizeCanvasAction);
    
    // Add Background Color action
    QAction *bgColorAction = new QAction(tr("&Background Color"), this);
    connect(bgColorAction, &QAction::triggered, this, &MainWindow::selectBackgroundColor);
    editMenu->addAction(bgColorAction);
    
    // Create toolbar
    QToolBar *toolBar = addToolBar(tr("Tools"));
    
    // Add color picker action
    QAction *colorAction = new QAction(QIcon(":/icons/color_picker.png"), tr("Color"), this);
    connect(colorAction, &QAction::triggered, this, &MainWindow::selectColor);
    toolBar->addAction(colorAction);
    
    // Add brush size action
    QAction *brushSizeAction = new QAction(QIcon(":/icons/brush.png"), tr("Brush Size"), this);
    connect(brushSizeAction, &QAction::triggered, this, &MainWindow::selectBrushSize);
    toolBar->addAction(brushSizeAction);
    
    // Add clear canvas action
    QAction *clearAction = new QAction(QIcon(":/icons/clear.png"), tr("Clear"), this);
    connect(clearAction, &QAction::triggered, canvasWidget, &CanvasWidget::clearCanvas);
    toolBar->addAction(clearAction);
    
    // Set canvas as central widget
    setCentralWidget(canvasWidget);
    
    // Set style sheet for pixel art theme
    setStyleSheet(
        "QMainWindow {"
        "   background-color: #2d2d2d;"
        "   color: #ffffff;"
        "}"
    );
}

void MainWindow::selectColor()
{
    QColor color = QColorDialog::getColor(canvasWidget->getPenColor(), this, tr("Select Pen Color"));
    if (color.isValid()) {
        canvasWidget->setPenColor(color);
    }
}

void MainWindow::selectBrushSize()
{
    bool ok;
    int size = QInputDialog::getInt(this, tr("Select Brush Size"),
                                  tr("Brush Size (1-50):"), canvasWidget->getPenSize(), 1, 50, 1, &ok);
    if (ok) {
        canvasWidget->setPenSize(size);
    }
}

void MainWindow::resizeCanvas()
{
    bool ok;
    int width = QInputDialog::getInt(this, tr("Canvas Width"),
                                   tr("Width:"), canvasWidget->width(), 100, 4096, 1, &ok);
    if (!ok) return;
    
    int height = QInputDialog::getInt(this, tr("Canvas Height"),
                                    tr("Height:"), canvasWidget->height(), 100, 4096, 1, &ok);
    if (ok) {
        canvasWidget->resizeCanvas(width, height);
    }
}

void MainWindow::selectBackgroundColor()
{
    QColor color = QColorDialog::getColor(canvasWidget->getBackgroundColor(), this, tr("Select Background Color"));
    if (color.isValid()) {
        canvasWidget->setBackgroundColor(color);
    }
}

void MainWindow::loadPlugins()
{
    pluginManager->loadPlugins();
    QStringList plugins = pluginManager->availablePlugins();
    if (!plugins.isEmpty()) {
        QMessageBox::information(this, tr("Plugins Loaded"),
                               tr("Successfully loaded plugins:\n- %1")
                               .arg(plugins.join("\n- ")));
    }
}

void MainWindow::setupThemes()
{
    QMenu *themeMenu = menuBar()->addMenu(tr("&Themes"));
    
    QAction *defaultThemeAction = new QAction(tr("&Default"), this);
    connect(defaultThemeAction, &QAction::triggered, this, [this]() {
        themeSwitcher->switchTheme("default");
    });
    themeMenu->addAction(defaultThemeAction);
    
    QAction *darkThemeAction = new QAction(tr("&Dark"), this);
    connect(darkThemeAction, &QAction::triggered, this, [this]() {
        themeSwitcher->switchTheme("dark");
    });
    themeMenu->addAction(darkThemeAction);
    
    QAction *lightThemeAction = new QAction(tr("&Light"), this);
    connect(lightThemeAction, &QAction::triggered, this, [this]() {
        themeSwitcher->switchTheme("light");
    });
    themeMenu->addAction(lightThemeAction);
}
