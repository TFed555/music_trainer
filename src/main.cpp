#include "gui/mainwindow.h"
#include <QFile>
#include <QApplication>
#include "core/factory/sessionfactory.h"
#include "core/factory/sessionregistry.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
