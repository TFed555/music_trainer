#include "gui/mainwindow.h"
#include <QFile>
#include <QApplication>
#include "core/factory/sessionfactory.h"
#include "core/factory/sessionregistry.h"
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontId = QFontDatabase::addApplicationFont(":/Bravura.otf");
    if (fontId == -1) {
        qDebug() << "Failed to load Bravura font";
    } else {
        qDebug() << "Loaded font families:" << QFontDatabase::applicationFontFamilies(fontId);
    }
    QFile stylesFile(":/styles/styles.qss");
    if (stylesFile.open(QFile::ReadOnly)) {
        a.setStyleSheet(stylesFile.readAll());
        stylesFile.close();
    } else {
        qWarning() << "Failed to load styles";
    }

    SessionFactory sessionFactory;
    registerAllSessions(sessionFactory);

    MainWindow w(sessionFactory);
    w.show();
    return a.exec();
}
