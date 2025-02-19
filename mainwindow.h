#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"
#include "pluginmanager.h"
#include "themeswitcher.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    void selectColor();
    void selectBrushSize();
    void loadPlugins();
    void setupThemes();
    
    CanvasWidget *canvasWidget;
    PluginManager *pluginManager;
    ThemeSwitcher *themeSwitcher;
};

#endif // MAINWINDOW_H
