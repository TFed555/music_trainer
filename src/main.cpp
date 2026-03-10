#include "gui/mainwindow.h"
#include <QFile>
#include <QApplication>

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

    MainWindow w;
    w.show();
    return a.exec();
}
