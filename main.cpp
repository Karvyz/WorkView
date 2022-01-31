#include "workview.h"
#include "dbservice.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>







int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DbService dbService;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "WorkView_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    WorkView w;
    w.setDbService(&dbService);
    w.updateActivites();
    w.show();
    return a.exec();
}
