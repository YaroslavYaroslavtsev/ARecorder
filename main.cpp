#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include "crusher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Экспериментальная дробилка");
    a.setOrganizationName("Электротехнические системы Сибирь");
    QTranslator *qt_translator = new QTranslator;
    if(qt_translator->load(":tr/qt_ru.qm"))
        a.installTranslator(qt_translator);
    MainWindow w;
    w.show();
    return a.exec();
}
