#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Load translations
    QTranslator translator;
    if (translator.load(QLocale(), QLatin1String("PixelArtStudio"), QLatin1String("_"), QLatin1String(":/translations"))) {
        app.installTranslator(&translator);
    }

    MainWindow mainWindow;
    mainWindow.setWindowTitle(QObject::tr("Pixel Art Studio"));
    mainWindow.show();

    return app.exec();
}
